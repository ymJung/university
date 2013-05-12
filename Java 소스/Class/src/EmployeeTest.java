import java.util.*;

class Employee{
	private String name;
	private double salary;
	
	private static int count = 0; //�������� ����
	
	public Employee(String n, double s){
		name =n;
		salary =s;
		count++; //�������� ����
	}
	
	protected void finalize(){ //��ü�� �Ҹ�ɶ� ȣ��
		count--; //������ �پ��°��̹Ƿ� count�� ����
		
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
		e1 = new Employee("�����",240000);
		e2 = new Employee("��ȣ��",303000);
		e3 = new Employee("����",30000);
		
		int n = Employee.getCount();
		System.out.println("���� ������ = "+n);

	}

}
