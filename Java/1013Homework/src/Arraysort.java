
public class Arraysort {
	public static void main(String args[]){
		//성적을 배열로 만든다.		
	    int Student[][] = {
	      {97,1}, {70,1}, {100,1}, {86,1}, {98,1},
	      {99,1}, {71,1}, {77,1}, {88,1}, {91,1}};
	    
	    
	    	
	    // 점수를 비교하여 석차를 구한다.
	    
	    /*int temp;
	    for(int i=0;i<Student.length;i++){ 
	    	for(int j=0;j<Student.length;j++){
	    		if(Student[i][0]>Student[j][0]){ //비교후 앞배열이 뒷 배열보다 크면
	    			Student[i][1] = i+1; //순위를 석차 배열에 저장
	    			temp = 	Student[i][0]; //점수는 임시에 넣고
	    			Student[i][0] = Student[j][0]; //뒷배열이 앞으로 이동
	    			Student[j][0] = temp; //임시에 넣은것은 뒷배열로 이동
	    			
	    		}
	    	}
	    } */
	    
	    for(int i=0;i<Student.length;i++){
	    	Student[i][1]=1;	    	
	    	for(int j=0;j<Student.length;j++){
	    		if(Student[i][0]<Student[j][0]) //비교후 앞배열이 뒷 배열보다 크면
	    			Student[i][1]++;
	    	}
	    }
	    	
	    //화면에 출력	
	    System.out.println("번호\t점수\t석차");
	    for(int i=0;i<Student.length;i++)
	    	System.out.println(i+1+"\t"+Student[i][0]+"\t"+Student[i][1]);
	    
	    
	}

}
