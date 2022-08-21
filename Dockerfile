FROM ubuntu:22.04

WORKDIR /krpc-fsw

# Update apt and get required base deps
RUN apt-get update -y
RUN apt-get install -y gcc g++ make cmake unzip

# Copy over the dependencies folder, for checked-in src deps
COPY deps /krpc-fsw/deps
COPY main.cpp /krpc-fsw/main.cpp

COPY install.sh install.sh
RUN ./install.sh

RUN g++ main.cpp -std=c++11 -lkrpc -lprotobuf

CMD ./a.out


# Install ASIO, a header-only library for network communications
# RUN apt-get install -y libasio-dev

# Install Google Protobuf, used for serialization
# Direct download: https://github.com/protocolbuffers/protobuf/releases (protoc-21.5-linux-x86_64.zim)
# Instructions: https://grpc.io/docs/protoc-installation/
# RUN cp /krpc-fsw/deps/protoc-21/bin/protoc /usr/local/bin && chmod +x /usr/local/bin/protoc && chmod +x /krpc-fsw/deps/protoc-21/bin/protoc
# RUN cp -r /krpc-fsw/deps/protoc-21/include/google /usr/local/include
# ENV PATH="${PATH}:/krpc-fsw/deps/protoc-21/bin"
# Alt: Compile from source: https://github.com/protocolbuffers/protobuf/blob/main/src/README.md
# RUN apt-get install -y libprotobuf-dev protobuf-compiler

# Check
# RUN echo $PATH

# Install KRPC from the provided ZIP file and cmake
# Instructions: https://krpc.github.io/krpc/cpp/client.html#using-cmake
# RUN apt-get install -y pkg-config
# RUN unzip /krpc-fsw/deps/krpc-cpp-0.4.8.zip -d /krpc-fsw
# RUN cd /krpc-fsw/krpc-cpp-0.4.8 && ./configure && make && make install && ldconfig

# Build and run the main code
# RUN g++ main.cpp -std=c++11 -lkrpc -lprotobuf
