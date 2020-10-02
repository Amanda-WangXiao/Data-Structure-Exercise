import java.util.*;
import java.lang.*;

class Exercise {
	public static void main(String[] args)   {
		var stack=new MyArrayStack<Integer>(3);
		stack.push
		
		
}
}


public class MyArrayStack<T> {
    private int top=-1;
	private int stack_size;
	
	
	public MyArrayStack(int num){
		this.stack_size=num;
		ArrayList<T> l=new ArrayList<T>(stack_size);	
	}
	
	public void push(T val){
		if(s.isFull()==false){
			top++;
			s[top]=val;
		}
		else System.out.println("Can't push: Stack is Full");
	}
	
	public T pop(T val){
		if(s.isEmpty()==false){
			T temp=s[top];
			top--;
			return temp;
		}
		else System.out.println("Can't pop: Stack is Empty");
	}
	
	public boolean isFull(){
		if(top==stack_size-1) return true;
		else return false;
	}
	
	public boolean isEmpty(){
		if(top==-1) return true;
		else return false;
	}
		
		
 }