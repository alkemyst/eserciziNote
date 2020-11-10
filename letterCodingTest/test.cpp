#include <iostream>
#include <cstdio>
#include <string>
#include <ctime>
#include <vector>

const std::string vowels = "012";
const std::string goodConsonants = "OI";

int decode(const std::string& myCode) {
 
  char aLetter;
  // std::cerr << "my code is '" << myCode << "'" << std::endl;
  std::string valueString = "";

  size_t foundPos;
  int digitValue=1;
  int nDigits;
  int result=0;

  std::vector <const std::string*> myDigits;
  myDigits.push_back(&vowels);
  myDigits.push_back(&goodConsonants);

  for (int i=myCode.length()-1; i>=0; --i) {
	  aLetter = myCode[i];
	  for (const auto digits : myDigits) {
		  // std::cerr << "letter '" << aLetter << "'";
		  if ( (foundPos=digits->find(aLetter)) != std::string::npos) {
			  nDigits = digits->length();
			  // std::cerr << " is digit #" << foundPos;
			  valueString = std::to_string(nDigits) + "-" + valueString;
			  result += int(foundPos)*digitValue;
			  digitValue *= nDigits;
		  }
	  }
	  // std::cerr << std::endl;
  }
  // std::cerr << valueString << std::endl;
  return result;
}

int main(int argc, char* argv[]) {
	std::string myCode = argv[1];
	int resultingCode = decode(myCode);
	std::cout << resultingCode << std::endl;

	return 0;
}
