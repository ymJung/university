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
		panel.setLayout(new GridLayout(3,2)); //3,2�׸��� ��ġ
		
		id = new JTextField(30);
		id.addActionListener(this);
		panel.add(new JLabel("ID :"));
		panel.add(id);
		
		password = new JPasswordField(30);
		password.addActionListener(this);
		panel.add(new JLabel("P.W :"));
		panel.add(password);
		
		MaskFormatter mf = new MaskFormatter("####.##.##"); //���ڸ� �Է�
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
		//����Ű��
		if(e.getSource() == id || e.getSource() == password || e.getSource() == date){
			String text = "ID = "+ id.getText()+"P.W = "+password.getText()+"DATE = "+date.getText();
			textArea.append(text+ "\n"); //�ؽ�Ʈ ������ �߰��Ѵ�
			id.selectAll();
			password.selectAll();
			date.selectAll();
			//ī���̵�
			textArea.setCaretPosition(textArea.getDocument().getLength());//�̵�
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
