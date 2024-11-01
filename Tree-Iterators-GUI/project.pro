QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = main
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += Demo.cpp Node.cpp Tree.cpp Screen.cpp Complex.cpp

# Define a custom target to run the program
run.target = tree
run.commands = ./main
run.depends = first # Depend on the first build target, ensuring the program is built before running

QMAKE_EXTRA_TARGETS += run

# Define the custom target for the test
test.target = test
test.commands = ./test
test.depends = test_executable

QMAKE_EXTRA_TARGETS += test

test_executable.target = testMake
test_executable.depends = Test.o Node.o Tree.o Complex.o
test_executable.commands = g++ -o test Test.o Node.o Tree.o Complex.o

QMAKE_EXTRA_TARGETS += test_executable

QMAKE_CLEAN += main test Demo.o Node.o Tree.o Screen.o Complex.o Test.o
