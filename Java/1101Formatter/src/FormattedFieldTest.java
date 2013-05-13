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
	//필드 정의
	private double amount = 100000;
	private Date date;
	
	//필드의 이름표시 레이블
	private JLabel amountLabel;
	private JLabel dateLabel;
	
	private JFormattedTextField amountField;
	private JFormattedTextField dateField;
	
	public MyFrame(){
		super();
		setSize(300,100);
		
		//레이블 생성
		amountLabel = new JLabel("금액 : ");
		dateLabel = new JLabel("날짜 : ");
		
		//숫자 입력 텍스트 필드 생성 과 설정
		amountField = new JFormattedTextField(new NumberFormatter()); // 숫자 포맷
		amountField.setValue(new Integer(1000)); // 숫자값 입력
		amountField.setColumns(10);
		amountField.addPropertyChangeListener("value",this);
		
		//날짜 입력 텍스트 필드 생성 설정
		dateField = new JFormattedTextField(new DateFormatter());
		dateField.setValue(new Date());
		dateField.setColumns(10);
		dateField.addPropertyChangeListener("value", this);
		
		//패널에 텍스트 필드를 배치
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
