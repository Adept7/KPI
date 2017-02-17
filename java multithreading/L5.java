import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.ReentrantLock;

public class L5 {	
	
	public static ReentrantLock Mutex = new ReentrantLock();
	public static Semaphore Sem1 = new Semaphore(0);
	public static Semaphore Sem2 = new Semaphore(0);
	public static CyclicBarrier CB1 = new CyclicBarrier(2);
	public static CyclicBarrier CB2 = new CyclicBarrier(2);
	
	public static void main(String[] args) {
		
		
		
		CMstack CR1 = new CMstack();
		CMvar CR2 = new CMvar();
		
		Consumer P1 = new Consumer(1, CR1, CR2);
		Consumer P2 = new Consumer(2, CR1, CR2);
		Producer P3 = new Producer(3, CR1, CR2);
		Consumer P4 = new Consumer(4, CR1, CR2);
		Producer P5 = new Producer(5, CR1, CR2);
		
		try
		 {
			 /* Очікується завершення потоків. */
			 P1.t.join();
			 P2.t.join();
			 P3.t.join();
			 P4.t.join();
			 P5.t.join();
		 }catch(InterruptedException e)
		 	{
			 	System.out.println(e.getMessage());
		 	}

		 System.out.println("\nMain finished"); 
	}

}
