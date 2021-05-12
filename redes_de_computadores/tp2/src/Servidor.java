import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.HashMap;

public class Servidor {

    public static void main(String[] args) throws IOException {

        //Check args length
        if (args.length != 1) {
            System.err.println("Incorrect number of parameters.");
            System.err.println("usage: java Servidor <server port> ");
            System.err.println("example: java Servidor 51511");
            return;
        }

        int port;
        try {
            port = Integer.parseInt(args[0]);
        } catch (Exception e) {
            System.err.println("Port parameter must be a integer");
            return;
        }

        ServerSocket ss = new ServerSocket(port);
        while (true) {
            Socket s = null;

            try {
                s = ss.accept();

                System.out.println("A new client is connected - " + s);

                DataInputStream dis = new DataInputStream(s.getInputStream());
                DataOutputStream dos = new DataOutputStream(s.getOutputStream());

                System.out.println("Creating thread for client");


                Thread t = new ClientHandler(s, dis, dos);
                t.start();

            }
            catch (Exception e){
                if (s != null) {
                    s.close();
                }
                System.err.println("Socket exception.");
            }
        }
    }
}

class ClientHandler extends Thread {

    public static int FILE_PAYLOAD_SIZE = 1000;
    public static int WINDOW_SIZE = 64;

    final Socket s;
    final DataInputStream dis;
    final DataOutputStream dos;

    public ClientHandler(Socket s, DataInputStream dis, DataOutputStream dos) {
        this.s = s;
        this.dis = dis;
        this.dos = dos;
    }

    @Override
    public void run() {

        int receivedMessageId = 0;

        String filename = "";
        long fileSize = 0;
        DatagramSocket ds = null;

        HashMap<Integer, byte[]> fileHashMap = new HashMap<>();

        while (receivedMessageId != 3) {

            try {

                byte[] receivedData = new byte[32];

                dis.read(receivedData, 0, receivedData.length);
                receivedMessageId = MessagesUtils.getInfo(receivedData, 2, 0, MessagesUtils.SHORT_CONSTANT);


                switch (receivedMessageId) {
                    case 1:
                        ds = new DatagramSocket();
                        int udpPort = ds.getLocalPort();
                        System.out.println("Hello message received. Assigning new UDP port this client - " + udpPort);
                        byte[] portInBytes = MessagesUtils.sendInfo(udpPort, MessagesUtils.INT_CONSTANT);
                        byte[] messageId = MessagesUtils.sendInfo(2, MessagesUtils.SHORT_CONSTANT);

                        byte[] header = new byte[messageId.length + portInBytes.length];
                        System.arraycopy(messageId, 0, header, 0, messageId.length);
                        System.arraycopy(portInBytes, 0, header, messageId.length, portInBytes.length);

                        dos.write(header);
                        break;
                    case 3:

                        byte[] bytesFilename = new byte[15];
                        System.arraycopy(receivedData, 2, bytesFilename, 0, 15);
                        filename = new String(bytesFilename, StandardCharsets.UTF_8);
                        fileSize = MessagesUtils.getInfo(receivedData, 8, 17, MessagesUtils.LONG_CONSTANT);

                        System.out.println("Received filename: " + filename + " - Size: " + fileSize + " bytes.");
                        System.out.println("Waiting file...");

                        dos.write(MessagesUtils.sendInfo(4, MessagesUtils.SHORT_CONSTANT));
                        break;
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

        try {

            String newFile = (filename.substring(0, filename.indexOf(".")) + "_received"
                            + filename.substring(filename.indexOf("."))).trim();
            File file = new File(newFile);
            FileOutputStream outToFile = new FileOutputStream(file);

            boolean isLastMessage = false;
            int lastPackage = -1;

            long totalPackages = Math.floorDiv(fileSize, FILE_PAYLOAD_SIZE);

            while (!isLastMessage) {
                byte[] message = new byte[FILE_PAYLOAD_SIZE + 8];
                byte[] fileByteArray = new byte[FILE_PAYLOAD_SIZE];

                DatagramPacket receivedPacket = new DatagramPacket(message, message.length);
                ds.receive(receivedPacket);
                message = receivedPacket.getData();

                int packageNumber = MessagesUtils.getInfo(message, 4, 2, MessagesUtils.INT_CONSTANT);
                int payloadSize = MessagesUtils.getInfo(message, 2, 6, MessagesUtils.SHORT_CONSTANT);

                System.arraycopy(message, 8, fileByteArray, 0, payloadSize);
                System.out.println("Received - sequence number = " + packageNumber + " - isLastMessage - = " + isLastMessage);

                if (packageNumber == (lastPackage + 1)) {
                    lastPackage = packageNumber;

                    outToFile.write(fileByteArray);
                    dos.write(MessagesUtils.sendAck(lastPackage));

                    int lsn = lastPackage;

                    for (int i = lsn + 1; i < lsn + WINDOW_SIZE && i < totalPackages; i++) {
                        if(fileHashMap.get(i) != null) {
                            outToFile.write(fileHashMap.get(i));
                            fileHashMap.remove(i);

                            dos.write(MessagesUtils.sendAck(packageNumber));
                            System.out.println("Sent ack - package number = " + lastPackage);

                            lastPackage = i;
                        } else
                            break;
                    }

                    if (packageNumber == totalPackages) {
                        byte[] endMessage = new byte[2];

                        byte[] messageId = MessagesUtils.sendInfo(5, MessagesUtils.SHORT_CONSTANT);
                        System.arraycopy(messageId, 0, endMessage, 0, messageId.length);

                        System.out.println("File completely received.");
                        System.out.println("Sending end message.");
                        isLastMessage = true;

                        dos.write(endMessage);
                        outToFile.close();
                    }

                } else {
                    byte[] header;

                    if (packageNumber < (lastPackage + 1))
                        header = MessagesUtils.sendAck(packageNumber);
                    else {
                        header = MessagesUtils.sendAck(lastPackage);
                        fileHashMap.put(packageNumber, fileByteArray);
                    }
                    dos.write(header);
                    System.out.println("Sent ack - package number = " + lastPackage);
                }
            }

            ds.close();
            System.out.println("Closing connection." + this.s);
            this.s.close();
            System.out.println("Connection closed");

        } catch (IOException e) {
            e.printStackTrace();
            return;
        }

        try {
            this.dis.close();
            this.dos.close();

        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}
