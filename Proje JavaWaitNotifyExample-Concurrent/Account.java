
public class Account{
	int accountNumber;
	int amount=0;;
	final static int maxAmount= 100;
	
	public Account(int n) {
		accountNumber = n;
		amount=100;
		System.out.println( "Account" + n + " created; amount: " + amount );
	}
	
	public synchronized void deposit(){
		if(amount>=maxAmount){
			try {
				this.wait();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		amount++;
		
	}
	
	public synchronized void withdraw(){
		amount--;
		this.notify();
	}
	
	
}
