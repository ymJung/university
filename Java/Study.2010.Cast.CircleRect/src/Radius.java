
public class Radius {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int half;
		float circleradius,PI;
		PI = 3.1415f;
		half = 5; //반지름
		circleradius = (float)half * 2 *PI;

		System.out.println("원의 넓이는 "+circleradius+"입니다");

		int x,y;

		x = 30 ; // 가로
		y = 20 ; //세로
		System.out.println("사각형의 넓이는 "+ x*y +"입니다");

		char c1,c2,c3,c4;
		c1 = 'e'; 
		c2 = 'h';
		c3 = 'a';
		c4 = 'n';
		
		int e = (byte)c1; //캐스팅 타입변환 
		int h = (byte)c2;
		int a = (byte)c3;
		int n = (byte)c4;
		e++;h++;a++;n++;
		int sum;
		sum = e+h+a+n; //합계
		
		System.out.println("e는 "+ e +" h는 "+ h + " a는 "+ a + " n는 " +n + " 이며");
		System.out.println("합계는 " +sum+ " 입니다.");



		}

}

