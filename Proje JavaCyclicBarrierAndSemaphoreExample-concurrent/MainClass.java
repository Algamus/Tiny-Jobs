
public class MainClass {
	final static int NumberOfCreators=6;

	public static void main(String[] args) {	
		
		Thread[] Creators = new Thread[ NumberOfCreators ];
		
		for( int i=0; i< NumberOfCreators; i++ ){
			Creators[ i ] = new Thread( new Creator( i+1 ), "Creator_" + (i+1) );
			Creators[ i ].start();
		}
	}
}
