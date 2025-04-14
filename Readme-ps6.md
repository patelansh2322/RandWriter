# PS6: RandWriter

## Contact
Name: Ansh Patel
Section: 202
Time to Complete: ~7 Hours


## Description
Explain what the project does.

This project creates random-looking text based on a sample input using a method called a Markov chain. It looks at patterns of letters in the input and learns which letters usually come after which. Then, using that information, it builds new text that sounds similar to the original. You choose how many letters it looks at (order k) and how long the final text should be. The program starts with the first k characters from the input and keeps adding new letters based on the patterns.

### Features
Describe what your major decisions were and why you did things that way.

One major decision was to use a map of maps to keep track of how often each letter follows a specific group of k letters (called a k-gram). This made it easier to store and look up frequencies quickly. We also decided to make the input text circular by adding the first k characters to the end, so the model could wrap around and treat the input as continuous. For randomness, we used a built-in random number generator with a fixed seed to make sure the results are repeatable. We kept the code simple with easy-to-read variable names and basic logic so it's clear what each part does. This helped make the program easier to debug, test, and understand.

### Testing
What tests did you write?  What exceptions did you use?  Does your code pass the tests?

I  wrote three main tests to make sure the RandWriter class works as expected. The first test checks if the constructor throws an exception when the input string is shorter than the value of k, which is required for the model to work properly. This helps catch invalid input early. The second test verifies that the orderK() function correctly returns the value of k that was passed during construction. The third test checks if the generate() function produces a string of the right length and starts with the correct seed. I used std::invalid_argument for input validation and BOOST_REQUIRE_THROW to test for expected exceptions. All the tests pass successfully, which shows that the main functions and error handling in the code are working correctly.

### Lambda
What does your lambda expression do?  What function did you pass it to?

This project does not use any lambda expressions, so there isn't one to describe. All the logic is written using regular functions and loops.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

One thing I had trouble with was getting the random character generation to work correctly. At first, I wasn’t sure how to choose the next character based on its frequency, but I figured it out using a running total and subtracting from it until the right character was found. I also had to learn how to use the std::mt19937 random number generator and set it up so the output is repeatable, which was new for me. Another challenge was making sure the program could handle edge cases, like when the input text was too short or when someone gave a bad k-gram. I had to add checks and throw exceptions to make the program more reliable. Writing the tests using Boost also helped me understand how to catch bugs early. I learned how to write basic unit tests, use BOOST_REQUIRE_THROW, and make sure functions behave correctly under different conditions. As of now, everything I tested works. The code seems to be working fine.

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I did not do anything extra for this project.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

Random generator: https://cplusplus.com/reference/random/mt19937/
Markov chain model: https://en.wikipedia.org/wiki/Markov_chain
