
public class MainClass {
	final static int NumberOfAccount=3;
	final static int NumberOfDepositor=2;
	final static int NumberOfWithdrawers=3;
	
	static Account[] Accounts = new Account[ NumberOfAccount ];
	
	@SuppressWarnings("deprecation")
	public static void main(String[] args) {		
		
		Thread[] Depositors = new Thread[ NumberOfDepositor ];
		Thread[] Withdrawers = new Thread[ NumberOfWithdrawers ];
		
		
		for( int i=0; i<NumberOfAccount; i++ ){
			Accounts[ i ] = new Account( i+1 );
		}
		
		for( int i=0; i< NumberOfDepositor; i++ ){
			Depositors[ i ] = new Thread( new Depositor( i+1 ), "Depositor_" + (i+1) );
			Depositors[ i ].start();
		}
		for( int i=0; i< NumberOfWithdrawers; i++ ){
			Withdrawers[ i ] = new Thread( new Withdrawer( i+1 ), "Withdrawer_" + (i+1) );
			Withdrawers[ i ].start();
		}
		
		for( int i=0; i< NumberOfWithdrawers; i++ ){
			try {
				Withdrawers[ i ].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		for( int i=0; i< NumberOfDepositor; i++ ){
			Depositors[ i ].stop();
		}
		
		System.out.println( "Done." );
		
	}
}
