#include<iostream>
#include<Windows.h>
using namespace std;

template<class Record>
void QuickSort(Record Array[], int left, int right) {//快速排序

	if (right <= left)return;
	int pivot = SelectPivot(left, right);//选择轴值
	swap(Array, pivot, right);//分割前先将轴值放到数组末端
	pivot = Partition(Array, left, right);//分割后轴值已到达正确位置
	QuickSort(Array, left, pivot - 1);//对轴值左边的子序列进行递归快速排序
	QuickSort(Array, pivot + 1, right);//对轴值右边的子序列进行递归快速排序
};
int SelectPivot(int left, int right){
	return (left + right) / 2;//选择中间记录作为轴值
};

template<class Record>
void swap(Record Array[], int pivot, int right){//将轴值放到数组末端
	Record m;
	m = Array[pivot];
	Array[pivot] = Array[right];
	Array[right] = m;
};
template<class Record>
int Partition(Record Array[], int left, int right)//分割函数，分割后轴值已到达正确位置
{
	int l = left;//l为左指针
	int r = right;//r为右指针
	Record TempRecord = Array[r];//将轴值存放在临时变量中
	while (l != r)//开始分割，l、r不断向中间移动，直到相遇
	{//l指针向右移动，越过那些小于等于轴值的记录，直到找到一个大于轴值的记录
		while (Array[l] <= TempRecord && r>l)
			l++;
		if (l<r)
		{
			Array[r] = Array[l];
			r--;
		}
	//r指针向左移动，越过那些大于等于轴值的记录，直到找到一个小于轴值的记录
		while (Array[r] >= TempRecord &&r>l)
			r--;
		if (l<r)//若l、r为相遇，将逆置元素换到左边的空位
		{
			Array[l] = Array[r];
			l++;//l指针向右移动一步
		}
	}
	Array[l] = TempRecord;//把轴值回填到分界位置l上
	return l;//返回分界位置l
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
void MergeSort(Record Array[], Record TempArray[], int left, int right)//归并排序
{
	int middle;
	if (left<right)//如果序列中只有0或1个记录，就不用排序
	{
		middle = (left + right) / 2;//从中间划分为两个子序列
		MergeSort(Array, TempArray, left, middle);//对左边一半进行递归
		MergeSort(Array, TempArray, middle + 1, right);//对右边一半进行递归
		Merge(Array, TempArray, left, right, middle);//进行归并
	}
}
template<class Record>
void Merge(Record Array[], Record TempArray[], int left, int right, int middle)
{
	int i, j, index1, index2;
	for (j = left; j <= right; j++)//将数组暂存入临时数组
		TempArray[j] = Array[j];
	index1 = left;//左边子序列的起始位置
	index2 = middle + 1;//右边子序列的起始位置
	i = left;//从左开始归并
	while (index1 <= middle&&index2 <= right)
	{
		if (TempArray[index1] <= TempArray[index2])//为保证稳定性，相等时左边优先
			Array[i++] = TempArray[index1++];
		else Array[i++] = TempArray[index2++];
	}
	while (index1 <= middle)//只剩左序列，可以直接复制
		Array[i++] = TempArray[index1++];
	while (index2 <= right)//与上个循环互斥，直接复制剩余的右序列
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
	cout << "输入序列长度n" << endl;
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
	cout << "快速排序："<<endl;
	cout << time2-time1 << endl;//测试系统执行时间
	cout << "********************************************************************" << endl;
	cout << "********************************************************************" << endl;
	
	DWORD time3 = GetTickCount();
	sort(d, n);
	DWORD time4 = GetTickCount();
	cout << "堆排序：" << endl;
	cout << time4-time3 << endl;//测试系统执行时间
	cout << "********************************************************************" << endl;
	cout << "********************************************************************" << endl;
	DWORD time5 = GetTickCount();
	int *e = new int[n];
	*e = { 0 };
	MergeSort(c, e, 0, n-1);
	DWORD time6 = GetTickCount();
	cout << "归并排序：" << endl;//归并排序的最大最小以及平均时间代价都为O（nlogn）.
	cout << time6-time5 << endl;//测试系统执行时间

	system("pause");
	return 0;
}

