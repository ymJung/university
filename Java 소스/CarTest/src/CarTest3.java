class Car{
	private int speed;
	private int mileage;
	private String color;
	
	private int id;
	
	private static int numberOfcars =0;
	
	public Car(int s,int m,String c){
		speed =s;
		mileage =m;
		color =c;
		
		id = ++numberOfcars;
	}
	public static int getNumberOfCars(){
		return numberOfcars;
	}
}
public class CarTest3 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Car c1 = new Car(100,0,"�۷���");
		Car c2 = new Car(200,400,"������");
		Car c3 = new Car(200,400,"������");
		Car c4 = new Car(200,400,"������");
		Car c5 = new Car(200,400,"������");
		int n = Car.getNumberOfCars();
		System.out.println("���ݱ��� ������ �ڵ��� �� = " +n); 

	}

}
