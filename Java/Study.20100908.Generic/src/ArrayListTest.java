import java.util.*;

public class ArrayListTest {
	public static void main(String args[]){
		ArrayList<String> list = new ArrayList<String>();
		
		list.add("MILK"); //����Ʈ�� ������� �߰�
		list.add("BREAD");
		list.add("BUTTER");
		list.add(1,"APPLE"); // �ε��� 1�� ����
		list.set(2,"GRAPE"); // �ε��� 2�� ��ü 
		list.remove(3); // 3 �ε��� ����
		
		for(int i=0;i<list.size();i++)
			System.out.println(list.get(i));	
	}

}
