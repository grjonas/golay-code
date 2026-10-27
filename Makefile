FILES   = \
	main.cpp \
	dependencies.cpp \
	binary.cpp \
	golay.cpp

OPTIONS = \
	-g \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-std=c++17

EXEC = main

build:
	g++ \
	$(FILES) \
	$(OPTIONS) \
	-o $(EXEC)
