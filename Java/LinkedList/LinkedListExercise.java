import java.util.*;

//	For Test
class LinkedListExercise {	
	public static void main(String[] args)   {
		LinkedListManager l = new LinkedListManager();
		MyNode n1=new MyNode(1,"Alice",25);
		MyNode n2=new MyNode(2,"Bob",20);
		MyNode n3=new MyNode(3,"Charlie",29);
		MyNode n4=new MyNode(4,"David",23);
		l.add(n1);
		l.add(n2);
		l.add(n3);
		l.add(n4);
		
		System.out.println("Original LinkedList: ");
		l.list();
		System.out.println(" ");
		
		System.out.println("The LinkedList After Deleting the 3rd node: ");
		l.delete(3);
		l.list();
		System.out.println(" ");
		
		System.out.println("The LinkedList After insert the 3rd node: ");
		l.insert(n3);
		l.list();
	}
}

//	Define LinkedList Manager
class LinkedListManager{
	MyNode headnode=new MyNode();	// Define a head node
	
	// Add a new node to the tail
	public void add(MyNode node){
		MyNode temp=headnode;
		while(true){
			if(temp.next==null)	break;
			temp=temp.next;
		}
		temp.next=node;
	}
	
	//	Insert a new node
	public void insert(MyNode node){
		MyNode temp=headnode;
		while(true){
			if(temp.next.num>node.num) break;
			else if(temp.next==null) System.out.println("Can not find the target position");
			temp=temp.next;
		}
		node.next=temp.next;
		temp.next=node;
	}
	
	//	Delete a node in any position
	public void delete(int mark){
		MyNode temp=headnode;
		while(true){
			if(temp.next.num==mark) break;
			else if(temp.next==null) System.out.println("Error: No such node");
			temp=temp.next;
		}
		temp.next=temp.next.next;
	}
	
	//	Go through the LinkedList
	public void list(){
		MyNode temp=headnode.next;
		if(headnode.next==null) System.out.println("This is an empty LinkedList");
		while(true){
			System.out.println(temp);
			if(temp.next==null)	break;
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