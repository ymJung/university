class Point{
	public int x,y;
	// ������
	public Point(int a,int b){
		x = a;
		y = b;
		
	}
}

class Circle{
	public int radius = 0;
	public Point center; //����Ʈ ���������� �ʵ�� ����Ǿ��ִ�. //point�� ������
	
	public Circle(){ //������
		center = new Point(0,0);
	}
	
	public Circle(int r ){
		center = new Point(0,0);
		radius = r;
	}
	public Circle(Point p, int r){ // center�� ������
		center =p;
		radius =r;
	}
}
public class CircleTest {
	public static void main(String args[]){
		Point p = new Point(25,47);
		Circle c = new Circle(p,10); // ����Ʈ�� ����
	}

}
