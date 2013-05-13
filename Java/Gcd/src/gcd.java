import java.util.*;
public class gcd {
	public static void main(String[] args){
		int x,y,r;
		System.out.print("최대공약수를 구할 두 정수를 입력하시오(큰수,작은수) : ");
		Scanner scan = new Scanner(System.in);
		x = scan.nextInt();
		y = scan.nextInt();
		
		while (y != 0){ //y가 0이 될때까지 나누기
			r = x%y; //남은값을 r값에 대입하고 남은값을 또 나누기
			x = y; //반복반복
			y = r;
			
		}
		System.out.printf("최대공약수는 %d 입니다.\n",x);
	}

}
