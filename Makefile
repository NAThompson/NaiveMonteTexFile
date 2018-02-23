CXX := g++
CPPFLAGS := --std=c++11 -O3 -march=native

all:
	pdflatex NaiveMonteCarloOnModernHardware bailey_example.x

final:
	pdflatex NaiveMonteCarloOnModernHardware
	bibtex NaiveMonteCarloOnModernHardware
	pdflatex NaiveMonteCarloOnModernHardware

bailey_example.x: bailey_example.cpp
	$(CXX) $(CPPFLAGS) -I../boost/libs/math/include $< -o $@ -pthread

clean:
	rm -f NaiveMonteCarloOnModernHardware.bbl  NaiveMonteCarloOnModernHardware.log  NaiveMonteCarloOnModernHardware.pdf NaiveMonteCarloOnModernHardware.aux  NaiveMonteCarloOnModernHardware.blg  NaiveMonteCarloOnModernHardware.out *.x
