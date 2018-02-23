CXX := g++-7
CPPFLAGS := --std=c++11 -O3 -march=native
KILLKAHAN := -funsafe-math-optimizations
INCFLAGS := -I../boost/libs/math/include -I../boost/libs/math/atomic/include -I../boost/libs/lockfree/include -I../boost

all: final bailey_example.x
	pdflatex -shell-escape NaiveMonteCarloOnModernHardware

final:
	pdflatex -shell-escape NaiveMonteCarloOnModernHardware
	bibtex NaiveMonteCarloOnModernHardware
	pdflatex -shell-escape NaiveMonteCarloOnModernHardware

bailey_example.x: bailey_example.cpp
	$(CXX) $(CPPFLAGS) $(INCFLAGS) $< -o $@ -pthread

clean:
	rm -f NaiveMonteCarloOnModernHardware.bbl  NaiveMonteCarloOnModernHardware.log  NaiveMonteCarloOnModernHardware.pdf NaiveMonteCarloOnModernHardware.aux  NaiveMonteCarloOnModernHardware.blg  NaiveMonteCarloOnModernHardware.out *.x
