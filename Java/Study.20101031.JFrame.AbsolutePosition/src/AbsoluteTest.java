import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MyFrame extends JFrame{
	JButton b1;
	private JButton b2,b3;
	
	public MyFrame(){
		setTitle("절대적 위치");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(300,200);
		JPanel p = new JPanel();
		p.setLayout(null);
		
		b1 = new JButton("버튼 #1");
		p.add(b1);
		b2 = new JButton("버튼 #2");
		p.add(b2);
		b3 = new JButton("버튼 #3");
		p.add(b3);
		
		b1.setBounds(20,5,95,30); // x20 y5 w95 h30
		b2.setBounds(55,45,105,70);
		b3.setBounds(180,15,105,90);
		add(p);
		setVisible(true);
	}
}
public class AbsoluteTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyFrame f = new MyFrame();
	}

}
