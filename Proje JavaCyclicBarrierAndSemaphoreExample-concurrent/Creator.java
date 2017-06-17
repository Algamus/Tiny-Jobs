import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class Creator implements Runnable{
	int CreatorNumber;

	static int totalSum=0;
	int time;
	int number;
	Random randomGenerator = new Random();
	
	final static CyclicBarrier BarrierPhase1 = new CyclicBarrier( MainClass.NumberOfCreators);
	public static Semaphore SemephorePhase2 = new Semaphore(3, true);
	final static CyclicBarrier BarrierPhase3 = new CyclicBarrier( MainClass.NumberOfCreators);

	public Creator(int n) {
		CreatorNumber = n;
		System.out.println( "Creator " + n+" Created." );
	}

	public void run() {
		
		//phase1 start
		time=randomGenerator.nextInt(2)+2;// 2-4
		//System.out.println( "Thread" + CreatorNumber +" n: "+ time );
		try {
			BarrierPhase1.await();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		//phase1 end
		//phase2 start
		for(int i=0; i<time;i++){
			try {
				SemephorePhase2.acquire();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			number=randomGenerator.nextInt(11);//0-10
			//System.out.println( "Thread" + CreatorNumber +" add number: "+ number );
			totalSum+=number;
			SemephorePhase2.release();
		}
		//phase2 end
		//phase3 start
		try {
			BarrierPhase3.await();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println( "Thread" + CreatorNumber +" End. Total sum: "+ totalSum );
		
		//phase 3 end
		
	}
}
