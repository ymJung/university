import java.awt.*;
import javax.swing.*;

class MyFrame extends JFrame {
	public MyFrame(){
		JButton Abutton = new JButton("'A'Button");// ��ư ����
		this.add(Abutton); // �����ӿ� �߰�
		setSize(300,200);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("MyFrame");
		
		JPanel panel = new JPanel(); //�гλ���
		JLabel label = new JLabel("��ο� ����"); //���̺����
		JButton Bbutton = new JButton("'B'Button");
		panel.add(label);
		panel.add(Bbutton);
		add(panel);
				
		setLayout(new FlowLayout()); // �������� ��ġ������
		setVisible(true);
	}

}
public class FrameTest{
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyFrame f = new MyFrame();
	}

}
