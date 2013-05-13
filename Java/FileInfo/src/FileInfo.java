import java.io.File;
import java.io.IOException;

public class FileInfo {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws IOException{
		// TODO Auto-generated method stub
		String name = "c:/Java";
		File dir = new File(name);
		String[] fileNames = dir.list();
		for(String s :fileNames){
			File f= new File(name + "/" + s);
			System.out.println("--Start--");
			System.out.println("Name: " + f.getName());
			System.out.println("Path: " + f.getPath());
			System.out.println("Parent : " + f.getParent());
			System.out.println("AbsolutePath : " + f.getAbsolutePath());
			System.out.println("CanonicalPath : " + f.getCanonicalPath());
			System.out.println("DirectoryNow: " + f.isDirectory());
			System.out.println("FileNow: "+f.isFile());
			System.out.println("--End--");
		}
		

	}

}
