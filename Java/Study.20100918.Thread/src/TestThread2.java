import java.util.Random;

class Horse implements Runnable{
	String name;
	private int sleepTime;
	private final static Random generator = new Random();
	
	public Horse(String name){
		this.name = name;
		sleepTime = generator.nextInt(3000); //3000�̳� ������ �Ű��� sleepTime����
	}
	
	public void run(){
		try{
			Thread.sleep(sleepTime);
		}catch (InterruptedException e){
	}
		System.out.println(name+ " ���� ����.");
	}
}

public class TestThread2{
	public static void main(String args[]){
		Thread t1 = new Thread(new Horse("1����"));
		Thread t2 = new Thread(new Horse("2����"));
		Thread t3 = new Thread(new Horse("3����"));
		Thread t4 = new Thread(new Horse("4����"));
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		
	}
	
}
