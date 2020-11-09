

generaNote: generaNote.cpp
	g++ generaNote.cpp -o generaNote

test: generaNote
	./generaNote 1000000 | tr ' ' '\n' | egrep . | sort | uniq -c

