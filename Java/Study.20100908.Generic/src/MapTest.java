import java.util.*;

class Student{
	int number;
	String name;
	
	public Student(int number, String name){
		this.number = number;
		this.name = name;
		
	}
	
	public String toString(){
		return name;
	}

}

public class MapTest{
	public static void main(String[] args){
		Map<String, Student> st = new HashMap<String,Student>();
		st.put("20090001",new Student(20090001,"구잔디"));
		st.put("20090002",new Student(20090002,"금준표"));
		st.put("20090003",new Student(20090003,"윤자후"));
		

		System.out.println(st);		//All print
		
		st.remove("20090001"); // 맵삭제 키 지정
		
		st.put("20090003",new Student(20090003,"소방관")); //값 대치
		
		System.out.println(st.get("20090003"));
		
		for(Map.Entry<String,Student> s : st.entrySet()){
			String key = s.getKey();
			Student value = s.getValue();
			System.out.println("key= " + key + ", value= " + value);
			
		}
		
		
	}
}