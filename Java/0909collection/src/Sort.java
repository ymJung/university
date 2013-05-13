import java.util.*;

public class Sort {
	public static void main(String[] args){
		String[] sample = {"i","you","love"};
		List<String> list = Arrays.asList(sample); // 배열을 리스트로 변경
		Collections.sort(list); // 리스트 정렬
		System.out.println(list);
	}

}
