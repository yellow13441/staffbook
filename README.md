# **Staffbook**

a demo for gRPC and Protobuf beginners implemented by C++

## Enviroment

|          | Version |
| -------- | ------- |
| Ubuntu   | 20.04   |
| gRPC     | 1.45.0  |
| Protobuf | 3.19.4  |
| CMake    | 3.16.3  |

gRPC and Protobuf are installed with [Quick start | C++ | gRPC](https://grpc.io/docs/languages/cpp/quickstart/), thus the default install path is `$HOME/.local/gRPC`.

## Build and Install

Clone the `staffbook` repo and use `setup.sh` to build and install.

```bash
cd $HOME/.local

git clone https://github.com/yellow13441/staffbook

cd staffbook/cmake/build

./setup.sh
```

## Try

```bash
# start server side and use staffbook.data as protobuf db
./staffbook_server staffbook.data

# open another terminal to start the client side
./staffbook_client
```
