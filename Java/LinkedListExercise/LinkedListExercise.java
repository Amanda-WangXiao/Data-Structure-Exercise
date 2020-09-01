import java.util.*;

//	For Test
class LinkedListExercise {	
	public static void main(String[] args)   {
		LinkedListManager l = new LinkedListManager();
		MyNode n1=new MyNode(1,"Alice",25);
		l.add(n1);
		System.out.println("Original LinkedList: ");
		l.list();
	
	}
}

//	Define LinkedList Manager
class LinkedListManager{
	MyNode headnode=new MyNode();	// Define a head node
	
	public void add(MyNode node){
		MyNode temp=headnode;
		//if(headnode.next==null) System.out.println("This is an empty LinkedList");
		while(true){
			if(temp.next==null){
				temp.next=node;
			}
			temp=temp.next;
		}
	}
	
	public void list(){
		MyNode temp=headnode.next;
		if(headnode.next==null) System.out.println("This is an empty LinkedList");
		while(true){
			System.out.println(temp);
			if(temp.next==null){
				break;
			}
			temp=temp.next;
		}
	}
}

//	Define Node Structure
class MyNode{
	int num;
	String name;
	int age;
	MyNode next;
	
	public MyNode(){
		this.num=99999;
		this.name="Anonymous";
		this.age=99999;
	}
	
	public MyNode(int num,String name,int age){
		this.num=num;
		this.name=name;
		this.age=age;
	}
	
	public String toString(){
		return "[num = "+num+", "+"name = "+name+", "+"age = "+age+"]";
	}
}