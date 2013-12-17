all:
	clang++ --std=c++11 --stdlib=libc++ readfile.cpp acapla.cpp -o acapla.out
	clang++ --std=c++11 --stdlib=libc++ readfile.cpp logan.cpp -o logan.out

run:
	./acapla.out test_cases.txt > acapla.result.txt
	./logan.out test_cases.txt > logan.result.txt

diff:
	diff acapla.result.txt result.txt
	diff logan.result.txt result.txt
