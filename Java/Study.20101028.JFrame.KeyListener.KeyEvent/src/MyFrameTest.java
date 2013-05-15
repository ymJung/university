import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

class MyFrame extends JFrame implements KeyListener{
	public MyFrame(){
		setTitle("Event Exam");
		setSize(300,200);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JTextField tf = new JTextField(20); //20칸 텍스트 공간
		tf.addKeyListener(this);
		
		add(tf);
		setVisible(true);
	}
	
	public void keyTyped(KeyEvent e){
		display(e,"KeyTyped ");
	}
	public void keyPressed(KeyEvent e){
		display(e,"KeyPressed ");
	}
	public void keyReleased(KeyEvent e){
		display(e,"KeyReleased ");
	}
	
	protected void display(KeyEvent e,String s){
		char c = e.getKeyChar();
		int keyCode = e.getKeyCode();
		String modifiers = e.isAltDown() + " " + e.isControlDown() + " " + e.isShiftDown();
		System.out.println(s + " " + c + " " + keyCode + " " + modifiers);
	}
}


public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyFrame f = new MyFrame();
	}

}
