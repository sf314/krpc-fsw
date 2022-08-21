#!/bin/bash
# This assumes that /krpc/deps contains both protobuf and KRPC

echo "Installing ASIO..."
apt-get install -y libasio-dev
echo "Successfully installed ASIO."

echo "Installing Protobuf..."
apt-get install -y libprotobuf-dev protobuf-compiler
echo "Check for protobuf executable: $(which protoc)"
echo "Successfully installed Protobuf."

echo "Installing KRPC and pkg-config"
apt-get install -y pkg-config
unzip /krpc-fsw/deps/krpc-cpp-0.4.9.zip -d /krpc-fsw
echo "Unpacked KRPC at /krpc-fsw/krpc-cpp-0.4.9"
ls krpc-cpp-0.4.9

cd /krpc-fsw/krpc-cpp-0.4.9
cmake .
make
make install
ldconfig
cd /krpc-fsw # Go back

echo "PATH: $PATH"

