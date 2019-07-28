#include<iostream>
#include<math.h>
using namespace std;

template <class T>      //������ڵ㶨�� 
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

template <class T>          //ջ����ʽʵ�� 
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
	bool pop(T&item) {      //��ջ����ʽʵ��
		Link<T>*tmp;
		if (isEmpty()) {
			cout << "ջΪ�գ�����ִ�г�ջ����" << endl;
			return false;
		}

		item = top->data;
		tmp = top->next;
		delete top;
		top = tmp;
		size--;
		return true;
	}

	bool gettop(T & item) {   //����ջ�����ݣ���������
		if (isEmpty()) {
			cout << "ջΪ�գ����ܶ�ȡջ��Ԫ��" << endl;
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
	void transform(char infix[], char suffix[], int &n);//����׺���ʽת��Ϊ��׺���ʽ
	double calculate(char suffix[],int &flag);//�ɺ�׺���ʽ�ַ���������Ӧ����ֵ���ʽ��ֵ
	double charToNum(char str[], int& i);//�������ַ���ת�����Ӧ������
	bool isOperator(char op);//�ж��Ƿ�Ϊ�����
	int opPriority(char op);//����������ȼ�

};
int main() {
	char infix[100];                       //��׺
	char suffix[100];                      //��׺
	double y;
	int flag;

	calculator x;
	int n = 0;                       //��ʼ����׺���ʽ���� 
	cout << "��������׺���ʽ��";
	cin >> infix;
	x.transform(infix, suffix, n);
                     
	cout << "��׺���ʽΪ��";
	for (int i = 0; i < n; i++)
		cout << suffix[i];

	y = x.calculate(suffix,flag);//��׺���ʽ������
	if (flag != 1)
	{
		cout << "\n���ʽ���Ϊ��";
		cout << y << endl;
	}

	system("pause"); //ʹ�������к�������˳���vs2015��
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
		else if (infix[i] == '(')//����������ֱ����ջ
			s.push(infix[i]);
		else if (infix[i] == ')')//����������ʱ����Ӧ�������ڵ��������γ�ջ
		{
			s.gettop(a);
			while (a!= '(')
			{
				s.pop(suffix[j++]);
				if (s.isEmpty()) {
					cout << "�������" << endl;
					n = 0;
					return;                                                 //δ���� ������
				}
				n++;
				s.gettop(a);
			}
			s.pop(a);
		}
		else if (isOperator(infix[i])) {
			suffix[j++] = ' ';                                                   // �ÿո�ֿ�������
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
			cout << "�������" << endl;
			break;                           //δ����������
		}
		suffix[j++] = a;
		n++;
	}

}

double calculator::charToNum(char str[], int& i) {
	double x= 0.0;
	int m = 0;
	while (str[i] >= '0' && str[i] <= '9')//������������
	{
		x = x * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')//����С������
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
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand1 + operand2);
			i++;
		}
		else if (suffix[i] == '-') {
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand2 - operand1);
			i++;
		}
		else if (suffix[i] == '*') {
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand2);
			t.push(operand1*operand2);
			i++;
		}

		else if (suffix[i] == '/') {
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			t.pop(operand1);
			if (t.isEmpty()) {
				cout << endl << "ȱ������" << endl;
				flag = 1;
				return 0;
			}
			if (abs(operand1)<1E-7) {
				cout << endl << "������󣬳�������Ϊ��" << endl;
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
