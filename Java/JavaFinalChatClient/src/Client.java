import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.net.*;
import javax.swing.*;

import java.security.*;
import javax.crypto.*;

public class Client implements ActionListener,Runnable {
  //  ��� ���� ����
	
	private Socket socket;          //Ŭ���̾�Ʈ ���� ���� 
	private ObjectInputStream clntOIS;  //��ü�Է½�Ʈ��
	private ObjectOutputStream clntOOS;  // ��ü��� ��Ʈ��
	private JFrame jFrame; //ȭ�鱸���� �ʿ��� ��ü ����
	private JTextField jTextfield;
	private JTextArea jTextarea;
	private JLabel jLabel1, jLabel2;
	private JPanel jPanel1, jPanel2;
	private JButton jButton;
	private String ip,id; //IP�ּҿ� ID���� ��Ʈ��
	  
	public Client(String argIp, String argID) {
		ip = argIp;  //IP
		id = argID;  //ID
	    jFrame = new JFrame("== Java Chat Program =="); 
	    jPanel1 = new JPanel(); //�ǳ� ����
	    jPanel1.setLayout(new BorderLayout()); //��ư ��ġ
	    jTextfield = new JTextField(30);  //�ؽ�Ʈ �ʵ� ũ��,��ġ
	    jButton = new JButton("--Exit--");//���� ��ư ����
	    jPanel1.add(jButton, BorderLayout.EAST);
	    jPanel1.add(jTextfield, BorderLayout.CENTER);
	    
	    jPanel2 = new JPanel(); //�ǳ� ����
	    jPanel2.setLayout(new BorderLayout());
	    jLabel1 = new JLabel("ID : [" + id + "]"); //ä�ý� ID ǥ��
	    jLabel1.setBackground(Color.WHITE);
	    jLabel2 = new JLabel("IP : " + ip);//IP
	    jLabel2.setBackground(Color.GRAY);
	    jPanel2.add(jLabel1, BorderLayout.CENTER);
	    jPanel2.add(jLabel2, BorderLayout.EAST);
	   
	    jTextarea = new JTextArea("", 10, 50);  //ä�ð���
	    jTextarea.setBackground(Color.WHITE);
	    JScrollPane jsp = new JScrollPane(jTextarea, 
	    		JScrollPane.VERTICAL_SCROLLBAR_ALWAYS,
	    		JScrollPane.HORIZONTAL_SCROLLBAR_NEVER); //������ũ�� ���� 
	    jFrame.add(jPanel1, BorderLayout.SOUTH);
	    jFrame.add(jPanel2, BorderLayout.NORTH);
	    jFrame.add(jsp, BorderLayout.CENTER);
	
	    jTextfield.addActionListener(this); //������� �Է½�
	    jButton.addActionListener(this);
	
	    jFrame.addWindowListener(new WindowAdapter() { //â����      
	    	public void windowClosing(WindowEvent e) {
	    		try {
	    			clntOOS.writeObject(id + "#exit"); //����ڰ� exit �Է½� ä�� ����
	    		} catch (Exception ee) { //���ܹ߻���
	    			ee.printStackTrace();
	    		}
	    		System.exit(0);
	    	}
	      
	    	public void windowOpened(WindowEvent e) { //����ڰ� â Ŭ���� 
	    		jTextfield.requestFocus(); //ä�ð����� ��Ŀ���� ��
	    	}
	    });
	    
	    jTextarea.setEditable(false); //�ؽ�Ʈ ������ ���� �Ұ�
	    jFrame.pack(); //âũ��� ���α׷��� �˾Ƽ� ����
	    jFrame.setResizable(true); //âũ�⺯�� ����
	    jFrame.setVisible(true); 
	}
  
