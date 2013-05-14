class DivideByZeroException extends ArithmeticException{
	public DivideByZeroException(){
		super("0���� ������ ����");
	}
}
public class Exception {
	public static void main(String[] args){
		double result;
		try{
			result = quotient(1,0);
		}catch(DivideByZeroException e){
			System.out.println(e.toString());
		}
	}
	public static double quotient(int n, int d)
	throws DivideByZeroException //���ܹ߻��� ������ ó��
	{
		if(d==0)
			throw new DivideByZeroException();
		return (double) n/d;
	}

}
