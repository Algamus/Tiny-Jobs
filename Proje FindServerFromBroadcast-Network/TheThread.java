import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Random;


public class TheThread extends Thread{

	int sleepTime= 500;
	
	
	
	
	
	
	
	int data;
	String dataSentence;
	int port;
	DatagramSocket clientSocket;
	InetAddress IPAddress;
	DatagramPacket sendPacket;
	Random rnd;
	
	
	byte[] sendData ;
	
	
	TheThread (InetAddress IP) throws IOException{
			
		IPAddress=IP;
		port=9999;
		sendData = new byte[1024];
		clientSocket = new DatagramSocket();
		rnd = new Random();
		data=rnd.nextInt(1000);
		dataSentence = Integer.toString(data);
			
	}
	
    public void run (){
    	if(sleepTime>0){
    		try {
				sleep(sleepTime);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
    	}
		
		try {
			sendData = dataSentence.getBytes();
			sendPacket = new DatagramPacket(sendData,sendData.length,IPAddress,port);
			clientSocket.send(sendPacket);
			
			
	
			System.out.println("To Server: " + dataSentence);
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
}

	
}
