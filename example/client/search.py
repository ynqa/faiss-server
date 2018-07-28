import argparse
import grpc
import numpy as np
import faiss_pb2
import faiss_pb2_grpc


def main(args):
    # create channel and stub
    address = '{}:{}'.format(args.host, args.port)
    channel = grpc.insecure_channel(address)
    stub = faiss_pb2_grpc.FaissServiceStub(channel)

    request = faiss_pb2.SearchRequest()
    request.top_k = args.top_k
    arr = np.random.rand(1, 100)[0]
    request.vector.float_val.extend(arr)
    response = stub.Search.future(request, args.timeout)
    print(response.result())


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--host',
        type=str,
        default='localhost',
        help='host of faiss server (default: localhost)')
    parser.add_argument(
        '--port',
        type=int,
        default=8080,
        help='port of faiss server (default: 8080)')
    parser.add_argument(
        '--timeout',
        type=float,
        default=1,
        help=
        'a duration of second to respond from tensorflow serving (default: 1)')
    parser.add_argument(
        '--top_k',
        type=int,
        default=5,
        help='number of neighbor for similarity search')
    main(parser.parse_args())
