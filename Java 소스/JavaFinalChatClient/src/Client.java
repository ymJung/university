import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import javax.swing.*;

import java.security.*;
import javax.crypto.*;

public class Client implements ActionListener,Runnable {
  //  멤버 변수 정의
	
	private Socket socket;          //클라이언트 접속 소켓 
	private ObjectInputStream clntOIS;  //객체입력스트림
	private ObjectOutputStream clntOOS;  // 객체출력 스트림
	private JFrame jFrame; //화면구성에 필요한 객체 선언
	private JTextField jTextfield;
	private JTextArea jTextarea;
	private JLabel jLabel1, jLabel2;
	private JPanel jPanel1, jPanel2;
	private JButton jButton;
	private String ip,id; //IP주소와 ID저장 스트링
	  
	public Client(String argIp, String argID) {
		ip = argIp;  //IP
		id = argID;  //ID
	    jFrame = new JFrame("== Java Chat Program =="); 
	    jPanel1 = new JPanel(); //판넬 선언
	    jPanel1.setLayout(new BorderLayout()); //버튼 배치
	    jTextfield = new JTextField(30);  //텍스트 필드 크기,배치
	    jButton = new JButton("--Exit--");//종료 버튼 생성
	    jPanel1.add(jButton, BorderLayout.EAST);
	    jPanel1.add(jTextfield, BorderLayout.CENTER);
	    
	    jPanel2 = new JPanel(); //판넬 선언
	    jPanel2.setLayout(new BorderLayout());
	    jLabel1 = new JLabel("ID : [" + id + "]"); //채팅시 ID 표시
	    jLabel1.setBackground(Color.WHITE);
	    jLabel2 = new JLabel("IP : " + ip);//IP
	    jLabel2.setBackground(Color.GRAY);
	    jPanel2.add(jLabel1, BorderLayout.CENTER);
	    jPanel2.add(jLabel2, BorderLayout.EAST);
	   
	    jTextarea = new JTextArea("", 10, 50);  //채팅공간
	    jTextarea.setBackground(Color.WHITE);
	    JScrollPane jsp = new JScrollPane(jTextarea, 
	    		JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
	    		JScrollPane.HORIZONTAL_SCROLLBAR_NEVER); //수직스크롤 설정 
	    jFrame.add(jPanel1, BorderLayout.SOUTH);
	    jFrame.add(jPanel2, BorderLayout.NORTH);
	    jFrame.add(jsp, BorderLayout.CENTER);
	
	    jTextfield.addActionListener(this); //사용자의 입력시
	    jButton.addActionListener(this);
	
	    jFrame.addWindowListener(new WindowAdapter() { //창관리      
	    	public void windowClosing(WindowEvent e) {
	    		try {
	    			clntOOS.writeObject(id + "#exit"); //사용자가 exit 입력시 채팅 종료
	    		} catch (Exception ee) { //예외발생시
	    			ee.printStackTrace();
	    		}
	    		System.exit(0);
	    	}
	      
	    	public void windowOpened(WindowEvent e) { //사용자가 창 클릭시 
	    		jTextfield.requestFocus(); //채팅공간에 포커스를 줌
	    	}
	    });
	    
	    jTextarea.setEditable(false); //텍스트 공간은 편집 불가
	    jFrame.pack(); //창크기는 프로그램이 알아서 지정
	    jFrame.setResizable(true); //창크기변경 가능
	    jFrame.setVisible(true); 
	}
  
