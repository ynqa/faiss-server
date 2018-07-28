# faiss-server

faiss-server provides gRPC services to for similarity search using [faiss](https://github.com/facebookresearch/faiss). It is written in C++ and now supports only CPU environments.

## Installation

Currently, installation is from source only.

```
$ git clone https://github.com/ynqa/faiss-server
$ cd faiss-server
```

To build faiss-server on your local, please use `cmake`.

```
$ mkdir build; cd build
$ cmake ..
$ make
```

[Beta] To build as docker image:

```
$ docker build -t faiss-server .
```

## Demo

1. Create indexed file, which is composed of the word vectors. Indexed words are on [text8](http://mattmahoney.net/dc/textdata) corpus and those vectors are trained by word2vec model of gensim.

```
$ python example/indexing/indexing.py
```

2. Select the indexed file and then execute faiss-server.
```
$ ./build/bin/faiss_server -file_path example/indexing/faiss.index
```

- If you build with docker:
  ```
  $ docker run -p 8080:8080 -v $(pwd)/example/indexing:/tmp faiss-server -file_path /tmp/faiss.index
  ```

3. Throw the requests for similarity search
```
$ PYTHONPATH=python python example/client/search.py
```

## Usage

```
faiss_server:
    -file_path (index file name) type: string default: ""
    -host (host of faiss server) type: string default: "0.0.0.0"
    -port (port of faiss server) type: string default: "8080"
    -top_k (default number of neighbor) type: uint64 default: 5
```
