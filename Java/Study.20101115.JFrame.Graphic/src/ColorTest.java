import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

class MyPanel extends JPanel implements ActionListener{
	JButton b1;
	Color color = new Color(0,0,0);
	
	public MyPanel(){
		setLayout(new BorderLayout());
		b1 = new JButton("Color Change!");
		b1.addActionListener(this);
		add(b1,BorderLayout.SOUTH);
	}
	
	public void paint(Graphics g){
		super.paint(g);
		g.setColor(color);
		g.fillRect(10,10,210,220);
	}
	
	public void actionPerformed(ActionEvent e){
		color = new Color((int)(Math.random()*255.0),(int)(Math.random()*255.0),(int)(Math.random()*255.0));
		repaint();
	}
}
public class ColorTest extends JFrame {
	public ColorTest(){
		setSize(300,300);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("Color Test");
		setVisible(true);
		JPanel panel = new MyPanel();
		add(panel);
	}
	public static void main(String[] args){
		ColorTest t = new ColorTest();
	}

}
