#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

const std::string vowels = "aeiouy";
const std::string goodConsonants = "bcdfgjklmnpqrstvwxz";
const std::string decimalDigits = "0123456789";
const std::string separators = "-+.";

std::vector<const std::string *> allDigitSet;

void prepareDigitSets() {
  if (allDigitSet.size() == 0) {
    allDigitSet.push_back(&vowels);
    allDigitSet.push_back(&goodConsonants);
    allDigitSet.push_back(&decimalDigits);
  }
}

std::string encode(const int originalInput, const std::string &myCode,
                   bool truncate = true) {
  int currentInput = originalInput;

  prepareDigitSets();

  int nDigits, thisDigit, digitValue;
  std::string result = "";
  int compute = 0;
  char aLetter;

  digitValue = 1;
  for (int i = myCode.length() - 1; i >= 0; --i) {
    aLetter = myCode[i];
    if (separators.find(aLetter) != std::string::npos) {
      result = "-" + result;
    } else
      for (const auto digits : allDigitSet) {
        if (digits->find(aLetter) != std::string::npos) {

          // There are nDigits digits in this position
          nDigits = digits->length();

          // This digit is ...
          thisDigit = currentInput % nDigits;

          // Let's update the final result
          result = digits->at(thisDigit) + result;

          // I remove the digit and divide the current input value
          currentInput -= thisDigit;
          currentInput /= nDigits;

          // And write the result we are actually encoding here
          // and also update digitValue for the next digit, if any
          compute += thisDigit * digitValue;
          digitValue *= nDigits;
        }
      }
    if (currentInput == 0)
      break;
  }

  if (!truncate) {
    // Final check to make sure the coding went right
    if (originalInput != compute) {
      std::cerr << "WARNING: you gave me " << originalInput
                << " and I think I encoded " << compute << " using system '"
                << myCode << "'" << std::endl;
    }
  }
  return result;
}

int decode(const std::string &myCode) {

  char aLetter;
  std::string valueString = "";

  size_t foundPos;
  int digitValue = 1;
  int nDigits;
  int result = 0;

  prepareDigitSets();

  for (int i = myCode.length() - 1; i >= 0; --i) {
    aLetter = myCode[i];
    for (const auto digits : allDigitSet) {
      if ((foundPos = digits->find(aLetter)) != std::string::npos) {
        nDigits = digits->length();
        valueString = std::to_string(nDigits) + "-" + valueString;
        result += int(foundPos) * digitValue;
        digitValue *= nDigits;
      }
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Syntax: " << argv[0]
              << " 'encode' timerSeed : generates a new code" << std::endl;
    std::cerr
        << "Syntax: " << argv[0]
        << " 'decode'  your-code-goes-here : generates a number from your code"
        << std::endl;
    return -1;
  }

  std::string command = argv[1];
  if (command == "encode") {
    int aSeed = atoi(argv[2]);
    if (aSeed == 0) {
      std::cerr << "Error: the seed is zero!" << std::endl;
      return -1;
    }
    std::string newCode = encode(aSeed, "sasa-9999-sasa");
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

