CXXFLAGS = -std=c++11 -Wall -Wextra -Wpedantic -Weverything -Wno-c++98-compat -Wno-missing-prototypes -Wno-padded -Wno-unused-parameter

build: test

test: csscolorparser.o test.o
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^

clean:
	rm -rf *.o test

.PHONY: clean
