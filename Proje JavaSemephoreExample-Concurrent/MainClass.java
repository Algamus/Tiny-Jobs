import java.util.concurrent.Semaphore;

public class MainClass {
	final static int numSumThread = 3;
	public static Semaphore Semephorethreads = new Semaphore(0, true);
	public static Semaphore SemephoreUpdate = new Semaphore(1, true);
	public static Semaphore SemephorePrint = new Semaphore(0, true);
	public static int THESUM=0;
	
	public static void main(String[] args) {		
			
		Thread[] Summers = new Thread[ numSumThread ];
		
		for( int i=0; i<numSumThread; i++ ){
			Summers[ i ] = new Thread( new SumThreads( i*500 ), "Summer_" + i );
			Summers[ i ].start();
		}
		try {
			Semephorethreads.acquire();
			Semephorethreads.acquire();
			Semephorethreads.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		SemephorePrint.release();

	}
}
