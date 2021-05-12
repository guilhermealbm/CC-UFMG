Para executar o programa, primeiramente, navegue até a pasta src

cd src

Em seguida, você pode:
1) Executar via .jar, com o seguinte comando:
java -jar Servidor.jar 51511
java -jar Cliente.jar 127.0.0.1 51511 arquivo.jpg

2) Compilar os arquivos .java, transformando-os em .class (por via das dúvidas, também zipei os arquivos .class, caso o javac não esteja disponível):
javac *.java -d .

Execute:

java Servidor 51511
java Cliente 127.0.0.1 51511 arquivo.jpg

Obrigado :)