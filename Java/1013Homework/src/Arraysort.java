
public class Arraysort {
	public static void main(String args[]){
		//������ �迭�� �����.		
	    int Student[][] = {
	      {97,1}, {70,1}, {100,1}, {86,1}, {98,1},
	      {99,1}, {71,1}, {77,1}, {88,1}, {91,1}};
	    
	    
	    	
	    // ������ ���Ͽ� ������ ���Ѵ�.
	    
	    /*int temp;
	    for(int i=0;i<Student.length;i++){ 
	    	for(int j=0;j<Student.length;j++){
	    		if(Student[i][0]>Student[j][0]){ //���� �չ迭�� �� �迭���� ũ��
	    			Student[i][1] = i+1; //������ ���� �迭�� ����
	    			temp = 	Student[i][0]; //������ �ӽÿ� �ְ�
	    			Student[i][0] = Student[j][0]; //�޹迭�� ������ �̵�
	    			Student[j][0] = temp; //�ӽÿ� �������� �޹迭�� �̵�
	    			
	    		}
	    	}
	    } */
	    
	    for(int i=0;i<Student.length;i++){
	    	Student[i][1]=1;	    	
	    	for(int j=0;j<Student.length;j++){
	    		if(Student[i][0]<Student[j][0]) //���� �չ迭�� �� �迭���� ũ��
	    			Student[i][1]++;
	    	}
	    }
	    	
	    //ȭ�鿡 ���	
	    System.out.println("��ȣ\t����\t����");
	    for(int i=0;i<Student.length;i++)
	    	System.out.println(i+1+"\t"+Student[i][0]+"\t"+Student[i][1]);
	    
	    
	}

}
