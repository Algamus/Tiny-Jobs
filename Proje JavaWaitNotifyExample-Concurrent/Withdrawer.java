import java.util.Random;

public class Withdrawer implements Runnable{
	int WithdrawerNumber;
	
	Random randomGenerator = new Random();
	
	int x;
	int withdrawerMoney;
	boolean flag;
	
	public Withdrawer(int n) {
		WithdrawerNumber = n;
		withdrawerMoney=0;
		flag=true;
		System.out.println( "Withdrawer" + n+" Created." );
	}

	public void run() {
		while(flag){
			x=randomGenerator.nextInt(MainClass.NumberOfAccount);
			MainClass.Accounts[x].withdraw();
			withdrawerMoney++;
			if(withdrawerMoney>=10){
				flag=false;
			}
		}
	}
}