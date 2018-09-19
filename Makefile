.PHONY: client
client:
	protoc --proto_path=protobuf \
		--cpp_out=src/protobuf \
		--grpc_out src/protobuf \
		--plugin=protoc-gen-grpc=`which grpc_cpp_plugin` \
		protobuf/faiss.proto

 .PHONY: pyclient
 pyclient:
	python -m grpc_tools.protoc --proto_path=protobuf \
		--python_out=python \
		--grpc_python_out=python \
		protobuf/faiss.proto

.PHONY: fmt
fmt:
	clang-format -style=Google -i src/*.h src/*.cpp

.PHONY: pyfmt
pyfmt:
	yapf -i example/indexing/*/py example/client/*.py
