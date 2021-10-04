from concurrent import futures

import grpc
import hello_pb2, hello_pb2_grpc
import sys

dicionario = {}
server = None


class Insere(hello_pb2_grpc.InsereServicer):

    def insere(self, request, context):

        if request.ch not in dicionario.keys():
            dicionario[request.ch] = [request.desc, request.val]
            return hello_pb2.InsereRes(val=0)
        else:
            return hello_pb2.InsereRes(val=-1)


class Consulta(hello_pb2_grpc.ConsultaServicer):

    def consulta(self, request, context):

        if request.ch not in dicionario.keys():
            return hello_pb2.ConsultaRes(desc="", val=-1)
        else:
            desc, val = dicionario[request.ch]
            return hello_pb2.ConsultaRes(desc=desc, val=val)


class Termina(hello_pb2_grpc.TerminaServicer):

    def termina(self, request, context):

        server.stop(3)
        return hello_pb2.TerminaRes(val=0)


def serve():
    global server
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))

    hello_pb2_grpc.add_InsereServicer_to_server(Insere(), server)
    hello_pb2_grpc.add_ConsultaServicer_to_server(Consulta(), server)
    hello_pb2_grpc.add_TerminaServicer_to_server(Termina(), server)

    server.add_insecure_port("localhost:" + sys.argv[1])
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    serve()
