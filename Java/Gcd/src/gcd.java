import java.util.*;
public class gcd {
	public static void main(String[] args){
		int x,y,r;
		System.out.print("�ִ������� ���� �� ������ �Է��Ͻÿ�(ū��,������) : ");
		Scanner scan = new Scanner(System.in);
		x = scan.nextInt();
		y = scan.nextInt();
		
		while (y != 0){ //y�� 0�� �ɶ����� ������
			r = x%y; //�������� r���� �����ϰ� �������� �� ������
			x = y; //�ݺ��ݺ�
			y = r;
			
		}
		System.out.printf("�ִ������� %d �Դϴ�.\n",x);
	}

}
