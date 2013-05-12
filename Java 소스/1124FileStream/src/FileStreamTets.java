import java.io.*;
import java.util.*;

public class FileStreamTets {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub
		//FileInputStream in = null;
		//FileOutputStream out = null;
		//BufferedInputStream in = null;
		//BufferedOutputStream out = null;
		//DataInputStream in = null;
		//DataOutputStream out = null;
		//ObjectInputStream in = null;
		//ObjectOutputStream out = null;
		FileReader in = null;
		FileWriter out = null;
		
		/*try{
			int c;
			//out = new FileOutputStream("Out.txt",false);
			//out = new BufferedOutputStream(new FileOutputStream("Out.txt"));
			//out = new BufferedOutputStream(new FileOutputStream("Data.bin"));
			//out = new DataOutputStream(new BufferedOutputStream(new FileOutputStream("Data.bin")));
			//out = new ObjectOutputStream(new FileOutputStream("ObjectDate.txt"));
			//out.writeObject(new Date());
			
			//for(int i=0;i<10;i++){
				//out.write(i);
			//}
			out.writeDouble(3.145916);
			out.writeInt(100);
			out.writeUTF("¾È³çÇÏ½Ê´Ï±î ÄáÄá");
			out.flush();
			//in = new FileInputStream("Out.txt");
			//in = new BufferedInputStream(new FileInputStream("Out.txt"));
			//in = new DataInputStream(new BufferedInputStream(new FileInputStream("Data.bin")));
			in = new ObjectInputStream(new FileInputStream("ObjectDate.txt"));
			Date d = (Date) in.readObject();
			System.out.println(d);
			
			//while((c = in.read()) != -1){
				//System.out.println(c+ " ");
			//}
			System.out.println(in.readDouble());
			System.out.println(in.readInt());
			System.out.println(in.readUTF());
		}catch(ClassNotFoundException e){
		}finally{
			if(in!=null){
				in.close();
			}
			if(out!=null){
				out.close();
			}
			
		}*/
		String s = "²Þ²ÙÀÚ ³»ÀÏÀÌ ´Ù°¡¿Â´Ù";
		out = new FileWriter("test.txt");
		out.write(s);
		out.append('.');
		out.flush();
		in = new FileReader("test.txt");
		int c;
		while((c = in.read()) != -1){
			System.out.print((char)c);
		}
		if(in !=null)in.close();
		if(out != null)out.close();
		
		Scanner scan =null;
		PrintWriter pout = null;
		
		double sum =0;
		
		pout = new PrintWriter(new FileWriter("Output.txt"));
		pout.println("123,456,789,901");
		pout.println("9.5");
		pout.println("567,000");
		pout.flush();
		scan = new Scanner(new BufferedReader(new FileReader("Output.txt")));
		//scan.useDelimiter(",");
		while(scan.hasNext()){
			//System.out.println(scan.next());
			if(scan.hasNextDouble()){
				sum += scan.nextDouble();
			}else{
				scan.next();
			}
		}
		if(scan != null)
			scan.close();
		if(pout != null)
			pout.close();
		System.out.println(sum);
		
		

	}

}
