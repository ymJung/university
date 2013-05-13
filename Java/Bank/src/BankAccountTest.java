
package bankaccount;

class BankAccount{
	int accountNumber; //계좌번호
	String owner; //소유주
	int balance; //잔액
	
	void deposit(int amount){ //입금
		balance += amount;
		
	}
	void withdraw(int amount){ //출금
		balance -=amount;
	}
	public String toString(){ //잔액표시
		return "현재 잔액은 " + balance + "입니다";
		
	}
}
public class BankAccountTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BankAccount myAccount = new BankAccount();
		
		//객체 메소드 호출
		myAccount.deposit(10000);
		System.out.println(myAccount);
		myAccount.withdraw(8000);
		System.out.println(myAccount);
	}

}
