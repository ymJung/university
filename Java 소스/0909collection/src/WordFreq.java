import java.util.*;

public class WordFreq {
	public static void main(String[] args){
		Map<String,Integer> m = new HashMap<String, Integer>();
		
		String[] sample= {"to","be","or","not","to","be","is","a","problem"};
		//�󵵰��
		for(String a : sample){
			Integer freq = m.get(a); // ���� �ؽ��� �ܾ��� �� ������
			m.put(a,(freq == null)? 1:freq +1); // �����ܾ�� �ܾ�󵵸� ����
			
		}
		System.out.println(m.size()+ "�ܾ �ֽ��ϴ�");
		System.out.println(m.containsKey("to")); // to �� ������ ��
		System.out.println(m.isEmpty()); // ������� ��
		System.out.println(m);
		
		
	}

}
