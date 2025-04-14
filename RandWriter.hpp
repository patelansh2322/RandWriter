// Copyright [2025] Ansh Patel

#include <string>
#include <map>
#include <random>
#include <set>
#include <stdexcept>
#include <iostream>

class RandWriter {
 public:
    // Create a Markov model of order k from given text
    // Assume that text has length at least k.
    RandWriter(const std::string& str, size_t k);

    size_t orderK() const;  // Order k of Markov model

    // Number of occurences of kgram in text
    // Throw an exception if kgram is not length k
    int freq(const std::string& kgram) const;
    // Number of times that character c follows kgram
    // if order=0, return num of times that char c appears
    // (throw an exception if kgram is not of length k)
    int freq(const std::string& kgram, char c) const;

    // Random character following given kgram
    // (throw an exception if kgram is not of length k)
    // (throw an exception if no such kgram)
    char kRand(const std::string& kgram);
    // Generate a string of length L characters by simulating a trajectory
    // through the corresponding Markov chain. The first k characters of
    // the newly generated string should be the argument kgram.
    // Throw an exception if kgram is not of length k.
    // Assume that L is at least k
    std::string generate(const std::string& kgram, size_t l);
    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    // Private member variables go here
    std::string data;
    size_t k_;
    std::map<std::string, std::map<char, int>> next_chars;
    std::map<std::string, int> count;
    std::string alphabet;
    std::mt19937 gen;
};
