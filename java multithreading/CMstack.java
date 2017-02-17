
public class CMstack {
	public static final int MaxBufSize = 99;
	public static final int MinBufSize = 0;
	int stack[] = new int[MaxBufSize + 1];
	int ind = 0;
	boolean IsEmpty = ind == MinBufSize;
	boolean IsFull = ind == MaxBufSize;

	CMstack() {
		for (int i = MinBufSize; i < MaxBufSize / 2; i++) {
			stack[i] = i;
			ind++;
		}
		System.out.println("\nStack with " + ind + " elements created\n"); 
	}

	synchronized void push() {
		while (IsFull)
			try {
				wait();
			} catch (InterruptedException e) {
				System.out.println("InterruptedException");
			}

		System.out.println("+++ ind: " + ind++ + " => " + ind);
		stack[ind] = ind;
		System.out.println("+++ stack[" + ind + "] = " + stack[ind]);
		System.out.println();

		IsFull = ind == MaxBufSize;
		IsEmpty = false;

		notify();
	}
	
	synchronized void pop() {
		while (IsEmpty)
			try {
				wait();
			} catch (InterruptedException e) {
				System.out.println("InterruptedException");
			}

		System.out.println("--- stack[" + ind + "] = " + stack[ind]);
		stack[ind] = 0;
		System.out.println("--- ind: " + ind-- + " => " + ind);
		System.out.println();

		IsEmpty = ind == MinBufSize;
		IsFull = false;

		notify();
	}
}
