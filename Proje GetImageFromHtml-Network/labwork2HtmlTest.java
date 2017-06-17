

import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class labwork2HtmlTest {
 
	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		



				String address;
				String hostName;
				String httpMessage;
				String path;
				String newSentence = "";
				int data;
				int i = 0;
				
				BufferedReader inFromUser= new BufferedReader( new InputStreamReader(System.in));
				System.out.print("Please enter the url address of the jpg ");
				address = inFromUser.readLine();
				
				if(!address.startsWith("http://")){
					address = "http://" + address;
				}
				
				URL url = new URL(address);
				hostName = url.getHost();
				path = url.getPath().isEmpty() ? "/" : url.getPath();
				httpMessage = "GET " + path +" HTTP/1.1\r\n" + "Host: " + hostName + "\r\n" + "Connection: close\r\n\r\n";
				
				Socket clientSocket= new Socket(hostName,80);
				
				DataInputStream inFromServer = new DataInputStream(clientSocket.getInputStream());
				
				DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
				
				System.out.print(httpMessage);
				outToServer.writeBytes(httpMessage);
				
				
				byte arr[] = new byte[150000];
				int count =0;
				
				while((data=inFromServer.read())!= -1){
					
					arr[count++] = (byte) data;
				}
				

				
				
			
				Pattern myPattern = Pattern.compile("Content-Length: [0-9]+");
				
				Matcher myMatcher = myPattern.matcher(new String(arr,0,count));
				
				String temp1 = null;
				
				while(myMatcher.find()){
					
					temp1=(new String(arr,0,count)).substring(myMatcher.start()  ,myMatcher.end());
				}
				
				clientSocket.close();
				
				int temp2=Integer.parseInt(temp1.substring(16));
				
				FileOutputStream file = new FileOutputStream("theimage.jpg");
				file.write(arr, (count-temp2), count);
				file.close();
				inFromServer.close();
				outToServer.close();
				
			}

		
	
	

}
