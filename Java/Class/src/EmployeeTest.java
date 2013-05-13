import java.util.*;

class Employee{
	private String name;
	private double salary;
	
	private static int count = 0; //정적변수 선언
	
	public Employee(String n, double s){
		name =n;
		salary =s;
		count++; //정적변수 증가
	}
	
	protected void finalize(){ //객체가 소멸될때 호출
		count--; //직원이 줄어드는것이므로 count를 감소
		
	}
	
	public static int getCount(){ //static method
		return count;
	}
}

public class EmployeeTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		Employee e1,e2,e3;
		e1 = new Employee("김덕팔",240000);
		e2 = new Employee("간호순",303000);
		e3 = new Employee("김대기",30000);
		
		int n = Employee.getCount();
		System.out.println("현재 직원수 = "+n);

	}

}
