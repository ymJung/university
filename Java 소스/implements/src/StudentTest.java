import java.util.*;

public class StudentTest {
	public static void main(String[] args){
		Student[] students = new Student[3];
		students[0] = new Student("ȫ����",4.5);
		students[1] = new Student("������",4.3);
		students[2] = new Student("ȫ��ȣ",3.2);
		
		Arrays.sort(students); //ArrayŬ�������� �����޼ҵ�
		
		for(Student s : students)
			System.out.println("�̸�: "+s.getName() + "����: "+s.getGPA());
		
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
	
	//Comparable �߻�޼ҵ�
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