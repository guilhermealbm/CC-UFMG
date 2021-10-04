import grpc
import hello_pb2, hello_pb2_grpc
import sys
import os


def run():
    channel = grpc.insecure_channel(sys.argv[1])
    stubInsere = hello_pb2_grpc.InsereStub(channel)
    stubConsulta = hello_pb2_grpc.ConsultaStub(channel)
    stubTermina = hello_pb2_grpc.TerminaStub(channel)

    my_pid = os.getpid()

    while True:
        message = input()

        if message[0] == 'I':
            option, ch, desc, val = message.split(",")
            response = stubInsere.insere(hello_pb2.InsereReq(ch=int(ch), desc=desc, val=int(val)))
            print(response.val)

        if message[0] == 'C':
            option, ch = message.split(",")
            response = stubConsulta.consulta(hello_pb2.ConsultaReq(ch=int(ch)))
            if response.val == -1:
                print(response.val)
            else:
                print(response.desc + "," + str(response.val))

        if message[0] == 'T':
            response = stubTermina.termina(hello_pb2.TerminaReq())
            print(response.val)
            channel.close()
            return


if __name__ == '__main__':
    run()
