import java.awt.*;
import java.awt.event.*;
import java.text.ParseException;

import javax.swing.*;
import javax.swing.text.MaskFormatter;

class MyFrame extends JFrame implements ActionListener{
	protected JTextField id;
	protected JPasswordField password;
	protected JFormattedTextField date;
	protected JTextArea textArea;
	
	public MyFrame() throws ParseException{
		super("My Frame");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(3,2)); //3,2그리드 배치
		
		id = new JTextField(30);
		id.addActionListener(this);
		panel.add(new JLabel("ID :"));
		panel.add(id);
		
		password = new JPasswordField(30);
		password.addActionListener(this);
		panel.add(new JLabel("P.W :"));
		panel.add(password);
		
		MaskFormatter mf = new MaskFormatter("####.##.##"); //숫자만 입력
		mf.setPlaceholderCharacter('_');
		date = new JFormattedTextField(mf);
		date.addActionListener(this);
		panel.add(new JLabel("DATE :"));
		panel.add(date);
		
		textArea = new JTextArea(10,30);
		textArea.setEditable(false);
		
		add(panel,BorderLayout.NORTH);
		add(textArea,BorderLayout.CENTER);
		pack();
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e){
		//엔터키시
		if(e.getSource() == id || e.getSource() == password || e.getSource() == date){
			String text = "ID = "+ id.getText()+"P.W = "+password.getText()+"DATE = "+date.getText();
			textArea.append(text+ "\n"); //텍스트 영역에 추가한다
			id.selectAll();
			password.selectAll();
			date.selectAll();
			//카렛이동
			textArea.setCaretPosition(textArea.getDocument().getLength());//이동
		}
	}
}

public class TextTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws ParseException {
		// TODO Auto-generated method stub
		MyFrame frame = new MyFrame();

	}

}
