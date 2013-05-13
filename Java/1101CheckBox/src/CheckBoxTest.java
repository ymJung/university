import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.applet.Applet;

import javax.swing.*;

class MyFrame extends JFrame implements ActionListener{
	private JButton buttonOK;
	private JCheckBox onion,cheese,tomato;
	
	public MyFrame(){
		setTitle("Check box Test");
		setSize(300,130);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JLabel label = new JLabel("햄버거에 추가할 것은?");
		JPanel topPanel = new JPanel();
		topPanel.add(label);
		add(topPanel,BorderLayout.NORTH);
		
		//체크박스 생성 추가
		JPanel panel = new JPanel();
		onion= new JCheckBox("양파");
		panel.add(onion);
		cheese = new JCheckBox("치즈");
		panel.add(cheese);
		tomato= new JCheckBox("토마토");
		panel.add(tomato);
		add(panel,BorderLayout.CENTER);
		
		//버튼 생성 및 추가
		buttonOK = new JButton("OK");
		JPanel bottomPanel = new JPanel();
		bottomPanel.add(buttonOK);
		add(bottomPanel,BorderLayout.SOUTH);
		buttonOK.addActionListener(this);
		
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == buttonOK){
			String msg = ""; //초기 메시지
			if(onion.isSelected())
				msg += "양파\n";
			if(cheese.isSelected())
				msg += "치즈\n";
			if(tomato.isSelected())
				msg += "토마토\n";
			msg = "선택한 옵션은 \n" +msg;
			System.out.println(msg);
			
			onion.setSelected(false); //해제
			cheese.setSelected(false);
			tomato.setSelected(false);
		}
	}
}


public class CheckBoxTest {
	public static void main(String args[]){
		new MyFrame();
	}

}
