# This Makefile is intended for use on the host development system, i.e. macOS.
# It is assumed that Docker will be used to build and run the FSW.

.PHONY: all no-cache run

DOCKER_IMAGE_NAME := krpc_krpc-fsw

# VERBOSE_FLAG := --progress=plain

# The default make target will build a fresh image as defined in the provided
# Dockerfile, using the Docker cache as necessary.
# Note: Uncomment VERBOSE_FLAG for more logs, this is helpful for debugging
# any compilation errors.
all:
	docker build . $(VERBOSE_FLAG)

# Build a fresh image as defined by the provided Dockerfile, but do not use any
# cached intermediate containers. This results in the freshest build.
no-cache:
	docker build . --no-cache

# Start the FSW in a container using the latest built image. (not docker-compose up)
run:
	docker run krpc_krpc-fsw

# Remove all stopped containers, and delete the FSW image by name.
# Note: this prunes *all* stopped containers, including containers for other
# projects.
clean:
	docker container prune
	docker image rm $(DOCKER_IMAGE_NAME)
