import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class MyFrame extends JFrame implements ActionListener{
	protected JTextField textField;
	protected JTextArea textArea;
	
	public MyFrame(){
		setTitle("Text Area Test");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		textField = new JTextField(30);
		textField.addActionListener(this);
		
		textArea = new JTextArea(10,30);
		textArea.setEditable(false);
		
		add(textField, BorderLayout.NORTH);
		add(textArea, BorderLayout.CENTER);
		
		pack();
		setVisible(true);
	}
	public void actionPerformed(ActionEvent evt){
		String text = textField.getText();
		textArea.append(text+"\n"); //텍스트 필드를 읽어서 영역에 추가
		textField.selectAll();
		textArea.setCaretPosition(textArea.getDocument().getLength());
	}
}

public class TextAreaTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new MyFrame();
	}

}