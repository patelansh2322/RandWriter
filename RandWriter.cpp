// Copyright 2025 Ansh Patel

#include "RandWriter.hpp"
#include <iostream>
#include <map>
#include <set>
#include <random>
#include <stdexcept>

// Constructor that builds the Markov model from the input
RandWriter::RandWriter(const std::string& text, size_t k) : data(text), k_(k), gen(42) {
    if (text.length() < k) {
        throw std::invalid_argument("Text too short for given k");
    }

    std::string wrap = text + text.substr(0, k);

    for (size_t i = 0; i < text.length(); ++i) {
        std::string gram = wrap.substr(i, k);
        char next = wrap[i + k];

        count[gram]++;
        next_chars[gram][next]++;
    }

    std::set<char> letters(text.begin(), text.end());
    alphabet = std::string(letters.begin(), letters.end());
}

// Returns the order of the model (value of k)
size_t RandWriter::orderK() const {
    return k_;
}

// Returns how many times a kgram appears in the text
int RandWriter::freq(const std::string& gram) const {
    if (gram.size() != k_) {
        throw std::invalid_argument("Wrong size kgram");
    }
    if (count.find(gram) != count.end()) {
        return count.at(gram);
    }
    return 0;
}

// Returns how many times char c follows kgram
int RandWriter::freq(const std::string& gram, char c) const {
    if (gram.size() != k_) {
        throw std::invalid_argument("Wrong size kgram");
    }
    if (next_chars.find(gram) != next_chars.end()) {
        if (next_chars.at(gram).find(c) != next_chars.at(gram).end()) {
            return next_chars.at(gram).at(c);
        }
    }
    return 0;
}

// Picks a random next character after the given kgram
char RandWriter::kRand(const std::string& gram) {
    if (gram.size() != k_) {
        throw std::invalid_argument("Wrong size kgram");
    }
    if (next_chars.find(gram) == next_chars.end()) {
        throw std::invalid_argument("Unknown kgram");
    }
    int total = 0;
    for (auto& pair : next_chars[gram]) {
        total += pair.second;
    }

    std::uniform_int_distribution<int> d(0, total - 1);
    int r = d(gen);

    for (auto& pair : next_chars[gram]) {
        r -= pair.second;
        if (r < 0) {
            return pair.first;
        }
    }

    throw std::runtime_error("kRand failed somehow");
}

// Generate a string of length L starting with the given kgram
std::string RandWriter::generate(const std::string& start, size_t len) {
    if (start.size() != k_) {
        throw std::invalid_argument("Start size not k");
    }
    if (len < k_) {
        throw std::invalid_argument("Length must be >= k");
    }

    std::string result = start;

    // Keep adding random characters
    while (result.size() < len) {
        std::string last = result.substr(result.size() - k_, k_);
        result += kRand(last);
    }
    return result;
}

// Overload << so we can print the model easily
std::ostream& operator<<(std::ostream& out, const RandWriter& rw) {
    out << "Markov order: " << rw.k_ << "\n";
    out << "Alphabet: " << rw.alphabet << "\n\n";

    // Print each kgram and its next character frequencies
    for (auto& p : rw.next_chars) {
        out << "\"" << p.first << "\" (" << rw.count.at(p.first) << ")\n";
        for (auto& q : p.second) {
            out << "  '" << q.first << "' -> " << q.second << "\n";
        }
    }

    return out;
}
