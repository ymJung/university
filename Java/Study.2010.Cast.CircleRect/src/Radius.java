
public class Radius {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int half;
		float circleradius,PI;
		PI = 3.1415f;
		half = 5; //������
		circleradius = (float)half * 2 *PI;

		System.out.println("���� ���̴� "+circleradius+"�Դϴ�");

		int x,y;

		x = 30 ; // ����
		y = 20 ; //����
		System.out.println("�簢���� ���̴� "+ x*y +"�Դϴ�");

		char c1,c2,c3,c4;
		c1 = 'e'; 
		c2 = 'h';
		c3 = 'a';
		c4 = 'n';
		
		int e = (byte)c1; //ĳ���� Ÿ�Ժ�ȯ 
		int h = (byte)c2;
		int a = (byte)c3;
		int n = (byte)c4;
		e++;h++;a++;n++;
		int sum;
		sum = e+h+a+n; //�հ�
		
		System.out.println("e�� "+ e +" h�� "+ h + " a�� "+ a + " n�� " +n + " �̸�");
		System.out.println("�հ�� " +sum+ " �Դϴ�.");



		}

}

