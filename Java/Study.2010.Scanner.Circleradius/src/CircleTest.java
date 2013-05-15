class Point{
	public int x,y;
	// 생성자
	public Point(int a,int b){
		x = a;
		y = b;
		
	}
}

class Circle{
	public int radius = 0;
	public Point center; //포인트 참조변수가 필드로 선언되어있다. //point를 재참조
	
	public Circle(){ //생성자
		center = new Point(0,0);
	}
	
	public Circle(int r ){
		center = new Point(0,0);
		radius = r;
	}
	public Circle(Point p, int r){ // center를 재참조
		center =p;
		radius =r;
	}
}
public class CircleTest {
	public static void main(String args[]){
		Point p = new Point(25,47);
		Circle c = new Circle(p,10); // 포인트를 참조
	}

}
