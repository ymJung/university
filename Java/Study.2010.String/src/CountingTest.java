
public class CountingTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String s = "I love you and you and you";
		int i,n = 0;
		System.out.println(s);
		for(i=0;i<s.length();i++){ //s�� ���̸�ŭ �ݺ�
			if(s.charAt(i) != 'y') //y�� ���ڸ� ����
				continue;
			
			n++;
		}
		
		System.out.println("���忡�� �߰ߵ� y�� ���� " +n);
		

	}

}
