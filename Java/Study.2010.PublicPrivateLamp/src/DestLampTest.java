class DeskLamp{
	private boolean isOn;
	
	public void turnOn(){
		isOn = true;
	}
	public void turnOff(){
		isOn = false;
	}
	public String toString(){
		return "ÇöÀç»óÅÂ´Â " +(isOn == true ? "ÄÑÁü" : "²¨Áü");
	}
}
public class DestLampTest {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		DeskLamp myLamp = new DeskLamp();
		
		myLamp.turnOn();
		System.out.println(myLamp);
		myLamp.turnOff();
		System.out.println(myLamp);
	}

}
