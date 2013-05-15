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
		// 패널 생성 배치관리자를 FlowLayout으로 설정
		panel = new JPanel();
		
		//panel.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		
		/*//서로 크기가 다른 버튼 생성
		//패널에 버튼 생성 추가
		panel.add(new JButton("버튼1번"));
		panel.add(new JButton("버튼2번"));
		panel.add(new JButton("버튼3번"));
		panel.add(new JButton("4번"));
		panel.add(new JButton("긴~ 버튼 5번"));
		add(panel);
		*/
		
		
		//컨테이너를 영역화하여 각각 영역에 배치한다 
		
		/*//영역별 배치관리자
		setLayout(new BorderLayout());
		
		//버튼 추가
		add(new JButton("중앙"),BorderLayout.CENTER);
		add(new JButton("줄 시작점"),BorderLayout.LINE_START);
		add(new JButton("줄 끝점"),BorderLayout.LINE_END);
		add(new JButton("페이지 시작점"),BorderLayout.PAGE_START);
		add(new JButton("페이지 끝점"),BorderLayout.PAGE_END);
		*/
		
		/*//행이 변하는 가변행 버튼 생성
		setLayout(new GridLayout(0,3)); // 3개의 열과 가변 행 
		
		add(new JButton("버튼1"));
		add(new JButton("버튼2"));
		add(new JButton("버튼3"));
		add(new JButton("가변행 버튼 4"));
		*/
		
		//컴포넌트박스 쌓기
		
		//Y축 방향으로 박스를 쌓음
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS)); 

		makeButton(panel, "버튼 1");
		makeButton(panel, "버튼 2");
		makeButton(panel, "버튼 3");
		makeButton(panel, "4");
		makeButton(panel, "긴~ 버튼 5");
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
	pack(); // 버튼을 묶어줌
	setVisible(true);
	
	
	}*/
}
public class FlowTest {
	public static void main(String args[]){
		MyFrame f = new MyFrame();
	}

}