	public void actionPerformed(ActionEvent e) {  //사용자 입력 처리
		Object obj = e.getSource();  //이벤트 발생 위치를 얻는 객체
		String msg = jTextfield.getText();  //텍스트 필드의 텍스트를 받는다
		if(obj == jTextfield) {  //입력시
			if(msg == null || msg.length() == 0) {//if 내용이 널값 일시
				JOptionPane.showMessageDialog(jFrame, "Please Input String!","Warning", JOptionPane.WARNING_MESSAGE);
			} else { //값이 들어왔을시 
				try {
					clntOOS.writeObject(id + "#" + msg); //ID + 메시지
				} catch (Exception ee) {
					ee.printStackTrace();
				}
				jTextfield.setText(""); //채팅 입력창을 비운다.
			}
		} else if(obj == jButton) {  // 종료 버튼을 누른경우 
			try {
				clntOOS.writeObject(id + "#exit"); //exit 입력 (채팅창에 exit = 종료)
			} catch (Exception ee) {
				ee.printStackTrace();
			}
			System.exit(0);
		}
	}
	public void init() {
		try {
			socket = new Socket(ip, 5000); //소켓 설정 (IP사용,포트 설정) 
			System.out.println("Connect to the Server");
			clntOOS = new ObjectOutputStream(socket.getOutputStream()); //소켓 출력 객체 선언
			clntOIS = new ObjectInputStream(socket.getInputStream()); //소켓 입력  객체 선언
			Thread t = new Thread(this); //쓰레드 선언
			t.start();  //쓰레드 시작
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		JFrame.setDefaultLookAndFeelDecorated(true); //기본 장식
	
		Client cc = new Client("127.0.0.1", "Alice"); // 클라이언트 실행 
		//  Client cp = new Client("127.0.0.1", "Bob"); //
		cc.init(); //쓰레드 초기화코드 
		 // cp.init();
		
	}

	public void T_DESEncryption(String str){
		try{
		
			String text = str;
			// Triple DES 생성
	        KeyGenerator keyGenerator = KeyGenerator.getInstance("DESede"); 
	        keyGenerator.init(168);        // 키의 크기를 168비트로 초기화
	        Key key = keyGenerator.generateKey();
	
	        // Cipher를 생성, 사용할 키로 초기화
	        Cipher cipher = Cipher.getInstance("DESede/ECB/PKCS5Padding");
	        cipher.init(Cipher.ENCRYPT_MODE, key);
	
	        byte [] plainText = text.getBytes("UTF8");
	        
	        // 암호화 시작
	        byte [] cipherText = cipher.doFinal(plainText);
	
	        // 암호문서 출력
	        for (int i = 0; i < cipherText.length ; i++)        {
	            System.out.print(cipherText[i] + " ");
	        }
	
	        
		}catch(Exception e){}

	}
	
	public void run() {
		
		String message = null; //메시지
		String[] receiveMsg = null; //사용자 ID,메시지 배열
		boolean clntisConnect = false; //클라이언트 접속 플래그 트루일시 중지 
		while(! clntisConnect) {
			try {
				
				message = (String) clntOIS.readObject(); //입력스트림의 메시지를 읽음
				T_DESEncryption(message); //전송 메시지 암호화
				receiveMsg = message.split("#");//ID뒤에 # 붙임
			} catch (Exception e) { //예외 발생시
				e.printStackTrace();
				clntisConnect = true; // 접속종료플래그
			}
			System.out.println(receiveMsg[0]+":"+receiveMsg[1]); //화면 출력
	     
			if(receiveMsg[1].equals("exit")) {  // 사용자가 exit 입력시 (직접입력,종료버튼클릭)
				if(receiveMsg[0].equals(id)) {  //서버에게 종료했음을 알림
					System.exit(0);
				} else {  //그외 사용자에게 알림
					jTextarea.append(receiveMsg[0] + "User is escape from Server. byebye~\n"); //떠났음을 알림
					jTextarea.setCaretPosition(jTextarea.getDocument().getLength());
				}
			} else { //일반 채팅처리
				T_DESEncryption(receiveMsg[1]); //수신 메시지 복호화
				jTextarea.append(receiveMsg[0] + " : " +receiveMsg[1] + "\n");//ID+ 메시지 
				jTextarea.setCaretPosition(jTextarea.getDocument().getLength()); //메시지 위치
			}
		}
	}
}
