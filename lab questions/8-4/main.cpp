#include <iostream>
#include <string>
#include <algorithm>

int main()
{
  // Basic string operations
  std::string str = "Hello, World!";

  // 1. String concatenation
  std::string str1 = "Hello";
  std::string str2 = " World";
  std::string result = str1 + str2; // "Hello World"

  // 2. Substring extraction
  std::string text = "Programming in C++";
  std::string sub = text.substr(0, 11); // "Programming"

  // 3. String searching
  std::string sentence = "The quick brown fox";
  size_t found = sentence.find("quick"); // returns position of "quick"

  // 4. String conversion to upper/lower case
  std::string mixed = "Hello World";
  std::transform(mixed.begin(), mixed.end(), mixed.begin(), ::toupper);
  // Now mixed = "HELLO WORLD"

  // 5. String comparison
  std::string s1 = "apple";
  std::string s2 = "banana";
  if (s1 < s2)
  { // true (lexicographical comparison)
    std::cout << "apple comes before banana\n";
  }

  // 6. Removing whitespace from beginning/end
  std::string trimMe = "   spaces around   ";
  trimMe.erase(0, trimMe.find_first_not_of(" ")); // Remove leading spaces
  trimMe.erase(trimMe.find_last_not_of(" ") + 1); // Remove trailing spaces

  // 7. String replacement
  std::string replace = "Hello World";
  replace.replace(replace.find("World"), 5, "C++"); // "Hello C++"

  // 8. Converting string to integer
  std::string number = "42";
  int num = std::stoi(number); // converts "42" to integer 42

  // 9. Converting number to string
  int value = 123;
  std::string str_value = std::to_string(value); // converts 123 to "123"

  return 0;
}
