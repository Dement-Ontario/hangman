# Overview

This program is a game of Hangman. The game picks from a list of words at random, and you need to guess the word letter by letter. If you make too many wrong guesses, you lose! This program also loads words from (and lets you add words to) a CSV file, and it also manually creates a new hangman object using new and delete.

I've never tried C++ before and I've been told it's used quite a bit, so I figure this project would give me some experience in it. I've also been told it's more difficult to write in, which I definitely saw in writing some of the code; it's definitely more complicated to do certain things.

[Software Demo Video](https://www.youtube.com/watch?v=W4rVsPOHuCI)

# Development Environment

I used Visual Studio Code with the C++ extension to develop this project.

I wrote this project in C++ with the MSVC compiler. No external libraries were used.

# Useful Websites

- [VSCode Docs: Configure VS Code for Microsoft C++](https://code.visualstudio.com/docs/cpp/config-msvc)
- [W3Schools: C++ Tutorial](https://www.w3schools.com/cpp/default.asp)
- [Stack Overflow: Random Number in Range](https://stackoverflow.com/questions/7560114/random-number-c-in-some-range)
- [GeeksforGeeks: Dynamic Object Initialization](https://www.geeksforgeeks.org/cpp/dynamic-initialization-of-object-in-c/)
- [Stack Overflow: How to Split Comma-Separated Strings with stringstream](https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings)
- [Stack Overflow: How to Determine if a char is a Number or Letter](https://stackoverflow.com/questions/8611815/determine-if-char-is-a-num-or-letter)
- [GeeksforGeeks: How to Convert Strings to Lowercase](https://www.geeksforgeeks.org/cpp/how-to-convert-std-string-to-lower-case-in-cpp/)
- [Stack Overflow: How to Use cin with Spaces](https://stackoverflow.com/questions/5838711/stdcin-input-with-spaces)
- [Stack Overflow: How to Append Text to a Text File](https://stackoverflow.com/questions/2393345/how-to-append-text-to-a-text-file-in-c)
- [Stack Overflow: How to Detect an Empty File](https://stackoverflow.com/questions/26228424/how-to-detect-an-empty-file-in-c)

# Future Work

- I've gotten adding a word to the CSV file working, but I didn't make anything that removed a word from the file. I'll have to do that next.
- I figure I should move everything related to text output inside the Hangman class to the UI class at some point, for consistency's sake.
- Using raw string literals for the hangman status makes the array very long and seems inefficient. I might want to try making one string and replacing chars inside as needed.