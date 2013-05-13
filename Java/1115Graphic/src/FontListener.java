import java.awt.*;

public class FontListener {
	public static void main(String[] args){
		String[] font_list;
		GraphicsEnvironment g;
		g = GraphicsEnvironment.getLocalGraphicsEnvironment();
		font_list = g.getAvailableFontFamilyNames();
		for(int i=0;i<font_list.length;i++)
			System.out.println(font_list[i]);
	}

}
