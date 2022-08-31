# This Makefile is intended for use from within the Ubuntu container described
# in the provided Dockerfile. It's sole purpose is to compile and run the FSW
# assuming that all the dependencies have been installed properly.
#
# When developing the FSW, this Makefile shoulud be updated if any source files
# are added or updated.

.PHONY: all run

INCLUDES = \
	-Iinclude

SOURCES = \
	src/main.cpp

FLAGS = \
	-std=c++11 \
	-Wall \
	-Werror

LIBS = \
	-lkrpc \
	-lprotobuf

EXEC = krpc-fsw

all:
	g++ $(FLAGS) $(SOURCES) -o $(EXEC) $(LIBS)

run:
	./$(EXEC)
