import java.awt.*;
import java.awt.event.*;
import java.text.*;
import java.util.Date;

import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.*;


import java.beans.PropertyChangeListener;
import java.beans.PropertyChangeEvent;

class MyFrame extends JFrame implements PropertyChangeListener{
	//�ʵ� ����
	private double amount = 100000;
	private Date date;
	
	//�ʵ��� �̸�ǥ�� ���̺�
	private JLabel amountLabel;
	private JLabel dateLabel;
	
	private JFormattedTextField amountField;
	private JFormattedTextField dateField;
	
	public MyFrame(){
		super();
		setSize(300,100);
		
		//���̺� ����
		amountLabel = new JLabel("�ݾ� : ");
		dateLabel = new JLabel("��¥ : ");
		
		//���� �Է� �ؽ�Ʈ �ʵ� ���� �� ����
		amountField = new JFormattedTextField(new NumberFormatter()); // ���� ����
		amountField.setValue(new Integer(1000)); // ���ڰ� �Է�
		amountField.setColumns(10);
		amountField.addPropertyChangeListener("value",this);
		
		//��¥ �Է� �ؽ�Ʈ �ʵ� ���� ����
		dateField = new JFormattedTextField(new DateFormatter());
		dateField.setValue(new Date());
		dateField.setColumns(10);
		dateField.addPropertyChangeListener("value", this);
		
		//�гο� �ؽ�Ʈ �ʵ带 ��ġ
		JPanel panel1 = new JPanel();
		JPanel panel2 = new JPanel();
		
		panel1.add(amountLabel);
		panel1.add(amountField);
		panel2.add(dateField);
		panel2.add(dateField);
		add(panel1, BorderLayout.NORTH);
		add(panel2, BorderLayout.SOUTH);
		setVisible(true);
	}
	
	
	
	public void propertyChange(PropertyChangeEvent e){
		Object source = e.getSource();
		if(source == amountField){
			amount = ((Number)amountField.getValue()).doubleValue();
			System.out.println(amount);
		}else if(source == dateField){
			date = (Date) (dateField.getValue());
			System.out.println(date);
		}
	}
}

public class FormattedFieldTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new MyFrame();
	}

}
