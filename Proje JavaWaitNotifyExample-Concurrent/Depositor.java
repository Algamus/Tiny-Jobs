import java.util.Random;

public class Depositor implements Runnable{
	int DepositorNumber;
	
	Random randomGenerator = new Random();
	int x;
	
	public Depositor(int n) {
		DepositorNumber = n;
		System.out.println( "Depositor" + n+" Created." );
	}

	public void run() {
		while(true){
			x=randomGenerator.nextInt(MainClass.NumberOfAccount);
			MainClass.Accounts[x].deposit();
		}
	}
}
