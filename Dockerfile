FROM ubuntu:22.04

WORKDIR /krpc-fsw

# Get latest package information
RUN apt-get update -y

# Install ASIO, used by KRPC for network communication
RUN apt-get install -y libasio-dev

# Install Google Protobuf, used by KRPC for serialization
# Suggested by: https://grpc.io/docs/protoc-installation
RUN apt-get install -y libprotobuf-dev protobuf-compiler

# Install packages required to build and install KRPC
RUN apt-get install -y pkg-config unzip gcc g++ make cmake

# Copy over all source files and build scripts
COPY deps /krpc-fsw/deps
COPY fsw.mak /krpc-fsw/Makefile
COPY src /krpc-fsw/src
COPY include /krpc-fsw/include

# Unzip, build, and install KRPC (requires pkg-config)
# Download link (working fork): https://github.com/nullprofile/krpc/releases/tag/0.4.9-1.12.1
RUN unzip /krpc-fsw/deps/krpc-cpp-0.4.9.zip -d /krpc-fsw
RUN cd /krpc-fsw/krpc-cpp-0.4.9 \
    && cmake . \
    && make \
    && make install \
    && ldconfig

# Build and run the source code using the FSW makefile (Makefile.fsw)
RUN make
CMD make run