	public void actionPerformed(ActionEvent e) {  //����� �Է� ó��
		Object obj = e.getSource();  //�̺�Ʈ �߻� ��ġ�� ��� ��ü
		String msg = jTextfield.getText();  //�ؽ�Ʈ �ʵ��� �ؽ�Ʈ�� �޴´�
		if(obj == jTextfield) {  //�Է½�
			if(msg == null || msg.length() == 0) {//if ������ �ΰ� �Ͻ�
				JOptionPane.showMessageDialog(jFrame, "Please Input String!","Warning", JOptionPane.WARNING_MESSAGE);
			} else { //���� �������� 
				try {
					clntOOS.writeObject(id + "#" + msg); //ID + �޽���
				} catch (Exception ee) {
					ee.printStackTrace();
				}
				jTextfield.setText(""); //ä�� �Է�â�� ����.
			}
		} else if(obj == jButton) {  // ���� ��ư�� ������� 
			try {
				clntOOS.writeObject(id + "#exit"); //exit �Է� (ä��â�� exit = ����)
			} catch (Exception ee) {
				ee.printStackTrace();
			}
			System.exit(0);
		}
	}
	public void init() {
		try {
			socket = new Socket(ip, 5000); //���� ���� (IP���,��Ʈ ����) 
			System.out.println("Connect to the Server");
			clntOOS = new ObjectOutputStream(socket.getOutputStream()); //���� ��� ��ü ����
			clntOIS = new ObjectInputStream(socket.getInputStream()); //���� �Է�  ��ü ����
			Thread t = new Thread(this); //������ ����
			t.start();  //������ ����
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	public static void main(String[] args) {
		JFrame.setDefaultLookAndFeelDecorated(true); //�⺻ ���
	
		Client cc = new Client("127.0.0.1", "Alice"); // Ŭ���̾�Ʈ ���� 
		//  Client cp = new Client("127.0.0.1", "Bob"); //
		cc.init(); //������ �ʱ�ȭ�ڵ� 
		 // cp.init();
		
	}

	public void T_DESEncryption(String str){
		try{
		
			String text = str;
			// Triple DES ����
	        KeyGenerator keyGenerator = KeyGenerator.getInstance("DESede"); 
	        keyGenerator.init(168);        // Ű�� ũ�⸦ 168��Ʈ�� �ʱ�ȭ
	        Key key = keyGenerator.generateKey();
	
	        // Cipher�� ����, ����� Ű�� �ʱ�ȭ
	        Cipher cipher = Cipher.getInstance("DESede/ECB/PKCS5Padding");
	        cipher.init(Cipher.ENCRYPT_MODE, key);
	
	        byte [] plainText = text.getBytes("UTF8");
	        
	        // ��ȣȭ ����
	        byte [] cipherText = cipher.doFinal(plainText);
	
	        // ��ȣ���� ���
	        for (int i = 0; i < cipherText.length ; i++)        {
	            System.out.print(cipherText[i] + " ");
	        }
	
	        
		}catch(Exception e){}

	}
	
	public void run() {
		
		String message = null; //�޽���
		String[] receiveMsg = null; //����� ID,�޽��� �迭
		boolean clntisConnect = false; //Ŭ���̾�Ʈ ���� �÷��� Ʈ���Ͻ� ���� 
		while(! clntisConnect) {
			try {
				
				message = (String) clntOIS.readObject(); //�Է½�Ʈ���� �޽����� ����
				T_DESEncryption(message); //���� �޽��� ��ȣȭ
				receiveMsg = message.split("#");//ID�ڿ� # ����
			} catch (Exception e) { //���� �߻���
				e.printStackTrace();
				clntisConnect = true; // ���������÷���
			}
			System.out.println(receiveMsg[0]+":"+receiveMsg[1]); //ȭ�� ���
	     
			if(receiveMsg[1].equals("exit")) {  // ����ڰ� exit �Է½� (�����Է�,�����ưŬ��)
				if(receiveMsg[0].equals(id)) {  //�������� ���������� �˸�
					System.exit(0);
				} else {  //�׿� ����ڿ��� �˸�
					jTextarea.append(receiveMsg[0] + "User is escape from Server. byebye~\n"); //�������� �˸�
					jTextarea.setCaretPosition(jTextarea.getDocument().getLength());
				}
			} else { //�Ϲ� ä��ó��
				T_DESEncryption(receiveMsg[1]); //���� �޽��� ��ȣȭ
				jTextarea.append(receiveMsg[0] + " : " +receiveMsg[1] + "\n");//ID+ �޽��� 
				jTextarea.setCaretPosition(jTextarea.getDocument().getLength()); //�޽��� ��ġ
			}
		}
	}
}
