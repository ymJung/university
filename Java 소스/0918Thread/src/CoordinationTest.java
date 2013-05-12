class Buffer{
	//wait() notify 사용
	private int data;
	private boolean empty = true;
	
	public synchronized int get(){
		while(empty){
			try{
				wait(); // 미 생산시 wait 호출
			}catch(InterruptedException e){
			}
		}
		empty = true; //소비
		notifyAll(); //소비되었음을 알림
		return data;
	}
	public synchronized void put(int data){
		//소비할때까지 wait()호출
		while(!empty){
			try{
				wait();
			}catch(InterruptedException e){
			}
		}
		//생산되었음을 표시
		empty = false; //생산되었다는 표시
		this.data = data; //케익을 저장
		notifyAll(); // 생산되었음을 알림
		
	}
	
	/*private int data; 
	public synchronized int get(){
		return data;
	}
	public synchronized void put(int d){
		data = d;
	}*/
}
class Producer extends Thread{
	private Buffer buffer;
	private int data;
	
	public Producer(Buffer b){ // 생산자 스레드
		buffer = b;
	}
	
	public void run(){
		for(int i=0;i<10;i++){
			data =i;
			System.out.println("생산자: "+data+"번 케익을 생산함");
			buffer.put(data);
			try{
				sleep((int)(Math.random()*100));
			}catch(InterruptedException e){
			}
		}
	}
}

class Consumer extends Thread{ //소비자쓰레드
	private Buffer buffer;
	private int data;
	
	public Consumer(Buffer b){
		buffer =b;
	}
	public void run(){
		for(int i =0;i<10; i++){
			data = buffer.get();
			System.out.println("소비자 "+data+"번 케익을 먹었음");
			try{
				sleep((int)(Math.random()*100));
			}catch(InterruptedException e){
			}
		}
	}
}
public class CoordinationTest {
	public static void main(String[] args){
		Buffer b = new Buffer();
		Producer t1 = new Producer(b);
		Consumer t2 = new Consumer(b);
		t1.start(); //생산자 스레드 실행
		t2.start(); //소비자 스레드 실행
	}

}
