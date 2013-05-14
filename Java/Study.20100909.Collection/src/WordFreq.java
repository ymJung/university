import java.util.*;

public class WordFreq {
	public static void main(String[] args){
		Map<String,Integer> m = new HashMap<String, Integer>();
		
		String[] sample= {"to","be","or","not","to","be","is","a","problem"};
		//빈도계산
		for(String a : sample){
			Integer freq = m.get(a); // 대입 해쉬맵 단어의 빈도 가져옴
			m.put(a,(freq == null)? 1:freq +1); // 같은단어시 단어빈도를 증가
			
		}
		System.out.println(m.size()+ "단어가 있습니다");
		System.out.println(m.containsKey("to")); // to 가 있을시 참
		System.out.println(m.isEmpty()); // 비었을시 참
		System.out.println(m);
		
		
	}

}
