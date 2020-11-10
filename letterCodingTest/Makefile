
all: test_binary_ternary test_complete

test_binary_ternary: test_binary_ternary.cpp
	g++ -fmax-errors=1 test_binary_ternary.cpp -o test_binary_ternary

test_complete: test_complete.cpp
	g++ -fmax-errors=1 test_complete.cpp -o test_complete

test: test_binary_ternary test_complete
	./test_binary_ternary 000000000-III 100
	./test_complete 99-xa-9 100

clean:
	rm -f test test_binary_ternary test_complete

