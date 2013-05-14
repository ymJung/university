import java.awt.*;
import javax.swing.*;

class MyFrame extends JFrame {
	public MyFrame(){
		JButton Abutton = new JButton("'A'Button");// 버튼 생성
		this.add(Abutton); // 프레임에 추가
		setSize(300,200);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("MyFrame");
		
		JPanel panel = new JPanel(); //패널생성
		JLabel label = new JLabel("헬로우 스윙"); //레이블생성
		JButton Bbutton = new JButton("'B'Button");
		panel.add(label);
		panel.add(Bbutton);
		add(panel);
				
		setLayout(new FlowLayout()); // 프레임의 배치관리자
		setVisible(true);
	}

}
public class FrameTest{
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyFrame f = new MyFrame();
	}

}
