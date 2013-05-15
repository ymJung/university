import javax.swing.*;
import javax.swing.border.Border;

import java.awt.event.*;
import java.awt.*;
class MyFrame extends JFrame implements ActionListener{
	private JRadioButton top,let,bm;
	private JLabel text;
	private JPanel topPanel, sizePanel, resultPanel;
	
	public MyFrame(){
		setTitle("라디오 버튼 테스트");
		setSize(300,150);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		topPanel = new JPanel();
		JLabel label = new JLabel("어떤 커피를 주문하시겠습니까? ");
		topPanel.add(label);
		add(topPanel,BorderLayout.NORTH);
		sizePanel = new JPanel();
		top = new JRadioButton("티오피");
		let = new JRadioButton("레쓰비");
		bm = new JRadioButton("밴딩머신");
		
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
		text = new JLabel ("상표가 선택되지 않았슴다");
		text.setForeground(Color.red);
		resultPanel.add(text);
		add(resultPanel, BorderLayout.SOUTH);
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e){
		if(e.getSource() == top){
			text.setText("신민아가 선택됨");
		}
		if(e.getSource() == let){
			text.setText("싸구려 커피가 선택됨");
		}
		if(e.getSource() == bm){
			text.setText("자판기 바보커피");
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
