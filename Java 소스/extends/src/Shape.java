class Shapes{
	public Shapes(String msg){
		System.out.println("Shape������ () " + msg); //���� Ŭ���� ������
	}
}


public class Shape extends Shapes {
	public Shape(){ //����Ŭ���� ������
		super("From rectangle"); //����Ŭ���� ������ ȣ��
		System.out.println("Rectangle ������ ()");
		
	}
	public static void main(String[] args){
		Shape r = new Shape();
	}

}
