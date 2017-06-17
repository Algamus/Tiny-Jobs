
public class SumThreads extends Thread{
	
	private int StartPoint;
	final private int Length=500;
	private int sum;
	
	SumThreads(int s){
		StartPoint=s;
		sum=0;
	}
	public void run(){
		
		for(int i=0;i<Length;i++){
			sum=sum+(i+1+StartPoint);
		}
		
		try {
			MainClass.SemephoreUpdate.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		synchronized(this){
			MainClass.THESUM+=sum;
			
		}
		 MainClass.SemephoreUpdate.release();
		 
		 MainClass.Semephorethreads.release();
		 try {
			MainClass.SemephorePrint.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		 synchronized(this){
			 System.out.println( Thread.currentThread().getName() + " TheSum: " + MainClass.THESUM );
		 }
		 MainClass.SemephorePrint.release();
		
	}
}
