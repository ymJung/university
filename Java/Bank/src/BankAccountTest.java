
package bankaccount;

class BankAccount{
	int accountNumber; //���¹�ȣ
	String owner; //������
	int balance; //�ܾ�
	
	void deposit(int amount){ //�Ա�
		balance += amount;
		
	}
	void withdraw(int amount){ //���
		balance -=amount;
	}
	public String toString(){ //�ܾ�ǥ��
		return "���� �ܾ��� " + balance + "�Դϴ�";
		
	}
}
public class BankAccountTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		BankAccount myAccount = new BankAccount();
		
		//��ü �޼ҵ� ȣ��
		myAccount.deposit(10000);
		System.out.println(myAccount);
		myAccount.withdraw(8000);
		System.out.println(myAccount);
	}

}
