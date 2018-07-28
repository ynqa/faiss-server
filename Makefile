.PHONY: pyclient
pyclient:
	python -m grpc.tools.protoc --proto_path=protobuf --python_out=python --grpc_python_out=python ./protobuf/faiss.proto

.PHONY: fmt
fmt:
	clang-format -style=Google -i src/*.h src/*.cpp
