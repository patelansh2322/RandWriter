// Copyright 2025 Ansh Patel

#include <iostream>
#include <sstream>
#include <string>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    // Make sure user gave us exactly 2 command-line arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <order k> <length L>\n";
        return 1;
    }

    // Read in k and L from command line
    size_t k, L;
    std::istringstream(argv[1]) >> k;
    std::istringstream(argv[2]) >> L;

    // Read the full input text
    std::string input_text;
    std::string line;
    while (std::getline(std::cin, line)) {
        input_text += line + '\n';
    }

    // Remove trailing newline
    if (!input_text.empty() && input_text.back() == '\n') {
        input_text.pop_back();
    }

    // Check if the input text is long enough
    if (input_text.length() < k || L < k) {
        std::cerr << "Error: text must be at least length k, and L must be >= k\n";
        return 1;
    }

    try {
        // Build the Markov model using the input text and order k
        RandWriter model(input_text, k);

        // Use the first k letters as the starting kgram
        std::string seed = input_text.substr(0, k);

        // Generate L characters of output starting from the seed
        std::string generated = model.generate(seed, L);

        // Print the result to standard output
        std::cout << generated << std::endl;
    } catch (const std::exception& e) {
        // Print any error message if something goes wrong
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
