#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>

std::string noteNames[] = {"Do", "Re", "Mi", "Fa", "Sol", "La", "Si"};
std::string noteCodes[] = {"c'", "d'", "e'", "f'", "g'", "a'", "b'"};
std::string fullNoteCodes[] = {"<c' c'' >", "<d' d''>", "<e' e''>", "<f' f''>",
                               "<g' g''>",  "a'",       "<b b'>",   "<c' c''>"};

int noRepeat = 1;
int latestNotes[7] = {-1};

int generateNote() {
  double randNum = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return int(randNum * 7);
}

int generateUniqueNote() {
  int aNote;
  bool isUnique = false;

  while (!isUnique) {
    isUnique = true;
    aNote = generateNote();
    for (int i = 0; i < noRepeat; ++i) {
      // std::cerr << i << " cheching " << latestNotes[i] << " against " <<
      // aNote << std::endl;
      if (latestNotes[i] == aNote) {
        isUnique = false;
        break;
      }
    }
  }

  return aNote;
}

void printNote(int nota, std::string &format) {
  if (format == "name")
    std::cout << "\" " << noteNames[nota] << " \" ";
  else if (format == "note")
    std::cout << fullNoteCodes[nota] << " ";
  else if (format == "noteSimple")
    std::cout << noteCodes[nota] << " ";
  else
    std::cerr << "unknown format: " << format << std::endl;
}

int main(int argc, char *argv[]) {
  //	if (argc<2) return -1;
  //	if (argc>3) return -1;
  //	int timerSeed = 0xcaffe;  // and not time(NULL)

  if (argc != 5) {
    std::cerr << "Syntax: " << argv[0]
              << " numeroNote timerSeed noRepeat [name|note]" << std::endl;
    return -1;
  }
  int nNotes = atoi(argv[1]);
  unsigned long timerSeed = std::stol(argv[2], nullptr, 10);
  noRepeat = atoi(argv[3]);
  if (noRepeat < 0)
    noRepeat = 0;
  if (noRepeat > 6)
    noRepeat = 6;
  std::string formatNote = argv[4];

  srand(timerSeed);

  int nota;
  for (int i = 0; i < nNotes; ++i) {
    nota = generateUniqueNote();
    printNote(nota, formatNote);
    if (i % 4 == 3)
      std::cout << std::endl;
    if (noRepeat)
      latestNotes[i % noRepeat] = nota;
  }
  std::cout << std::endl;
  return 0;
}
