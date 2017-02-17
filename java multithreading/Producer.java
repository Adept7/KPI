import java.util.concurrent.BrokenBarrierException;

public class Producer implements Runnable {
	
	int num;
	Thread t;
	CMstack CR1;
	CMvar CR2;
	
	Producer (int p_num, CMstack s, CMvar v) {
		num = p_num;
		this.CR1 = s;
		this.CR2 = v;
		System.out.println("Producer " + num + " started");
		t = new Thread (this, "Producer:" + p_num);
		t.start();
	}
	
	public void run() {		
		while (true)	{
			
			if (num == 3){//with access to CR2
				try {
					System.out.format("Thread %d wait CB1.\n", num);
					L5.CB1.await();
				} catch (InterruptedException | BrokenBarrierException e) {
					e.printStackTrace();
				}
				
				try {
					System.out.format("Thread %d wait CB1.\n", num);
					L5.CB2.await();
				} catch (InterruptedException | BrokenBarrierException e) {
					e.printStackTrace();
				}
				
				L5.Mutex.lock();
				System.out.format("Thread %d lock mutex.\n", num);
				CR2.setVar(num);
				System.out.format("Thread %d unlock mutex.\n", num);
				L5.Mutex.unlock();
			}
			
			if (num == 5){
				//Semaphore synchronization
					try {
						System.out.println("Thread " + num + " release Sem1\n");
						L5.Sem1.release();
						System.out.println("Thread " + num + " waiting Sem2\n");
						L5.Sem2.acquire();
						System.out.println("Thread " + num + " check Sem1\n");
					} catch (InterruptedException e) {
						System.out.println("Interrupted exception");						
					}
						CR1.push();						
			}
			
			
		}
	}
}