class Car{
	//�ʵ弱��
	private int speed,mileage;
	private String color;
	
	//�����ڼ���
	public int getSpeed(){
		return speed;
	}
	public int getMileage(){
		return mileage;
	}
	public String getColor(){
		return color;
	}
	
	//�����ڼ���
	public void setSpeed(int s){
		speed =s;
	}
	public void setMileage(int m){
		mileage = m;
	}
	public void setColor(String c){
		color = c;
	}
	
	
}
public class CarTest2 {
	public static void main(String[] args){
		Car myCar = new Car(); //��ü����
		
		//������ �޼ҵ� ȣ��
		myCar.setSpeed(100);
		myCar.setMileage(0);
		myCar.setColor("red");
		
		//������ �޼ҵ� ȣ��
		System.out.println("���� �ڵ��� �ӵ��� "+myCar.getSpeed());
		System.out.println("���� �ڵ����� ����Ÿ��� "+myCar.getMileage());
		System.out.println("���� �ڵ���  ������ "+myCar.getColor());
		
	}
}
