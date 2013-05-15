import javax.swing.*;
import java.awt.event.*;

class MyFrame extends JFrame{
	private JButton button;
	private JTextField text, result;
	
	public MyFrame(){
		setSize(300,130);
		setTitle("제곱계산하기");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		ButtonListener listener = new ButtonListener(); //리스터 객체
		
		JPanel panel = new JPanel();
		panel.add(new JLabel("숫자를 입력하시오 : "));
		text = new JTextField(15);
		text.addActionListener(listener);
		panel.add(text); //텍스트 받음
		
		panel.add(new JLabel("제곱한 값 : "));
		result = new JTextField(15);
		result.setEditable(false);
		panel.add(result);
		
		button = new JButton("OK");
		button.addActionListener(listener);
		panel.add(button);
		add(panel);
		setVisible(true);
	}
	
	//텍스트필드와 버튼의 액션 이벤트 처리
	
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
