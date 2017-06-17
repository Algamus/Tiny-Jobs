import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;


public class lab7 {

	
	public static void main(String[] args) throws Exception{
		
		
		DatagramSocket clientSocket = new DatagramSocket();
		InetAddress IPAddress = InetAddress.getByName("255.255.255.255");
		clientSocket.setBroadcast(true);
		byte[] sendData = new byte[1024];
		byte[] receiveData = new byte[1024];
		
		
		String sentence = "UDP_SERVER_SEARCH_REQUEST";
		String answeringsentence = "UDP_SERVER_FOUND";
		
		InetAddress serverIP;
		
		sendData = sentence.getBytes();
		
		DatagramPacket sendPacket = new DatagramPacket(sendData,sendData.length,IPAddress,8888);
		clientSocket.send(sendPacket);
		while(true){
			DatagramPacket receivePacket = new DatagramPacket(receiveData,receiveData.length);
			clientSocket.receive(receivePacket);
			String modifiedSentence = new String(receivePacket.getData(),0,receivePacket.getLength());
			System.out.println("From Server: " + modifiedSentence);
			if(modifiedSentence.matches(answeringsentence)){
				serverIP=receivePacket.getAddress();
				System.out.println("Server IP: " + serverIP.toString());
				break;
			}
		}
		clientSocket.close();
		
		Thread thread1 = new Thread(new TheThread(serverIP));
		Thread thread2 = new Thread(new TheThread(serverIP));
		thread1.start();
		thread2.start();
		
		
		
	}

}
