import java.util.*;

public class Shuffle {
	public static void main(String[] args){
		List<Integer> list = new ArrayList<Integer>();
		for(int i = 1; i<11;i++)
			list.add(i); // 1~10 Ãß°¡
		Collections.shuffle(list);
		System.out.println(list);
		int index = Collections.binarySearch(list, 3);
		System.out.println(index);
	}

}
