FROM nvidia/cuda:8.0-devel-ubuntu16.04

RUN apt-get update -y && \
    apt-get install -y \
    curl libssl-dev libopenblas-dev python-numpy python-dev swig git python-pip wget
ENV BLASLDFLAGS /usr/lib/libopenblas.so.0

# cmake
RUN curl https://cmake.org/files/v3.11/cmake-3.11.4-Linux-x86_64.sh -o /tmp/curl-install.sh \
      && chmod u+x /tmp/curl-install.sh \
      && mkdir /usr/bin/cmake \
      && /tmp/curl-install.sh --skip-license --prefix=/usr/bin/cmake \
      && rm /tmp/curl-install.sh
ENV PATH="/usr/bin/cmake/bin:${PATH}"

WORKDIR /builder
COPY . .
RUN mkdir build

WORKDIR /builder/build
RUN cmake ..
RUN make

ENTRYPOINT ["/builder/build/bin/faiss_server"]
CMD ["--help"]
