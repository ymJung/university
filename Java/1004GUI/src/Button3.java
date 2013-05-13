
import java.awt.*;
import javax.swing.*;

class MyFrame1 extends JFrame{
	public MyFrame1(){
		setSize(500,200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Test Frame");
		JPanel panel = new JPanel(); // 패널생성
		JButton b1 = new JButton(); //버튼1
		b1.setText("Left Button");
		JButton b2 = new JButton("Center Button");
		JButton b3 = new JButton("Right Button");
		b3.setEnabled(false);
		
		panel.add(b1);
		panel.add(b2);
		panel.add(b3);
		
		add(panel);
		setVisible(true);
		
	}
}
public class Button3 {
	public static void main(String[] args){
		MyFrame f = new MyFrame();
	}

}
