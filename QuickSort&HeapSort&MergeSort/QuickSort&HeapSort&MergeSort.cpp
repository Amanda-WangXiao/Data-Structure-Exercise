#include<iostream>
#include<Windows.h>
using namespace std;

template<class Record>
void QuickSort(Record Array[], int left, int right) {//��������

	if (right <= left)return;
	int pivot = SelectPivot(left, right);//ѡ����ֵ
	swap(Array, pivot, right);//�ָ�ǰ�Ƚ���ֵ�ŵ�����ĩ��
	pivot = Partition(Array, left, right);//�ָ����ֵ�ѵ�����ȷλ��
	QuickSort(Array, left, pivot - 1);//����ֵ��ߵ������н��еݹ��������
	QuickSort(Array, pivot + 1, right);//����ֵ�ұߵ������н��еݹ��������
};
int SelectPivot(int left, int right){
	return (left + right) / 2;//ѡ���м��¼��Ϊ��ֵ
};

template<class Record>
void swap(Record Array[], int pivot, int right){//����ֵ�ŵ�����ĩ��
	Record m;
	m = Array[pivot];
	Array[pivot] = Array[right];
	Array[right] = m;
};
template<class Record>
int Partition(Record Array[], int left, int right)//�ָ�����ָ����ֵ�ѵ�����ȷλ��
{
	int l = left;//lΪ��ָ��
	int r = right;//rΪ��ָ��
	Record TempRecord = Array[r];//����ֵ�������ʱ������
	while (l != r)//��ʼ�ָl��r�������м��ƶ���ֱ������
	{//lָ�������ƶ���Խ����ЩС�ڵ�����ֵ�ļ�¼��ֱ���ҵ�һ��������ֵ�ļ�¼
		while (Array[l] <= TempRecord && r>l)
			l++;
		if (l<r)
		{
			Array[r] = Array[l];
			r--;
		}
	//rָ�������ƶ���Խ����Щ���ڵ�����ֵ�ļ�¼��ֱ���ҵ�һ��С����ֵ�ļ�¼
		while (Array[r] >= TempRecord &&r>l)
			r--;
		if (l<r)//��l��rΪ������������Ԫ�ػ�����ߵĿ�λ
		{
			Array[l] = Array[r];
			l++;//lָ�������ƶ�һ��
		}
	}
	Array[l] = TempRecord;//����ֵ����ֽ�λ��l��
	return l;//���طֽ�λ��l
};
template<class T>
class MinHeap {
private:
	T *heapArray;
	int CurrentSize;
	int MaxSize;
	void swap(int pos_x, int pos_y) {
		T t;
		t = heapArray[pos_x];
		heapArray[pos_x] = heapArray[pos_y];
		heapArray[pos_y] = t;
	}
	void BuildHeap();
public:
	MinHeap(const int n);
	virtual ~MinHeap() { delete[]heapArray; }
	bool isEmpty();
	int LeftChild(int pos)const;
	int RightChild(int pos)const;
	int Parent(int pos)const;
	bool Insert(const T& newNode);
	T& RemoveMin();
	void SiftUp(int position);
	void SiftDown(int left);
};
template<class T>
MinHeap<T>::MinHeap(const int n)
{
	if (n <= 0)
		return;
	CurrentSize = 0;
	MaxSize = n;
	heapArray = new T[MaxSize];
}
template<class T>
void MinHeap<T>::BuildHeap()
{
	for (int i = CurrentSize / 2 - 1; i >= 0; i--)
		SiftDown(i);
}
template<class T>
bool MinHeap<T>::isEmpty()
{
	if (CurrentSize == 0)
		return true;
	return false;
}
template<class T>
int MinHeap<T>::LeftChild(int pos)const
{
	return 2 * pos + 1;
}
template<class T>
int MinHeap<T>::RightChild(int pos)const
{
	return 2 * pos + 2;
}
template<class T>
int MinHeap<T>::Parent(int pos)const
{
	return (pos - 1) / 2;
}
template<class T>
bool MinHeap<T>::Insert(const T& newNode)
{
	if (CurrentSize == MaxSize)
	{
		cout << "Can't insert.";
		return false;
	}
	heapArray[CurrentSize] = newNode;
	SiftUp(CurrentSize);
	CurrentSize++;
	return true;
}
template<class T>
T& MinHeap<T>::RemoveMin()
{
	if (CurrentSize == 0)
	{
		cout << "Can't Delete.";
		exit(1);
	}
	else
	{
		swap(0, --CurrentSize);
		if (CurrentSize>1)
			SiftDown(0);
		return heapArray[CurrentSize];
	}
}
template<class T>
void MinHeap<T>::SiftUp(int position)
{
	int temppos = position;
	T temp = heapArray[temppos];
	while ((temppos>0) && (heapArray[Parent(temppos)]>temp))
	{
		heapArray[temppos] = heapArray[Parent(temppos)];
		temppos = Parent(temppos);
	}
	heapArray[temppos] = temp;
}
template<class T>
void MinHeap<T>::SiftDown(int left)
{
	int i = left;
	int j = LeftChild(i);
	T temp = heapArray[i];
	while (j<CurrentSize)
	{
		if ((j<CurrentSize - 1) && (heapArray[j]>heapArray[j + 1]))
			j++;
		if (temp>heapArray[j])
		{
			heapArray[i] = heapArray[j];
			i = j;
			j = LeftChild(j);
		}
		else break;
	}
	heapArray[i] = temp;
}
template<class Record>
void MergeSort(Record Array[], Record TempArray[], int left, int right)//�鲢����
{
	int middle;
	if (left<right)//���������ֻ��0��1����¼���Ͳ�������
	{
		middle = (left + right) / 2;//���м仮��Ϊ����������
		MergeSort(Array, TempArray, left, middle);//�����һ����еݹ�
		MergeSort(Array, TempArray, middle + 1, right);//���ұ�һ����еݹ�
		Merge(Array, TempArray, left, right, middle);//���й鲢
	}
}
template<class Record>
void Merge(Record Array[], Record TempArray[], int left, int right, int middle)
{
	int i, j, index1, index2;
	for (j = left; j <= right; j++)//�������ݴ�����ʱ����
		TempArray[j] = Array[j];
	index1 = left;//��������е���ʼλ��
	index2 = middle + 1;//�ұ������е���ʼλ��
	i = left;//����ʼ�鲢
	while (index1 <= middle&&index2 <= right)
	{
		if (TempArray[index1] <= TempArray[index2])//Ϊ��֤�ȶ��ԣ����ʱ�������
			Array[i++] = TempArray[index1++];
		else Array[i++] = TempArray[index2++];
	}
	while (index1 <= middle)//ֻʣ�����У�����ֱ�Ӹ���
		Array[i++] = TempArray[index1++];
	while (index2 <= right)//���ϸ�ѭ�����⣬ֱ�Ӹ���ʣ���������
		Array[i++] = TempArray[index2++];
}
template<class Record>
void sort(Record Array[], int n) {
	int i;
	MinHeap<int> H(n);
	for (i = 0; i < n; i++)
		H.Insert(Array[i]);
	int *b = new int[n];
	for (i = 0; i < n; i++)
		b[i] = H.RemoveMin();
}
int main()
{
	int n,i;
	cout << "�������г���n" << endl;
	cin >> n;	
	int *a=new int[n];
	int *d = new int[n];
	int *c = new int[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 600000;
		d[i] = a[i];
		c[i] = a[i];
	}
	int left = 0;
	int right = n-1;
	DWORD time1 = GetTickCount();
	QuickSort(a, left, right);
	DWORD time2 = GetTickCount();
	cout << "********************************************************************" << endl;
	cout << "********************************************************************" << endl;
	cout << "��������"<<endl;
	cout << time2-time1 << endl;//����ϵͳִ��ʱ��
	cout << "********************************************************************" << endl;
	cout << "********************************************************************" << endl;
	
	DWORD time3 = GetTickCount();
	sort(d, n);
	DWORD time4 = GetTickCount();
	cout << "������" << endl;
	cout << time4-time3 << endl;//����ϵͳִ��ʱ��
	cout << "********************************************************************" << endl;
	cout << "********************************************************************" << endl;
	DWORD time5 = GetTickCount();
	int *e = new int[n];
	*e = { 0 };
	MergeSort(c, e, 0, n-1);
	DWORD time6 = GetTickCount();
	cout << "�鲢����" << endl;//�鲢����������С�Լ�ƽ��ʱ����۶�ΪO��nlogn��.
	cout << time6-time5 << endl;//����ϵͳִ��ʱ��

	system("pause");
	return 0;
}

