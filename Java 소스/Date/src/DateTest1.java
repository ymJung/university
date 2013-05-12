import java.util.Scanner;

class Data{
	private int year,day;
	private String month;
	public Data(){
		month = "1월";
		day = 10;
		year = 2009;
	}
	public Data(int year,String month, int day){ //생성자
		setDate(year,month,day);
	}
	public Data(int year){
		setDate(year,"1월",10); //생성자
	}
	
	public void setDate(int year,String month, int day){
		this.month  = month; //this는 현재객체를 가르킨다
		this.day = day;
		this.year =year; 
	}
	
}

public class DateTest1 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Data date1 = new Data(2009,"3월",2);
		Data date2 = new Data(2010);
		Data date3 = new Data();

	}

}
