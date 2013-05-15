import java.awt.*;
import java.awt.event.*;

import javax.swing.*;

class MyFrame extends JFrame implements ComponentListener, FocusListener{
	JTextArea display;
	
	public MyFrame(){
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(300,200);
		setTitle("Event Test");
		
		addComponentListener(this); // 프레임에 컴포넌트 리스터 등록
		addFocusListener(this);
		
		setVisible(true);
	}
	
	public void componentHidden(ComponentEvent e){
		display("componentHidden() Method Call");
	}
	public void componentMoved(ComponentEvent e){
		display("componentMoved() Method Call");
	}
	public void componentResized(ComponentEvent e){
		display("componentResized() Method Call");
	}
	public void componentShown(ComponentEvent e){
		display("componentShown() Method Call");
	}
	public void focusGaind(FocusEvent e){
		display("FocusGained() Method Call");
	}
	public void focusLost(FocusEvent e){
		display("focusLost() Method Call");
	}
	public void display(String s){
		System.out.println(s);
	}
	
}


public class MyFrameTest {
	public static void main(String[] args){
		MyFrame t = new MyFrame();
	}
}
