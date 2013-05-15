import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MyComponent extends JComponent {
	public static final int x= 30;
	public static final int y= 80;
	
	public void paint(Graphics g){
		g.setColor(Color.YELLOW);
		g.fillOval(20,30,200,200);
		g.setColor(Color.black);
		
		g.drawArc(60, 80, 50, 50, 180, -180);
		g.drawArc(150,80,50,50,180,-180);
		g.drawArc(70, 130, 100, 70, 180, 180);
		g.drawString("Hello Java Programer !!", x, y);
		//g.drawLine(x,y+10, x+200, y+10);
	}
}
public class GraphicFrame extends JFrame{
	public static final int WIDTH =300;
	public static final int HEIGHT = 200;
	
	public GraphicFrame(){
		setSize(280,300);
		setTitle("My Graphic");
		setSize(WIDTH,HEIGHT);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setVisible(true);
		
		MyComponent c = new MyComponent();
		add(c);
	}
	
	public static void main(String[] args){
		GraphicFrame fr = new GraphicFrame();
	}

}
