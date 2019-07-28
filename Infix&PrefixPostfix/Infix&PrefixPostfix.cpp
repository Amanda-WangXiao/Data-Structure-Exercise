#include<iostream>
#include<math.h>
using namespace std;

template <class T>      //单链表节点定义 
class Link {
public:
	T data;
	Link<T> * next;

	Link(const T info, Link<T>*nextValue = NULL) {
		data = info;
		next = nextValue;
	}
	Link(const Link<T>*nextValue) {
		next = nextValue;
	}
};

template <class T>          //栈的链式实现 
class lnkStack {
private:
	Link<T>* top;
	int size;
public:
	lnkStack() {
		top = NULL;
		size = 0;
	}
	~lnkStack() {
		clear();
	}
	void clear() {
		while (top != NULL) {
			Link<T>* tmp = top;
			top = top->next;
			delete tmp;
		}
		size = 0;
	}
	bool push(const T item) {
		Link <T> * tmp = new Link<T>(item, top);
		top = tmp;
		size++;
		return true;
	}
	bool pop(T&item) {      //出栈的链式实现
		Link<T>*tmp;
		if (isEmpty()) {
			cout << "栈为空，不能执行出栈操作" << endl;
			return false;
		}

		item = top->data;
		tmp = top->next;
		delete top;
		top = tmp;
		size--;
		return true;
	}

	bool gettop(T & item) {   //返回栈顶内容，但不弹出
		if (isEmpty()) {
			cout << "栈为空，不能读取栈顶元素" << endl;
			return false;
		}
		item = top->data;
		return true;
	}

	bool isEmpty() {
		if (size == 0)
			return true;
		else
			return false;
	}


};

class calculator {
private:
	lnkStack<char> s;
	lnkStack<double> t;
public:
	void transform(char infix[], char suffix[], int &n);//把中缀表达式转换为后缀表达式
	double calculate(char suffix[],int &flag);//由后缀表达式字符串计算相应的中值表达式的值
	double charToNum(char str[], int& i);//将数字字符串转变成相应的数字
	bool isOperator(char op);//判断是否为运算符
	int opPriority(char op);//求运算符优先级

};
int main() {
	char infix[100];                       //中缀
	char suffix[100];                      //后缀
	double y;
	int flag;

	calculator x;
	int n = 0;                       //初始化后缀表达式长度 
	cout << "请输入中缀表达式：";
	cin >> infix;
	x.transform(infix, suffix, n);
                     
	cout << "后缀表达式为：";
	for (int i = 0; i < n; i++)
		cout << suffix[i];

	y = x.calculate(suffix,flag);//后缀表达式计算结果
	if (flag != 1)
	{
		cout << "\n表达式结果为：";
		cout << y << endl;
	}

	system("pause"); //使程序运行后按任意键退出（vs2015）
	return 0;

}
bool calculator::isOperator(char op) {
	if (op == '+' || op == '-' || op == '*' || op == '/')
		return true;
	else
		return false;
}
int calculator::opPriority(char op) {
	switch (op)
	{
	case '#':
		return -1;
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return -1;
	}
}

void calculator::transform(char infix[], char suffix[], int &n) {

	int i = 0, j = 0;
	int flag = 0;
	char a;
	s.push('#');

	while (infix[i] != '\0') {
		if (infix[i] >= '0' && infix[i] <= '9' || infix[i] == '.') 
		{
			suffix[j++] = infix[i];
			n++;
		}
		else if (infix[i] == '(')//遇到“（”直接入栈
			s.push(infix[i]);
		else if (infix[i] == ')')//遇到“）”时将对应左括号内的内容依次出栈
		{
			s.gettop(a);
			while (a!= '(')
			{
				s.pop(suffix[j++]);
				if (s.isEmpty()) {
					cout << "输入错误" << endl;
					n = 0;
					return;                                                 //未遇到 左括号
				}
				n++;
				s.gettop(a);
			}
			s.pop(a);
		}
		else if (isOperator(infix[i])) {
			suffix[j++] = ' ';                                                   // 用空格分开操作数
			n++;
			s.gettop(a);
			while (!s.isEmpty() && opPriority(a) >= opPriority(infix[i])) {
				s.pop(a);
				suffix[j++] = a;
				s.gettop(a);
				n++;
			}
			s.push(infix[i]);
		}

		i++;
	}

	while (!s.isEmpty()) {
		s.pop(a);
		if (a == '(') {
			cout << "输入错误" << endl;
			break;                           //未遇到左括号
		}
		suffix[j++] = a;
		n++;
	}

}

double calculator::charToNum(char str[], int& i) {
	double x= 0.0;
	int m = 0;
	while (str[i] >= '0' && str[i] <= '9')//处理整数部分
	{
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')//处理小数部分
	{
		i++;
		while (str[i] >= '0'&&str[i] <= '9')
		{
			x = x * 10 + (str[i] - '0');
			i++;
			m++;
		}
	}
	while (m != 0)
	{
		x/= 10.0;
		m--;
	}
	return x;
}

double calculator::calculate(char suffix[],int &flag) {
	int i = 0;
	double operand1, operand2, result;

	while (suffix[i] != '#') {
		if (suffix[i] >= '0'&&suffix[i] <= '9') {
			t.push(charToNum(suffix, i));
		}

		else if (suffix[i] == ' ')
			i++;
		else if (suffix[i] == '+') {
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand1 + operand2);
			i++;
		}
		else if (suffix[i] == '-') {
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand2 - operand1);
			i++;
		}
		else if (suffix[i] == '*') {
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand1*operand2);
			i++;
		}

		else if (suffix[i] == '/') {
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "缺少数据" << endl;
				flag = 1;
				return 0;
			}
			if (abs(operand1)<1E-7) {
				cout << endl << "输入错误，除数不能为零" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand2 / operand1);
			i++;
		}
	}
	t.gettop(result);
	return result;

}
