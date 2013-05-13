import javax.swing.*;
import java.awt.event.*;

class MyFrame extends JFrame{
	private JButton button;
	private JTextField text, result;
	
	public MyFrame(){
		setSize(300,130);
		setTitle("��������ϱ�");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		ButtonListener listener = new ButtonListener(); //������ ��ü
		
		JPanel panel = new JPanel();
		panel.add(new JLabel("���ڸ� �Է��Ͻÿ� : "));
		text = new JTextField(15);
		text.addActionListener(listener);
		panel.add(text); //�ؽ�Ʈ ����
		
		panel.add(new JLabel("������ �� : "));
		result = new JTextField(15);
		result.setEditable(false);
		panel.add(result);
		
		button = new JButton("OK");
		button.addActionListener(listener);
		panel.add(button);
		add(panel);
		setVisible(true);
	}
	
	//�ؽ�Ʈ�ʵ�� ��ư�� �׼� �̺�Ʈ ó��
	
	private class ButtonListener implements ActionListener{
		public void actionPerformed(ActionEvent e){
			if(e.getSource() == button || e.getSource() == text){
				String name = text.getText();
				int value = Integer.parseInt(name);
				result.setText(" " + value * value);
				text.requestFocus();
			}
		}
	}
}

public class MyFrameTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MyFrame taa = new MyFrame();

	}

}
