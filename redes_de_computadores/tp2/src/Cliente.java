import java.io.*;
import java.net.*;
import java.util.Vector;

public class Cliente {

    public static int FILE_PAYLOAD_SIZE = 1000;
    public static int WINDOW_SIZE = 64;
    public static int TIMEOUT = 100;

    public static void main(String[] args) {

        //Check args length
        if (args.length != 3) {
            System.err.println("Incorrect number of parameters.");
            System.err.println("usage: java Cliente <server IP> <server port> <file>");
            System.err.println("example: java Cliente 127.0.0.1 51511 arquivo.jpg");
            return;
        }

        String ipNumber = args[0];
        String filename = args[2];

        int count = filename.length() - filename.replace(".", "").length();
        boolean ascii = filename.matches("\\A\\p{ASCII}*\\z");
        if (count != 1 || filename.getBytes().length > 15 || filename.substring(filename.indexOf(".") + 1).length() > 3 || !ascii) {
            System.err.println("Nome não permitido");
            return;
        }

        int port;
        try {
            port = Integer.parseInt(args[1]);
        } catch (Exception e) {
            System.err.println("Port parameter must be a integer");
            return;
        }

        // Connection
        try {

            InetAddress ip = InetAddress.getByName(ipNumber);
            Socket s = new Socket(ip, port);

            int receivedMessageId = 0;
            DataInputStream dis = new DataInputStream(s.getInputStream());
            DataOutputStream dos = new DataOutputStream(s.getOutputStream());
            byte[] receivedData = new byte[32];

            DatagramSocket ds = new DatagramSocket();
            File file = new File(filename);

            InputStream fileInputStream = new FileInputStream(file);
            byte[] fileByteArray = new byte[(int)file.length()];
            fileInputStream.read(fileByteArray);

            //Send hello message
            byte[] header = MessagesUtils.sendInfo(1, MessagesUtils.SHORT_CONSTANT);
            dos.write(header);

            int udpPort = 0;


            while (receivedMessageId != 4) {

                //Read server message
                dis.read(receivedData, 0, receivedData.length);
                receivedMessageId = MessagesUtils.getInfo(receivedData, 2, 0, MessagesUtils.SHORT_CONSTANT);


                switch (receivedMessageId) {
                    case 2:

                        udpPort = MessagesUtils.getInfo(receivedData, 4, 2, MessagesUtils.INT_CONSTANT);
                        System.out.println("UDP port received - " + udpPort);

                        byte[] bytesFilename = new byte[15];
                        System.arraycopy(filename.getBytes(), 0, bytesFilename, 0, filename.getBytes().length);

                        byte[] messageId = MessagesUtils.sendInfo(3, MessagesUtils.SHORT_CONSTANT);
                        byte[] fileSize = MessagesUtils.sendInfo(file.length(), MessagesUtils.LONG_CONSTANT);

                        header = MessagesUtils.generateHeaderMessageType3(messageId, fileSize, bytesFilename);
                        dos.write(header);
                        break;

                    case 4:
                        System.out.println("OK message received. Sending file");
                        break;
                }
            }


            Thread.sleep(50); //Evita condição de corrida

            boolean endExecution = false;
            boolean reSend = false;

            int lastAckedPackageNumber = -1;
            int ackPackageNumber = -1;

            int retransmissionCounter = 0;
            Vector <byte[]> sentMessages = new Vector<>();

            long totalPackages = Math.floorDiv(fileByteArray.length, FILE_PAYLOAD_SIZE);

            int i = 0;
            int packageNumber = 0;
            while (!endExecution) {

                byte[] message = new byte[1008];

                if(packageNumber <= totalPackages) {
                    if (packageNumber < sentMessages.size()) {
                        message = sentMessages.get(packageNumber);
                        reSend = false;
                    } else {
                        byte[] messageId = MessagesUtils.sendInfo(6, MessagesUtils.SHORT_CONSTANT);
                        byte[] bytesPackageNumber = MessagesUtils.sendInfo(packageNumber, MessagesUtils.INT_CONSTANT);
                        byte[] bytesPayloadSize;

                        if (i + FILE_PAYLOAD_SIZE >= fileByteArray.length) {
                            bytesPayloadSize = MessagesUtils.sendInfo(fileByteArray.length - i, MessagesUtils.SHORT_CONSTANT);
                            System.arraycopy(fileByteArray, i, message, 8, fileByteArray.length - i);
                        } else {
                            bytesPayloadSize = MessagesUtils.sendInfo(FILE_PAYLOAD_SIZE, MessagesUtils.SHORT_CONSTANT);
                            System.arraycopy(fileByteArray, i, message, 8, FILE_PAYLOAD_SIZE);
                        }

                        System.arraycopy(messageId, 0, message, 0, 2);
                        System.arraycopy(bytesPackageNumber, 0, message, 2, 4);
                        System.arraycopy(bytesPayloadSize, 0, message, 6, 2);

                        sentMessages.add(message);
                    }

                    i += FILE_PAYLOAD_SIZE;

                }

                DatagramPacket sendPacket = new DatagramPacket(message, message.length, ip, udpPort);


                while (true) {
                    if ((packageNumber - WINDOW_SIZE) > lastAckedPackageNumber) {

                        boolean ackPacketReceived, ackReceivedCorrect = false;

                        while (!ackReceivedCorrect) {

                            try {
                                s.setSoTimeout(TIMEOUT);
                                dis.read(receivedData, 0, 6);
                                ackPackageNumber = MessagesUtils.getInfo(receivedData, 4, 2, MessagesUtils.INT_CONSTANT);
                                ackPacketReceived = true;
                            } catch (SocketTimeoutException e) {
                                ackPacketReceived = false;
                            }

                            if (ackPacketReceived) {
                                if (ackPackageNumber >= (lastAckedPackageNumber + 1))
                                    lastAckedPackageNumber = ackPackageNumber;

                                ackReceivedCorrect = true;
                                System.out.println("Ack received - package number = " + ackPackageNumber);
                            } else {
                                i = (lastAckedPackageNumber + 1) * FILE_PAYLOAD_SIZE;
                                packageNumber = lastAckedPackageNumber;
                                reSend = true;
                                retransmissionCounter++;
                                System.out.println("Resending from packet " + (packageNumber + 1));
                                break;
                            }
                        }
                    } else {
                        break;
                    }
                }

                if(!reSend && packageNumber <= totalPackages) {
                    ds.send(sendPacket);
                    System.out.println("Sent - package number = " + packageNumber);
                }

                while (true) {

                    try {
                        s.setSoTimeout(TIMEOUT);
                        int messageBytes = dis.read(receivedData, 0, 6);
                        int messageType = MessagesUtils.getInfo(receivedData, 2, 0, MessagesUtils.SHORT_CONSTANT);
                        ackPackageNumber = MessagesUtils.getInfo(receivedData, 4, 2, MessagesUtils.INT_CONSTANT);

                        if (messageType == 5) {
                            endExecution = true;
                            break;
                        }

                        if(messageBytes <= 0)
                            break;
                    } catch (SocketTimeoutException e) {
                        break;
                    }

                    if (ackPackageNumber >= (lastAckedPackageNumber + 1)) {
                        lastAckedPackageNumber = ackPackageNumber;
                        System.out.println("Ack received - package number = " + ackPackageNumber);
                    }
                }

                packageNumber += 1;

            }

            System.out.println("Retransmission counter - " + retransmissionCounter);

            System.out.println("Closing connection - " + s);
            s.close();
            System.out.println("Closed");

            dis.close();
            dos.close();
        } catch(UnknownHostException e) {
            System.err.println("Error with inserted IP (UnknownHostException).");
        } catch (FileNotFoundException e) {
            System.err.println("Error with inserted File (FileNotFoundException).");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
