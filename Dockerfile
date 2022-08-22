FROM ubuntu:22.04

WORKDIR /krpc-fsw

# Copy over the dependencies folder, scripts, and source code
COPY deps /krpc-fsw/deps
COPY Makefile.fsw /krpc-fsw/Makefile
COPY main.cpp /krpc-fsw/main.cpp

# Get latest package information
RUN apt-get update -y

# Install ASIO, used by KRPC for network communication
RUN apt-get install -y libasio-dev

# Install Google Protobuf, used by KRPC for serialization
# Suggested by: https://grpc.io/docs/protoc-installation
RUN apt-get install -y libprotobuf-dev protobuf-compiler

# Unzip, build, and install KRPC (requires pkg-config)
# Download (working fork): https://github.com/nullprofile/krpc/releases/tag/0.4.9-1.12.1
RUN apt-get install -y pkg-config unzip
RUN unzip /krpc-fsw/deps/krpc-cpp-0.4.9.zip -d /krpc-fsw
RUN apt-get install -y gcc g++ make cmake unzip
RUN cd /krpc-fsw/krpc-cpp-0.4.9 \
    && cmake . \
    && make \
    && make install \
    && ldconfig

# Build and run the source code using the FSW makefile (Makefile.fsw)
RUN make

CMD make run
