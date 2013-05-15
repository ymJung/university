class ParentClass{
	int data =100;
	public void print(){
		System.out.println("수퍼클래스 print() 메소드");
	
	}
}
public class ChildClass extends ParentClass {
	int data =200;
	public void print(){ //메소드 재정의
		super.print();
		System.out.println("서브클래스print() 메소드");
		System.out.println(data); // 지금클래스 데이터
		System.out.println(this.data); //지금클래스데이터
		System.out.println(super.data);
	}
	public static void main(String[] args){
		ChildClass cls = new ChildClass();
		cls.print();
	}

}
