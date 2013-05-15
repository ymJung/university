class Shapes{
	public Shapes(String msg){
		System.out.println("Shape생성자 () " + msg); //수퍼 클래스 생성자
	}
}


public class Shape extends Shapes {
	public Shape(){ //서브클래스 생성자
		super("From rectangle"); //수퍼클래스 생성자 호출
		System.out.println("Rectangle 생성자 ()");
		
	}
	public static void main(String[] args){
		Shape r = new Shape();
	}

}
