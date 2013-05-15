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
    //서버 화면 구성,배치 
    setTitle("== Java Encryption Chat Server");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    textarea = new JTextArea();
    add(new JScrollPane(textarea));
    textfield = new JTextField();
    textfield.setEditable(false);
    add(textfield, BorderLayout.SOUTH);
    setSize(300, 300);
    setVisible(true);
    //채팅 코드
    list = new ArrayList<MultiServerThread>();
    try {
      ServerSocket serverSocket = new ServerSocket(5000); //클라이언트 수 
      MultiServerThread mst = null; //한 사용자 담당할 채팅 객체
      boolean connectFlag = false;  //접속 깃발 값
      textfield.setText("Server is Running !\n");
      while(! connectFlag) { // 클라이언트 접속시
        clntsocket = serverSocket.accept(); //클라이언트 소켓 
        mst = new MultiServerThread();//채팅 서버 객체
        list.add(mst);//ArrayList에 채팅 객체 하나 담는다.
        mst.start();//채팅 시작
      }
    }catch (IOException e) { //예외처리
      e.printStackTrace();
    }
  }  

  //내부 처리 클래스
  class MultiServerThread extends Thread { //스레드 클래스를 상속
    private ObjectInputStream clntOIS;
    private ObjectOutputStream clntOOS;
    public void run() {
      boolean connectFlag = false;  //  flag value(깃발 값)
      try {
        clntOIS = new ObjectInputStream(clntsocket.getInputStream());
        clntOOS = new ObjectOutputStream(clntsocket.getOutputStream());
        String message = null;  //  채팅 내용을 저장할 변수 ->암호화 할것.
        while(! connectFlag) { //접속시
          message = (String)clntOIS.readObject(); //클라이언트의 스트링객체를 읽음
          String[] str = message.split("#"); //ID #를 붙임
          if(str[1].equals("exit")) { //나가겠다는 요청을 받을시
            broadCasting(message); //나간다고 알림
            connectFlag = true;  //종료
          } else { //그외의 채팅 메시지
            broadCasting(message); //모든 사용자에게 채팅 내용 전달
          }
        }
        list.remove(this); //리스트에서 사용자 제거(exit요청을 받을시)
        textarea.append(clntsocket.getInetAddress() + 
            " IP User is Exit from Server.\n");
        textfield.setText("Remain User : " + list.size()); //남은 사용자를 알림
      } catch (Exception e) {
        list.remove(this); //에러발생시
        textarea.append(clntsocket.getInetAddress() + 
            " IP User is Error ! Remove from Server.");
        textfield.setText("Remain User : " + list.size()); //남은 사용자를 알림
      }
    }
    public void broadCasting(String message) { //사용자 리스트 전체에게 메시지 전달
      for (MultiServerThread users : list)
        users.send(message); //메시지 전송(한사람씩)
    }
    public void send(String message){ //전송객체
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