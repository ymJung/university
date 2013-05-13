import java.awt.*;
import javax.swing.*;

class MyFrame extends JFrame{
	public MyFrame(){
		//setTitle("FlowLayoutTest");
		//setTitle("BorderLayoutTest");
		//setTitle("GridLayoutTest");
		setTitle("BoxLayoutTest");
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel;
		// �г� ���� ��ġ�����ڸ� FlowLayout���� ����
		panel = new JPanel();
		
		//panel.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		
		/*//���� ũ�Ⱑ �ٸ� ��ư ����
		//�гο� ��ư ���� �߰�
		panel.add(new JButton("��ư1��"));
		panel.add(new JButton("��ư2��"));
		panel.add(new JButton("��ư3��"));
		panel.add(new JButton("4��"));
		panel.add(new JButton("��~ ��ư 5��"));
		add(panel);
		*/
		
		
		//�����̳ʸ� ����ȭ�Ͽ� ���� ������ ��ġ�Ѵ� 
		
		/*//������ ��ġ������
		setLayout(new BorderLayout());
		
		//��ư �߰�
		add(new JButton("�߾�"),BorderLayout.CENTER);
		add(new JButton("�� ������"),BorderLayout.LINE_START);
		add(new JButton("�� ����"),BorderLayout.LINE_END);
		add(new JButton("������ ������"),BorderLayout.PAGE_START);
		add(new JButton("������ ����"),BorderLayout.PAGE_END);
		*/
		
		/*//���� ���ϴ� ������ ��ư ����
		setLayout(new GridLayout(0,3)); // 3���� ���� ���� �� 
		
		add(new JButton("��ư1"));
		add(new JButton("��ư2"));
		add(new JButton("��ư3"));
		add(new JButton("������ ��ư 4"));
		*/
		
		//������Ʈ�ڽ� �ױ�
		
		//Y�� �������� �ڽ��� ����
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS)); 

		makeButton(panel, "��ư 1");
		makeButton(panel, "��ư 2");
		makeButton(panel, "��ư 3");
		makeButton(panel, "4");
		makeButton(panel, "��~ ��ư 5");
		add(panel);
		pack(); 
		setVisible(true);
	}
	
	private void makeButton(JPanel panel, String text){
		JButton button = new JButton(text);
		button.setAlignmentX(Component.CENTER_ALIGNMENT);
		panel.add(button);
	}
	/*
	pack(); // ��ư�� ������
	setVisible(true);
	
	
	}*/
}
public class FlowTest {
	public static void main(String args[]){
		MyFrame f = new MyFrame();
	}

}
