# 326627635 | adi.peisach@gmail.com

CXX=clang++
CXXFLAGS=-std=c++14 -Werror -Wsign-conversion
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

DOCTEST_INCLUDE = -I /usr/include/doctest
BUILDING_SOURCES = Board/Buildings/Road.cpp Board/Buildings/Settlement.cpp
CARD_SOURCES = Cards/Card.cpp Cards/MonopolCard.cpp Cards/YearOfPlenty.cpp Cards/KnightCard.cpp Cards/PointsCard.cpp Cards/RoadsCard.cpp
TILES_SOURCES = Board/Tiles/Field.cpp Board/Tiles/Forest.cpp Board/Tiles/Mine.cpp Board/Tiles/Mountains.cpp Board/Tiles/Pasture.cpp Board/Tiles/Tile.cpp Board/Tiles/Direction.cpp
CODE_SOURCES = $(BUILDING_SOURCES) $(TILES_SOURCES) Board/Board.cpp Player.cpp Game.cpp $(CARD_SOURCES)
CODE_HEADERS = $(subst .cpp,.h,$(CODE_SOURCES))
CODE_OBJECTS = $(subst .cpp,.o,$(CODE_SOURCES))
TEST_SOURCES = Tests/TestGameFunctions.cpp Tests/TestTrading.cpp Tests/TestCards.cpp Tests/TestBoard.cpp
TEST_OBJECTS = $(subst .cpp,.o,$(TEST_SOURCES))

catan: demo
	./$^

all: demo testMake

demo: $(CODE_OBJECTS) Demo.cpp
	$(CXX) $(CXXFLAGS) $^ -o demo -lstdc++

testfull: testFullMake
	./testFull

testFullMake: Tests/TestGame.o $(CODE_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o testFull -lstdc++ -lm $(DOCTEST_INCLUDE)

test: testMake
	./test

testMake: Tests/TestCounter.o $(TEST_OBJECTS) $(CODE_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test -lstdc++ -lm $(DOCTEST_INCLUDE)

tidy:
	clang-tidy $(CODE_SOURCES) \
        -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory \
        -warnings-as-errors=-* \
        -header-filter=".*" \
        -extra-arg=-Wno-shorten-64-to-32

valgrind: demo testMake
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./testFull 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test testFull Cards/*.o Board/Buildings/*.o Board/Tiles/*.o Board/*.o Tests/*.o