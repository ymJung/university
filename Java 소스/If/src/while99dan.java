
import java.util.*;

public class while99dan {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int n,i=1;
		
		System.out.print("����� �˰�ͽ��ϱ�?");
		Scanner scan = new Scanner(System.in);
		n = scan.nextInt();
		while(i<=9){
			System.out.printf("%d*%d = %d \n",n,i,n*i);
			i++;
		}

	}

}
