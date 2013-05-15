
public class Apartment implements Comparable{ //���������̽� ����
	private double area = 0;
	public Apartment(double a){
		area =a;
		
	}
	public int compareTo(Object otherObject){
		Apartment other = (Apartment) otherObject;
		if(this.area < other.area) return -1;
		else if(this.area > other.area)return 1;
		else return 0;
	}
	public static void main(String[] args){
		Apartment o1 = new Apartment(201.4);
		Apartment o2 = new Apartment(100.2);
		if(o1.compareTo(o2)>0)
			System.out.println("o1�� o2���� ũ��");
		else if(o1.compareTo(o2)<0)
			System.out.println("o1�� o2���� �۴�");
		else
			System.out.println("o1,o2�� ����");
	}

}
