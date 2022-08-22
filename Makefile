# This Makefile is intended for use on both the host development system, i.e.
# macOS, as well as from within a ubuntu:22.04 Docker container. Any make
# commands prefixed with `docker` are meant to be run from macOS, in order to
# perform docker commands.

LOCAL_TGTS := docker-build docker-run
LINUX_TGTS := all run
.PHONY: $(LOCAL_TGTS) $(LINUX_TGTS)

SOURCES = \
	main.cpp

FLAGS = \
	-std=c++11 \
	-Wall \
	-Werror

LINKER_ARGS = \
	-lkrpc \
	-lprotobuf

EXEC = krpc-fsw

##### PROJECT BUILD: RUN WITHIN CONTAINERIZED ENVIRONMENT

all:
	g++ main.cpp -std=c++11 -lkrpc -lprotobuf 
	g++ $(FLAGS) $(SOURCES) -o $(EXEC) $(LINKER_ARGS)

run:
	./$(EXEC)

##### CONTAINER BUILD: RUN FROM HOST SYSTEM

docker-build:
	docker build . --progress=plain

docker-run:
	docker-compose up --build
