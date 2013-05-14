import java.util.*;

public class QueueTest {
	public static void main(String[] args)throws InterruptedException{
		int time = 10;
		Queue<Integer> queue = new LinkedList<Integer>(); //큐생성
		for(int i = time; i>=0; i--) //10부터 0가지 큐에 대입
			queue.add(i);
		while(!queue.isEmpty()){
			System.out.print(queue.remove()+ " "); // 큐를 1초에 하나씩 삭제 삭제된값을 반환
			Thread.sleep(100);
		}
	PriorityQueue<Integer> pq = new PriorityQueue<Integer>();
	pq.add(30);
	pq.add(80);
	pq.add(20);
	
	for(Integer o : pq)
		System.out.println(o); //큐 원소 출력
	System.out.println("원소삭제");
	while(!pq.isEmpty()) //큐에서 삭제
		System.out.println(pq.remove()); //삭제된값 반환
		
	}
	

}
