
public class CountingTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String s = "I love you and you and you";
		int i,n = 0;
		System.out.println(s);
		for(i=0;i<s.length();i++){ //s의 길이만큼 반복
			if(s.charAt(i) != 'y') //y의 숫자를 센다
				continue;
			
			n++;
		}
		
		System.out.println("문장에서 발견된 y의 개수 " +n);
		

	}

}
