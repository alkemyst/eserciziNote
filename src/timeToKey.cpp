#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

const std::string vowels = "aeiouy";
const std::string goodConsonants = "bcdfgjklmnpqrstvwxz";
const std::string digits = "0123456789";

char generate(const std::string &reference) {
  int length = reference.length();
  double randNum = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  char result = reference[int(randNum * length)];
  return result;
}

int decode(const std::string &myCode) { return myCode.length(); }

std::string generateNewCode(std::string structure) {
  std::string result = "";
  for (int i = 0; i < structure.length(); ++i) {
    if (structure[i] == 'a')
      result += generate(vowels);
    else if (structure[i] == 'z')
      result += generate(goodConsonants);
    else if (structure[i] == 's')
      result += generate(goodConsonants);
    else if (structure[i] == '0')
      result += generate(digits);
    else if (structure[i] == '1')
      result += generate(digits);
    else if (structure[i] == '2')
      result += generate(digits);
    else if (structure[i] == '3')
      result += generate(digits);
    else if (structure[i] == '4')
      result += generate(digits);
    else if (structure[i] == '5')
      result += generate(digits);
    else if (structure[i] == '6')
      result += generate(digits);
    else if (structure[i] == '7')
      result += generate(digits);
    else if (structure[i] == '8')
      result += generate(digits);
    else if (structure[i] == '9')
      result += generate(digits);
    else if (structure[i] == '-')
      result += '-';
    else {
      std::cerr << "ERROR: unknown code '" << structure[i] << "'" << std::endl;
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Syntax: " << argv[0]
              << " 'generate' timerSeed : generates a new code" << std::endl;
    std::cerr
        << "Syntax: " << argv[0]
        << " 'deccode'  your-code-goes-here : generates a number from your code"
        << std::endl;
    return -1;
  }

  std::string command = argv[1];
  if (command == "generate") {
    int aSeed = atoi(argv[2]);
    if (aSeed == 0) {
      std::cerr << "Error: the seed is zero!" << std::endl;
      return -1;
    }
    srand(aSeed);
    std::string newCode = generateNewCode("sasa-sasa-sasa");
    std::cout << newCode << std::endl;
  } else if (command == "decode") {
    std::string myCode = argv[2];
    int resultingCode = decode(myCode);
    std::cout << resultingCode << std::endl;
  } else {
    std::cerr << "Error: unknown command '" << command
              << "': should be either 'generate' or 'decode'" << std::endl;
    return -1;
  }

  return 0;
}
