import java.util.*;
public class HashSetTest {
	public static void main(String args[]){
		HashSet<String> set = new HashSet<String>();
		
		set.add("MILK");
		set.add("BREAD");
		set.add("BUTTER");
		set.add("CHEESE");
		set.add("MILK");
		set.add("milk");
		
		System.out.println(set);
	}

}
