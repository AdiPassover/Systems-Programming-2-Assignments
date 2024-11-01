# 326627635 | adi.peisach@gmail.com

CXX=clang
CXXFLAGS=-std=c++11 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

CODE_SOURCES = Graph.cpp Algorithms.cpp
CODE_OBJECTS=$(subst .cpp,.o,$(CODE_SOURCES))
TEST_SOURCES= TestCounter.cpp Test.cpp
TEST_OBJECTS=$(subst .cpp,.o,$(TEST_SOURCES))

run: demo
	./$^

all: demo test

demo: Demo.o $(CODE_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo -lstdc++

test: $(TEST_OBJECTS) $(CODE_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -lstdc++ -lm

tidy:
	clang-tidy $(CODE_SOURCES) \
        -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory \
        -warnings-as-errors=-* \
        -header-filter=".*" \
        -extra-arg=-Wno-shorten-64-to-32

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test
