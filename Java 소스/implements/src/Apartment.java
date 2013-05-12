
public class Apartment implements Comparable{
	private double area =0;
	
	public Apartment(double a){
		area = a;
	}
	public int compareTo(Object otherObject){
		Apartment other = (Apartment) otherObject;
		if(this.area < other.area) return -1;
		else if(this.area > other.area)return 1;
		else return 0;
	}
	public static void main(String[] args){
		Apartment o1 = new Apartment(105.3);
		Apartment o2 = new Apartment(54.2);
		
		if(o1.compareTo(o2) >0)
			System.out.println("o1이 o2보다 커");
		else if(o2.compareTo(o2) <0)
			System.out.println("o2가 o1보다 크네");
		else
			System.out.println("둘다 같다");
		
	}

}
