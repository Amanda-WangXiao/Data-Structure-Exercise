package pkg;

import java.util.*;

public class StackCalculator {
	public static void main(String[] args) {
		var num_stack = new Stack<Integer>();
		var operator_stack = new Stack<Character>();
		
		Scanner scanner = new Scanner(System.in);
		System.out.println("Please Input your formula£º");
		String input_formula = scanner.next();
		//String input_formula = "1+2*3+8/2-6";		//5
		char[] to_be_calculated = input_formula.toCharArray();
		
		for(int i=0;i<to_be_calculated.length;i++) {
			if(to_be_calculated[i]=='+'||to_be_calculated[i]=='-'||to_be_calculated[i]=='*'||to_be_calculated[i]=='/') {
				if(operator_stack.size()==0) {
					operator_stack.push(to_be_calculated[i]);
				}
				else {
					if(checkpriority(operator_stack.peek())>=checkpriority(to_be_calculated[i])) {
						int a = num_stack.pop();
						int b = num_stack.pop();
						char o =  operator_stack.pop();
						int temp_result = calculate(b, a, o);
						if(temp_result==-1) {
							System.out.println("Error Input");
							break;
						}
						num_stack.push(temp_result);
						operator_stack.push(to_be_calculated[i]);
					}
					else operator_stack.push(to_be_calculated[i]);
				}
			}
			
			else {
					num_stack.push(to_be_calculated[i]-'0');
			}
		}
		
		while(operator_stack.size()!=0) {
			int a = num_stack.pop();
			int b = num_stack.pop();
			char o =  operator_stack.pop();
			int temp_result = calculate(b, a, o);
			num_stack.push(temp_result);
		}
		
		System.out.println("The Result is£º"+num_stack.pop());
	}
	
	public static int checkpriority(char temp) {
		if(temp=='*'||temp=='/') return 1;
		else return 0;
	}
	
	
	public static int calculate(int num1,int num2,char operator) {
		switch(operator) {
		case '+': 
			return num1+num2;
			
		case '-': 
			return num1-num2;
			
		case '*': 
			return num1*num2;
			
		case '/': 
			if(num2==0) return -1;
			else return num1/num2;
			
		default:
			return -1;
		}
	}
	
}
