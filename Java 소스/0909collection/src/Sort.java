import java.util.*;

public class Sort {
	public static void main(String[] args){
		String[] sample = {"i","you","love"};
		List<String> list = Arrays.asList(sample); // �迭�� ����Ʈ�� ����
		Collections.sort(list); // ����Ʈ ����
		System.out.println(list);
	}

}
