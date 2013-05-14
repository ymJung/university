class MyRunnable implements Runnable{
	String myName;
	
	public MyRunnable(String name){
		myName = name;
	}
	public void run(){
		for(int i=0;i<10;i++){
			System.out.println(myName +i);
		}
	}
}
public class TestThread1 {
	public static void main(String[] args){
		Thread t1= new Thread(new MyRunnable("First "));
		Thread t2= new Thread(new MyRunnable("Second "));
		t1.start();
		
		t2.start();
	}

}
