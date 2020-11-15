#include <cstdio>
#include <ctime>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> noteVector;

noteVector noteNames_en = {"\" C \"", "\" D \"", "\" E \"", "\" F \"",
                           "\" G \"", "\" A \"", "\" B \""};
noteVector noteNames = {"\" do \"",  "\" re \"", "\" mi \"", "\" fa \"",
                        "\" sol \"", "\" la \"", "\" si \""};
noteVector noteCodes = {"c'", "d'", "e'", "f'", "g'", "a'", "b'"};
noteVector fullNoteCodes = {"<c' c'' >", "<d' d''>",   "<e' e''>",  "<f' f''>",
                            "<g' g''>",  "<a a' a''>", "<b b' b''>"};
noteVector fullNoteCodes_bass = {"<c, c c'>", "<d, d d'>", "<e, e>", "<f, f>",
                                 "<g, g>",    "<a, a>",    "<b, b>"};
noteVector fakeCodes = {"d'"};
noteVector fakeCodes_bass = {"d"};

int noRepeat = 1;
std::map<int, int> latestNotes;

int generateNote(int numberOfNotes) {
  double randNum = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
  return int(randNum * numberOfNotes);
}

int generateUniqueNote(int numberOfNotes) {
  int aNote;
  bool isUnique = false;

  while (!isUnique) {
    isUnique = true;
    aNote = generateNote(numberOfNotes);
    for (unsigned int i = 0; i < latestNotes.size(); ++i) {
      if (latestNotes[i] == aNote) {
        isUnique = false;
        break;
      }
    }
  }

  return aNote;
}

// Here is the one and only switch to select the notes array
noteVector &getNoteVector(const std::string &format) {
  if (format == "name")
    return noteNames;
  else if (format == "notes_treble")
    return fullNoteCodes;
  else if (format == "notes_bass")
    return fullNoteCodes_bass;
  else if (format == "noteSimple")
    return noteCodes;
  else if (format == "fake_treble")
    return fakeCodes;
  else if (format == "fake_bass")
    return fakeCodes_bass;
  else {
    std::cerr << "unknown format: " << format << std::endl;
    return noteNames;
  }
}

// Get the number of notes in this array
int nNotesAvailable(const noteVector &pNoteVector) {
  return pNoteVector.size();
}

void printNote(int nota, const noteVector &pNoteVector) {
  std::cout << pNoteVector[nota] << " ";
}

bool isFakeGeneration(const std::string &format) {
  if (format == "fake_treble")
    return true;
  else if (format == "fake_bass")
    return true;
  else
    return false;
}

int main(int argc, char *argv[]) {
  if (argc != 6) {
    std::cerr << "Syntax: " << argv[0]
              << " numeroNote timerSeed noRepeat [name|note|fake] notesPerLine"
              << std::endl;
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
  int notesPerLine = atoi(argv[5]);

  srand(timerSeed);

  int nota;
  noteVector &correctNotesArray = getNoteVector(formatNote);
  if (isFakeGeneration(formatNote)) {
    // Fake note generation:
    // do not bother avoiding duplicates or randomly generate the note
    for (int i = 0; i < nNotes; ++i) {
      nota = 0;
      printNote(nota, correctNotesArray);
      if ((notesPerLine != 0) && (formatNote != "name") &&
          ((i % notesPerLine) == (notesPerLine - 1)))
        std::cout << " \\break ";

      if (i % 4 == 3)
        std::cout << std::endl;
    }
    std::cout << std::endl;
  } else {
    // Actual note generation
    int numberOfNotes = nNotesAvailable(correctNotesArray);
    for (int i = 0; i < nNotes; ++i) {
      nota = generateUniqueNote(numberOfNotes);
      printNote(nota, correctNotesArray);
      if ((notesPerLine != 0) && (formatNote != "name") &&
          ((i % notesPerLine) == (notesPerLine - 1)))
        std::cout << " \\break ";

      if (i % 4 == 3)
        std::cout << std::endl;
      if (noRepeat)
        latestNotes[i % noRepeat] = nota;
    }
    std::cout << std::endl;
  }
  return 0;
}
