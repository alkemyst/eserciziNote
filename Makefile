
all: bin/generaNote bin/timeToKey

bin/generaNote: src/generaNote.cpp
	g++ -fmax-errors=1 -Wall -Werror -std=c++14 src/generaNote.cpp -o bin/generaNote

bin/timeToKey: src/timeToKey.cpp
	g++ -fmax-errors=1 -Wall -Werror -std=c++14 src/timeToKey.cpp -o bin/timeToKey

test: generaNote
	bin/generaNote 1000000 | tr ' ' '\n' | egrep . | sort | uniq -c

clean:
	rm -f bin/generaNote bin/timeToKey

