import java.util.Random;

class Horse implements Runnable{
	String name;
	private int sleepTime;
	private final static Random generator = new Random();
	
	public Horse(String name){
		this.name = name;
		sleepTime = generator.nextInt(3000); //3000이내 난수를 매개로 sleepTime지정
	}
	
	public void run(){
		try{
			Thread.sleep(sleepTime);
		}catch (InterruptedException e){
	}
		System.out.println(name+ " 말이 도착.");
	}
}

public class TestThread2{
	public static void main(String args[]){
		Thread t1 = new Thread(new Horse("1번마"));
		Thread t2 = new Thread(new Horse("2번마"));
		Thread t3 = new Thread(new Horse("3번마"));
		Thread t4 = new Thread(new Horse("4번마"));
		
		t1.start();
		t2.start();
		t3.start();
		t4.start();
		
	}
	
}
