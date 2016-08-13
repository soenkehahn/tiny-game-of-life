SOURCES=test/test.cpp tiny-game-of-life/world.cpp
OBJECTS=$(SOURCES:%.cpp=_build/%.o)

test: _build/run-test
	./_build/run-test

_build/run-test: $(OBJECTS)
	g++ $(OBJECTS) -o _build/run-test

_build/%.o: %.cpp
	mkdir -p _build/test
	mkdir -p _build/tiny-game-of-life
	g++ -I tiny-game-of-life $*.cpp -c -Wno-write-strings -std=c++11 -o _build/$*.o

clean:
	rm -rf _build
