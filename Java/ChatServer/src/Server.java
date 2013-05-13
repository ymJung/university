import java.awt.*;
import java.io.*;   
import java.net.*;  
import java.util.*; 
import javax.swing.*;

public class Server extends JFrame {
  private ArrayList<MultiServerThread> list;
  private Socket clntsocket;
  JTextArea textarea;
  JTextField textfield;
  public Server() {
    //���� ȭ�� ����,��ġ 
    setTitle("== Java Encryption Chat Server");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    textarea = new JTextArea();
    add(new JScrollPane(textarea));
    textfield = new JTextField();
    textfield.setEditable(false);
    add(textfield, BorderLayout.SOUTH);
    setSize(300, 300);
    setVisible(true);
    //ä�� �ڵ�
    list = new ArrayList<MultiServerThread>();
    try {
      ServerSocket serverSocket = new ServerSocket(5000); //Ŭ���̾�Ʈ �� 
      MultiServerThread mst = null; //�� ����� ����� ä�� ��ü
      boolean connectFlag = false;  //���� ��� ��
      textfield.setText("Server is Running !\n");
      while(! connectFlag) { // Ŭ���̾�Ʈ ���ӽ�
        clntsocket = serverSocket.accept(); //Ŭ���̾�Ʈ ���� 
        mst = new MultiServerThread();//ä�� ���� ��ü
        list.add(mst);//ArrayList�� ä�� ��ü �ϳ� ��´�.
        mst.start();//ä�� ����
      }
    }catch (IOException e) { //����ó��
      e.printStackTrace();
    }
  }  

  //���� ó�� Ŭ����
  class MultiServerThread extends Thread { //������ Ŭ������ ���
    private ObjectInputStream clntOIS;
    private ObjectOutputStream clntOOS;
    public void run() {
      boolean connectFlag = false;  //  flag value(��� ��)
      try {
        clntOIS = new ObjectInputStream(clntsocket.getInputStream());
        clntOOS = new ObjectOutputStream(clntsocket.getOutputStream());
        String message = null;  //  ä�� ������ ������ ���� ->��ȣȭ �Ұ�.
        while(! connectFlag) { //���ӽ�
          message = (String)clntOIS.readObject(); //Ŭ���̾�Ʈ�� ��Ʈ����ü�� ����
          String[] str = message.split("#"); //ID #�� ����
          if(str[1].equals("exit")) { //�����ڴٴ� ��û�� ������
            broadCasting(message); //�����ٰ� �˸�
            connectFlag = true;  //����
          } else { //�׿��� ä�� �޽���
            broadCasting(message); //��� ����ڿ��� ä�� ���� ����
          }
        }
        list.remove(this); //����Ʈ���� ����� ����(exit��û�� ������)
        textarea.append(clntsocket.getInetAddress() + 
            " IP User is Exit from Server.\n");
        textfield.setText("Remain User : " + list.size()); //���� ����ڸ� �˸�
      } catch (Exception e) {
        list.remove(this); //�����߻���
        textarea.append(clntsocket.getInetAddress() + 
            " IP User is Error ! Remove from Server.");
        textfield.setText("Remain User : " + list.size()); //���� ����ڸ� �˸�
      }
    }
    public void broadCasting(String message) { //����� ����Ʈ ��ü���� �޽��� ����
      for (MultiServerThread users : list)
        users.send(message); //�޽��� ����(�ѻ����)
    }
    public void send(String message){ //���۰�ü
      try {
        clntOOS.writeObject(message);
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }
  public static void main(String[] args) {
	    new Server();
  }
 } 