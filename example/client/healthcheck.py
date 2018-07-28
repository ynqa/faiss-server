import argparse
import grpc
import faiss_pb2
import faiss_pb2_grpc


def main(args):
    # create channel and stub
    address = '{}:{}'.format(args.host, args.port)
    channel = grpc.insecure_channel(address)
    stub = faiss_pb2_grpc.FaissServiceStub(channel)
    response = stub.HealthCheck.future(faiss_pb2.HealthCheckRequest(),
                                       args.timeout)
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
    main(parser.parse_args())
