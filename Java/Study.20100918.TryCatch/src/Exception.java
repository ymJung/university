class DivideByZeroException extends ArithmeticException{
	public DivideByZeroException(){
		super("0으로 나눌수 없다");
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
	throws DivideByZeroException //예외발생시 던져서 처리
	{
		if(d==0)
			throw new DivideByZeroException();
		return (double) n/d;
	}

}
