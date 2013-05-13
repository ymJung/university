import javax.swing.*;
import javax.swing.border.Border;

import java.awt.event.*;
import java.awt.*;
class MyFrame extends JFrame implements ActionListener{
	private JRadioButton top,let,bm;
	private JLabel text;
	private JPanel topPanel, sizePanel, resultPanel;
	
	public MyFrame(){
		setTitle("���� ��ư �׽�Ʈ");
		setSize(300,150);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		topPanel = new JPanel();
		JLabel label = new JLabel("� Ŀ�Ǹ� �ֹ��Ͻðڽ��ϱ�? ");
		topPanel.add(label);
		add(topPanel,BorderLayout.NORTH);
		sizePanel = new JPanel();
		top = new JRadioButton("Ƽ����");
		let = new JRadioButton("������");
		bm = new JRadioButton("����ӽ�");
		
		ButtonGroup size = new ButtonGroup();
		size.add(top);
		size.add(let);
		size.add(bm);
		top.addActionListener(this);
		let.addActionListener(this);
		bm.addActionListener(this);
		sizePanel.add(top);
		sizePanel.add(let);
		sizePanel.add(bm);
		add(sizePanel,BorderLayout.CENTER);
		
		resultPanel = new JPanel();
		text = new JLabel ("��ǥ�� ���õ��� �ʾҽ���");
		text.setForeground(Color.red);
		resultPanel.add(text);
		add(resultPanel, BorderLayout.SOUTH);
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == top){
			text.setText("�Źξư� ���õ�");
		}
		if(e.getSource() == let){
			text.setText("�α��� Ŀ�ǰ� ���õ�");
		}
		if(e.getSource() == bm){
			text.setText("���Ǳ� �ٺ�Ŀ��");
		}
		
	}
}
public class RadioBoxTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		new MyFrame();
	}

}
