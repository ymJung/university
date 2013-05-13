import java.util.*;

public class HashSetTest1 {
	public static void main(String[] args){
		Set<String> s1 = new HashSet<String>();
		Set<String> s2 = new HashSet<String>();
		
		s1.add("A");
		s1.add("B");
		s1.add("C");
		
		s2.add("A");
		s2.add("D");
		
		Set<String> union = new HashSet<String>(s1);
		union.addAll(s2); // s2를 합집합
		
		Set<String> intersection = new HashSet<String>(s1); // s1을 대입
		intersection.retainAll(s2); // s2와 교집합
		
		System.out.println("합집합 " +union);
		System.out.println("교집합 " +intersection);
		
	}
}
