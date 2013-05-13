
import java.util.Scanner; //Scanner Class
public class Add {
	public static void main(String args[]){
		Scanner input = new Scanner(System.in);
		
		int x,y,sum;
		
		System.out.print("First number input : ");
		x = input.nextInt();
		
		System.out.print("Second number input : ");
		y = input.nextInt();
		
		sum = x + y;
		System.out.printf("두개의 숫자를 더한값은 %d입니다요",sum);
		
	}

}
