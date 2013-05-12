class Car{
	//필드선언
	private int speed,mileage;
	private String color;
	
	//접근자선언
	public int getSpeed(){
		return speed;
	}
	public int getMileage(){
		return mileage;
	}
	public String getColor(){
		return color;
	}
	
	//설정자선언
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
		Car myCar = new Car(); //객체생성
		
		//설정자 메소드 호출
		myCar.setSpeed(100);
		myCar.setMileage(0);
		myCar.setColor("red");
		
		//접근자 메소드 호출
		System.out.println("현재 자동차 속도는 "+myCar.getSpeed());
		System.out.println("현재 자동차의 주행거리는 "+myCar.getMileage());
		System.out.println("현재 자동차  색상은 "+myCar.getColor());
		
	}
}
