run_cli_arm:
	python -m grpc_tools.protoc --proto_path=. ./hello.proto --python_out=. --grpc_python_out=.
	python cliente.py $(arg)


run_serv_arm:
	python -m grpc_tools.protoc --proto_path=. ./hello.proto --python_out=. --grpc_python_out=.
	python servidor.py $(arg)


clean:
	rm hello_pb2.py hello_pb2_grpc.py
