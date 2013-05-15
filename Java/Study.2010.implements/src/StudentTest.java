import java.util.*;

public class StudentTest {
	public static void main(String[] args){
		Student[] students = new Student[3];
		students[0] = new Student("홍낄낄",4.5);
		students[1] = new Student("꺽정리",4.3);
		students[2] = new Student("홍진호",3.2);
		
		Arrays.sort(students); //Array클래스안의 정적메소드
		
		for(Student s : students)
			System.out.println("이름: "+s.getName() + "평점: "+s.getGPA());
		
	}

}
class Student implements Comparable{
	private String name;
	private double gpa;
	
	public Student(String n,double g){
		name = n;
		gpa = g;
	}
	public String getName(){
		return name;
	}
	public double getGPA(){
		return gpa;
	}
	
	//Comparable 추상메소드
	public int compareTo(Object obj){
		Student other = (Student) obj;
		if(gpa<other.gpa)
			return -1;
		else if(gpa>other.gpa)
			return 1;
		else
			return 0;
		
	}
}