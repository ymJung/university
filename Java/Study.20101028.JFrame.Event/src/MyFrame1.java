import javax.swing.*;

import java.awt.Color;
import java.awt.event.*;

class MyFrame extends JFrame{
	private JButton button1;
	private JButton button2;
	private JPanel panel;
	
	public MyFrame(){
		this.setSize(300,200);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setTitle("Event exam");
		panel = new JPanel();
		button1 = new JButton("Yellow");
		button1.addActionListener(new MyListener()); //액션이벤트 처리
		panel.add(button1);
		button2 = new JButton("Pink");
		button2.addActionListener(new MyListener());
		panel.add(button2);
		
		this.add(panel);
		this.setVisible(true);
	}
		
		private class MyListener implements ActionListener{
			public void actionPerformed(ActionEvent e){
				if(e.getSource() == button1){
					panel.setBackground(Color.YELLOW);
				}else if(e.getSource() == button2){
					panel.setBackground(Color.PINK);
				}
				
			}
		}
		
}


public class MyFrame1 {
	public static void main(String[] args){
		MyFrame t = new MyFrame();
	}
}


