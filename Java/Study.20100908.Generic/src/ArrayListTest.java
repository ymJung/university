import java.util.*;

public class ArrayListTest {
	public static void main(String args[]){
		ArrayList<String> list = new ArrayList<String>();
		
		list.add("MILK"); //리스트에 순서대로 추가
		list.add("BREAD");
		list.add("BUTTER");
		list.add(1,"APPLE"); // 인덱스 1에 삽입
		list.set(2,"GRAPE"); // 인덱스 2를 대체 
		list.remove(3); // 3 인덱스 삭제
		
		for(int i=0;i<list.size();i++)
			System.out.println(list.get(i));	
	}

}
