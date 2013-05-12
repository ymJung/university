import java.util.*;

public class QueueTest {
	public static void main(String[] args)throws InterruptedException{
		int time = 10;
		Queue<Integer> queue = new LinkedList<Integer>(); //ť����
		for(int i = time; i>=0; i--) //10���� 0���� ť�� ����
			queue.add(i);
		while(!queue.isEmpty()){
			System.out.print(queue.remove()+ " "); // ť�� 1�ʿ� �ϳ��� ���� �����Ȱ��� ��ȯ
			Thread.sleep(100);
		}
	PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
	pq.add(30);
	pq.add(80);
	pq.add(20);
	
	for(Integer o : pq)
		System.out.println(o); //ť ���� ���
	System.out.println("���һ���");
	while(!pq.isEmpty()) //ť���� ����
		System.out.println(pq.remove()); //�����Ȱ� ��ȯ
		
	}
	

}
