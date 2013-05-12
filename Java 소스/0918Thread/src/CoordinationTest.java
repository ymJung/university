class Buffer{
	//wait() notify ���
	private int data;
	private boolean empty = true;
	
	public synchronized int get(){
		while(empty){
			try{
				wait(); // �� ����� wait ȣ��
			}catch(InterruptedException e){
			}
		}
		empty = true; //�Һ�
		notifyAll(); //�Һ�Ǿ����� �˸�
		return data;
	}
	public synchronized void put(int data){
		//�Һ��Ҷ����� wait()ȣ��
		while(!empty){
			try{
				wait();
			}catch(InterruptedException e){
			}
		}
		//����Ǿ����� ǥ��
		empty = false; //����Ǿ��ٴ� ǥ��
		this.data = data; //������ ����
		notifyAll(); // ����Ǿ����� �˸�
		
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
	
	public Producer(Buffer b){ // ������ ������
		buffer = b;
	}
	
	public void run(){
		for(int i=0;i<10;i++){
			data =i;
			System.out.println("������: "+data+"�� ������ ������");
			buffer.put(data);
			try{
				sleep((int)(Math.random()*100));
			}catch(InterruptedException e){
			}
		}
	}
}

class Consumer extends Thread{ //�Һ��ھ�����
	private Buffer buffer;
	private int data;
	
	public Consumer(Buffer b){
		buffer =b;
	}
	public void run(){
		for(int i =0;i<10; i++){
			data = buffer.get();
			System.out.println("�Һ��� "+data+"�� ������ �Ծ���");
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
		t1.start(); //������ ������ ����
		t2.start(); //�Һ��� ������ ����
	}

}
