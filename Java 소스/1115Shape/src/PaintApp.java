import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.util.*;

class PaintPanel extends JComponent implements MouseListener,MouseMotionListener
{
	ArrayList<Shape> shapes = new ArrayList<Shape>();
	Point start,end;
	
	public PaintPanel(){
		addMouseListener(this);
		addMouseMotionListener(this);
	}
	public void mousePressed(MouseEvent e){
		start = new Point(e.getX(),e.getY());
		end = start;
		repaint();
	}
	public void mouseReleased(MouseEvent arg0){
		Shape r = new Ellipse2D.Float(start.x,start.y,end.x-start.x,end.y-start.y);
		shapes.add(r);
		start = null;
		end = null;
		repaint();
	}
	public void mouseDragged(MouseEvent e){
		end = new Point(e.getX(), e.getY());
		repaint();
	}
	public void mouseExited(MouseEvent arg0){}
	public void mouseClicked(MouseEvent arg0){}
	public void mouseEntered(MouseEvent arg0){}
	public void mouseMoved(MouseEvent arg0){}
	public void paint(Graphics g){
		super.paint(g);
		Graphics2D g2 = (Graphics2D) g;
		
		g2.setComposite(AlphaComposite.getInstance(AlphaComposite.SRC_OVER,0.50f));
		
		for(Shape s: shapes){
			g2.setPaint(Color.black);
			g2.draw(s);
			g2.setPaint(Color.red);
			g2.fill(s);
		}
		
		if(start != null && end != null){
			g2.setColor(Color.pink);
			g2.drawOval(start.x, start.y, end.x-start.x, end.y-start.y);
			
		}
	}
}

public class PaintApp extends JFrame {
	public PaintApp(){
		setSize(500,300);
		setTitle("Paint Board");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.add(new PaintPanel());
		this.setVisible(true);
	}
	public static void main(String[] args){
		new PaintApp();
	}

}
