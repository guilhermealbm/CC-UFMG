import java.nio.ByteBuffer;

public class MessagesUtils {

    public static final String SHORT_CONSTANT = "SHORT_CONSTANT";
    public static final String INT_CONSTANT = "INT_CONSTANT";
    public static final String LONG_CONSTANT = "LONG_CONSTANT";

    public static int getInfo(byte[] receivedData, int size, int srcOffset, String constantType) {

        byte[] messageBytes = new byte[size];
        System.arraycopy(receivedData, srcOffset, messageBytes, 0, size);
        return constantType.equals(SHORT_CONSTANT)
                ? ByteBuffer.wrap(messageBytes).getShort()
                : constantType.equals(INT_CONSTANT)
                ? ByteBuffer.wrap(messageBytes).getInt()
                : (int) ByteBuffer.wrap(messageBytes).getLong();

    }

    public static byte[] sendInfo(long number, String constantType) {

        return constantType.equals(SHORT_CONSTANT)
                ? ByteBuffer.allocate(2).putShort((short) number).array()
                : constantType.equals(INT_CONSTANT)
                ? ByteBuffer.allocate(4).putInt((int) number).array()
                : ByteBuffer.allocate(8).putLong(number).array();

    }

    public static byte[] generateHeaderMessageType3(byte[] messageId, byte[] fileSize, byte[] filename) {
        byte[] header = new byte[messageId.length + filename.length + fileSize.length];
        System.arraycopy(messageId, 0, header, 0, messageId.length);
        System.arraycopy(filename, 0, header, messageId.length, filename.length);
        System.arraycopy(fileSize, 0, header, messageId.length + filename.length,
                fileSize.length);

        return header;

    }

    public static byte[] sendAck(int packageNumber) {
        byte[] header = new byte[6];
        byte[] messageId = MessagesUtils.sendInfo(7, MessagesUtils.SHORT_CONSTANT);
        byte[] portInBytes = MessagesUtils.sendInfo(packageNumber, MessagesUtils.INT_CONSTANT);
        System.arraycopy(messageId, 0, header, 0, 2);
        System.arraycopy(portInBytes, 0, header, 2, 4);
        return header;
    }
}
