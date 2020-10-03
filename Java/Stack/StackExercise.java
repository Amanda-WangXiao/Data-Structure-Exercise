import java.util.*;
import java.lang.*;

class StackExercise {
	public static void main(String[] args)   {
		var my_stack=new MyArrayStack(3);
		
		System.out.println("Push 1 and 2 into the stack:");	//Push 1 and 2
		my_stack.push(1);
		my_stack.push(2);
		my_stack.ShowFullStack();
		System.out.println(" ");
		System.out.println("Is the stack full?");
		System.out.println(my_stack.isFull());
		System.out.println(" ");
		
		System.out.println("Push 3 and 4 into the stack:");	//Push 3 and 4
		my_stack.push(3);
		my_stack.push(4);	//	Cannot push
		my_stack.ShowFullStack();
		System.out.println(" ");
		System.out.println("Is the stack full?");
		System.out.println(my_stack.isFull());
		System.out.println(" ");
		
		System.out.println("Pop 2 numbers:");	//Pop 2 numbers
		my_stack.pop();
		my_stack.pop();
		my_stack.ShowFullStack();
		System.out.println(" ");
		System.out.println("Is the stack full?");
		System.out.println(my_stack.isFull());
		System.out.println("Is the stack empty?");
		System.out.println(my_stack.isEmpty());
		System.out.println(" ");
		
		System.out.println("Pop 2 numbers again:");	//Pop 2 numbers again
		my_stack.pop();
		my_stack.pop();
		my_stack.ShowFullStack();
		System.out.println(" ");
		System.out.println("Is the stack full?");
		System.out.println(my_stack.isFull());
		System.out.println("Is the stack empty?");
		System.out.println(my_stack.isEmpty());
}
}


class MyArrayStack {
    private int top=-1;
	private int stack_size;
	private int[] s;
	
	public MyArrayStack(int num){
		this.stack_size=num;
		s=new int[this.stack_size];
	}
	
	public void push(int val){
		if(isFull()==false){
			top++;
			s[top]=val;
		}
		else System.out.printf("Cannot push [value=%d] : Stack is Full\n",val);
	}
	
	public int pop(){
		int temp=-1;
		if(isEmpty()==false){
			temp=s[top];
			top--;
		}
		else System.out.println("Cannot pop: Stack is Empty");
		return temp;
	}
	
	public boolean isFull(){
		if(top==stack_size-1) return true;
		else return false;
	}
	
	public boolean isEmpty(){
		if(top==-1) return true;
		else return false;
	}

	public void ShowFullStack(){
		int temp=top;
		while(temp!=-1){
			System.out.println("top="+temp+" "+"value="+s[temp]);
			temp--;
		}
	}

}

