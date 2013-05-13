import java.util.Scanner;
class Car{
	public int speed;
	public int mileage;
	public String color;
	
	public Car(){
		speed = mileage =0;
		color = "red";
	}
	
	public void speedUp(){
		speed += 10;
	}
	public String toString(){
		return "加档:" +speed+ "林青芭府"+mileage+"祸惑"+color;
	}
}
public class CarTest {
	public static void main(String[] args){
		final int NUM_CARS =5;
		Car[] cars = new Car[NUM_CARS];
		
		for(int i =0;i<cars.length;i++)
			cars[i] = new Car();
		for(int i =0;i<cars.length;i++)
			cars[i].speedUp();
		for(int i =0;i<cars.length;i++)
			System.out.println(cars[i]);
	}

}
