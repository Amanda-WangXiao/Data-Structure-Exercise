#include<iostream>
#include <fstream>
#include <queue>
#include<string>
using namespace std;
#define UNVISITED 0
#define VISITED 1
#define INFINITY 99999
#define ROOT -1
class Dist {
public:
	int index;
	int length;
	int pre;
	Dist& operator= (const Dist& Node)
	{
			this->index = Node.index;
			this->length = Node.length;
			this->pre = Node.pre;
			return *this;
	};                                        //���ظ�ֵ������
	bool operator> (Dist& Node)
	{
		return this->length>Node.length;
	};                                       //����>������
	bool operator< (Dist& Node)
	{
		return this->length<Node.length;
	};                                       //����<������
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
class Edge {
public:
	int from, to, weight;
	Edge() {
		from = -1; to = -1; weight = 0;
	}
	Edge(int f, int t, int w) {
		from = f; to = t; weight = w;
	}
};
class Graph {
public:
	int numVertex;//ͼ�ж���ĸ���
	int numEdge; //ͼ�бߵ�����
	int *Mark;//���ͼ�Ķ����Ƿ񱻷��ʹ�
	int *Indegree;//���ͼ�ж�������
	Graph(int numVert) {                  //�вι��캯������̬������ǺͶȵ����飬��ʼ�������������ͷ���
		numVertex = numVert;
		numEdge = 0;
		Indegree = new int[numVertex];
		Mark = new int[numVertex];
		for (int i = 0; i<numVertex; i++) {
			Mark[i] = UNVISITED;
			Indegree[i] = 0;
		}
	}
	~Graph() {                                //����������ɾ������
		delete[]Mark;
		delete[]Indegree;
	}
	int VerticesNum() {                           //���ض������
		return numVertex;
	}
	bool IsEdge(Edge oneEdge) {                     //�ж��Ƿ���ͼ�ı�
		if (oneEdge.weight>0 && oneEdge.weight<INFINITY&&oneEdge.to >= 0)
			return true;
		else return false;
	}
	virtual Edge FirstEdge(int oneVertex) = 0;  //�����붥��oneVertex������ĵ�һ����
	virtual Edge NextEdge(Edge preEdge) = 0;    //�������PreEdge����ͬ��������oneVertex����һ����
	int EdgesNum()                 //����ͼ�ı���
	{
		return numEdge;
	}
	int FromVertex(Edge oneEdge)   //���ر�oneEdge��ʼ��
	{
		return oneEdge.from;
	}
	int ToVertex(Edge oneEdge)     //���ر�oneEdge���յ�
	{
		return oneEdge.to;
	}
	int Weight(Edge oneEdge)	   //���ر�oneEdge��Ȩ
	{
		return oneEdge.weight;
	}
	virtual void setEdge(int from, int to, int weight) = 0;     //�麯�������ñߵ�����յ��Լ�Ȩֵ��������ʵ����
	virtual void delEdge(int from, int to) = 0;
};
int minVertex(Graph &G, Dist *&D) {
	int i, v;
	for (i = 0; i < G.VerticesNum(); i++)
		if (G.Mark[i] == UNVISITED) {
			v = i;
			break;
		}
	for (i = 0; i < G.VerticesNum(); i++)
		if ((G.Mark[i] == UNVISITED) && (D[i] < D[v]))
			v = i;
	return v;
}
void Dijkstra(Graph &G, int s) {			//s��Դ��
	Dist *D;
	 D = new Dist[G.VerticesNum()];					//����D��¼��ǰ�ҵ����������·������
	for (int i = 0; i < G.VerticesNum(); i++) {		//��ʼ��Mark���飬D����
		G.Mark[i] = UNVISITED;
		D[i].index = i;
		D[i].length = INFINITY;
		D[i].pre = s;
	}
	D[s].length = 0;
	MinHeap<Dist> H(G.EdgesNum());
	H.Insert(D[s]);
	for (int i = 0; i < G.VerticesNum(); i++) {
		bool FOUND = false;
		Dist d;
		while (!H.isEmpty()) {
			d = H.RemoveMin();
			if (G.Mark[d.index] == UNVISITED) {
				FOUND = true;
				break;
			}
		}
		if (!FOUND)
			break;
		int v = d.index;
		G.Mark[v] = VISITED;
		for (Edge e = G.FirstEdge(v); G.IsEdge(e);e=G.NextEdge(e))
			if (D[G.ToVertex(e)].length>(D[v].length + G.Weight(e))) {
				D[G.ToVertex(e)].length = D[v].length + G.Weight(e);
				D[G.ToVertex(e)].pre = v;
				H.Insert(D[G.ToVertex(e)]);
			}
	}
	//���
	cout << "Dijkstra�㷨" << endl;
	cout << endl << "��ʼ��Ϊ" << s << "�ĵ�Դ���·�����£�" << endl;
	for (int i = 0; i<G.VerticesNum(); i++) {
		if (D[i].length != INFINITY && s != i) {
			cout << "��ʼ��" << s << "����" << i << "�ĵ�Դ���·��Ϊ��" << D[i].length << "\tǰ��Ϊ��" << D[i].pre << endl;
		}
		else if (s != i) {
			cout << "��ʼ��" << s << "����" << i << "��·��" << endl;
		}
	}

	//ɾ��D���� 
	delete[] D;
}
void Floyd(Graph &G) {
	int i, j, v;
	Dist **D;
	D = new Dist*[G.VerticesNum()];
	for (i = 0; i < G.VerticesNum(); i++)
		D[i] = new Dist[G.VerticesNum()];
	for (i = 0; i < G.VerticesNum(); i++)
		for (j = 0; j < G.VerticesNum(); j++) {
			if (i == j) {
				D[i][j].length = 0;
				D[i][j].pre = i;
			}
			else {
				D[i][j].length = INFINITY;
				D[i][j].pre = -1;
			}
		}
	for (v = 0; v < G.VerticesNum(); v++)
		for (Edge e = G.FirstEdge(v); G.IsEdge(e); e = G.NextEdge(e)) {
			D[v][G.ToVertex(e)].length = G.Weight(e);
			D[v][G.ToVertex(e)].pre = v;
		}
	//����i������j��·����������v�����̣������·������
	for (v = 0; v < G.VerticesNum(); v++)
		for (i = 0; i < G.VerticesNum(); i++)
			for (j = 0; j < G.VerticesNum();j++)
				if (D[i][j].length>(D[i][v].length + D[v][j].length)) {
					D[i][j].length = D[i][v].length + D[v][j].length;
					D[i][j].pre = D[v][j].pre;
				}
	//���
	cout << "Floyd�㷨" << endl;
	cout << "                 " << endl;
	for (int i = 0; i<G.VerticesNum(); i++) {
		for (int j = 0; j<G.VerticesNum(); j++) {
			if (D[i][j].length != INFINITY && i != j) {
				cout << "��" << i << "����" << j << "�����·��Ϊ��" << D[i][j].length << "\tǰ��Ϊ��" << D[i][j].pre << endl;
			}
			else if (i != j) {
				cout << "��" << i << "����" << j << "��·��" << endl;
			}
		}
	}
}
void AddEdgetoMST(Edge edge, Edge *&MST, int &MSTtag) {
	MST[MSTtag].from = edge.from;
	MST[MSTtag].to = edge.to;
	MST[MSTtag].weight = edge.weight;
}
void Prim(Graph &G, int s) {
	Edge *MST;
	int MSTtag = 0;//��С�������ı߼���
	MST = new Edge[G.VerticesNum() - 1];
	Dist *D;
	D = new Dist[G.VerticesNum()];
	for (int i = 0; i < G.VerticesNum(); i++) {
		G.Mark[i] = UNVISITED;
		D[i].index = i;
		D[i].length = INFINITY;
		D[i].pre = s;
	}
	D[s].length = 0;
	G.Mark[s] = VISITED;
	int v = s;
	for (int i = 0; i < G.VerticesNum() - 1; i++) {
		if (D[v].length == INFINITY) {               // i��v�ޱ�,����ͨ,�в��ɴﶥ��
			cout << "��ͼΪ����ͨͼ������С������" << endl;
			return;
		}
		//��Ϊv�ļ��룬��Ҫˢ����v���ڽӵĶ����Dֵ
		for (Edge e = G.FirstEdge(v); G.IsEdge(e);e=G.NextEdge(e))
			if (G.Mark[G.ToVertex(e)] != VISITED && (D[G.ToVertex(e)].length>e.weight)) {
				D[G.ToVertex(e)].length = e.weight;
				D[G.ToVertex(e)].pre = v;
			}
		v = minVertex(G, D);
		G.Mark[v] = VISITED;
		Edge edge(D[v].pre, D[v].index, D[v].length);
		AddEdgetoMST(edge,MST,MSTtag);
	}
	//���	
	cout << "Prim�㷨" << endl;
	cout << "                 " << endl;
	for (int i = 0; i<G.VerticesNum(); i++)
		if (i != D[i].pre)
			cout << "��" << i << "��ǰ��Ϊ��" << D[i].pre<< "\t��ȨֵΪ��" << D[i].length << endl;
	//ɾ��D���� 
	delete[] D;

}

template<class Elem>
class Link
{
public:
	Elem element;      //��Ŀ������
	Link *next;        //��Ŀָ�룬ָ����һ����Ŀ
	Link(const Elem& elemval, Link *nextval = NULL)  //���캯��
	{
		element = elemval; next = nextval;
	}
	Link(Link *nextval = NULL)                        //���캯��
	{
		next = nextval;
	}
};

//����
template<class Elem>
class LList
{
public:
	Link<Elem>* head;  //headָ�벢�������κ�ʵ��Ԫ�أ������ֻ��Ϊ�˲�������

	LList()            //���캯��
	{
		head = new Link<Elem>();
	}

	void removeall()        //�ͷű߱����б�Ŀռ�ݵĿռ�
	{
		Link<Elem> *fence;
		while (head != NULL)   //���ͷ�ÿ����Ŀռ�ݵĿռ�
		{
			fence = head;
			head = head->next;
			delete fence;
		}
	}

	~LList() { removeall(); } //��������
};
struct listUnit      //�ڽӱ��Ŀ�����ݲ��ֵĽṹ����
{
	int vertex;      //�ߵ��յ�
	int weight;      //�ߵ�Ȩ
};
class Graphl : public Graph
{
private:
	LList<listUnit> *graList;    //graList�Ǳ������б߱������

public:
	Graphl(int numVert) :Graph(numVert)          //���캯��
	{
		graList = new LList<listUnit>[numVertex]; //ΪgraList��������ռ䣬ͼ��numVertex�����㣬����numVertex���߱�
	}

	~Graphl()                                   //��������
	{
		delete[] graList;						//�ͷſռ�
	}

	Edge FirstEdge(int oneVertex)              //���ض���oneVertex�ĵ�һ����
	{
		Edge myEdge;                           //��myEdge����Ϊ�����ķ���ֵ
		myEdge.from = oneVertex;                 //������oneVertex��Ϊ��myEdge��ʼ��
		Link<listUnit> *temp = graList[oneVertex].head;  //graList[oneVertex].head������Ƕ���oneVertex�ı߱�temp->nextָ�򶥵�oneVertex�ĵ�һ����(���temp->next��Ϊnull)
		if (temp->next != NULL)                   //�������oneVertex�ĵ�һ����ȷʵ����
		{
			myEdge.to = temp->next->element.vertex;
			myEdge.weight = temp->next->element.weight;
		}
		return myEdge;	                      //����ҵ��˶���oneVertex�ĵ�һ����,�򷵻ص�myEdgeȷʵ��һ����;���û���ҵ�����oneVertex�ĵ�һ����,��myEdge�ĳ�Ա����toΪ-1,����IsEdge�����жϿ�֪myEdge����һ����
	}

	Edge NextEdge(Edge preEdge)               //�������PreEdge����ͬ��������oneVertex����һ����
	{
		Edge myEdge;                          //��myEdge����Ϊ�����ķ���ֵ
		myEdge.from = preEdge.from;             //����myEdge��ʼ����Ϊ����һ����preEdge��ʼ����ͬ
		Link<listUnit> *temp = graList[preEdge.from].head;           //graList[oneVertex].head������Ƕ���oneVertex�ı߱�temp->nextָ�򶥵�oneVertex�ĵ�һ����(���temp->next��Ϊnull)
		while (temp->next != NULL&&temp->next->element.vertex <= preEdge.to)  //ȷ����preEdge�ڱ߱��е�λ��,�����preEdge����һ����ȷʵ���ڣ���temp->nextָ��ָ����һ���ߵı�Ŀ
			temp = temp->next;
		if (temp->next != NULL)                 //��preEdge����һ���ߴ���			                                
		{
			myEdge.to = temp->next->element.vertex;
			myEdge.weight = temp->next->element.weight;
		}
		return myEdge;
	}

	void setEdge(int from, int to, int weight)   //Ϊͼ�趨һ����
	{
		Link<listUnit> *temp = graList[from].head;  //graList[from].head������Ƕ���from�ı߱�temp->nextָ�򶥵�from�ĵ�һ����(���temp->next��Ϊnull)
		while (temp->next != NULL&&temp->next->element.vertex<to)   //ȷ����(from,to)��<from,to>�ڱ߱��е�λ��,���������,���(from,to)��<from,to>Ϊ�¼ӵ�һ����
			temp = temp->next;
		if (temp->next == NULL)                //��(from,to)��<from,to>�ڱ߱��в��������ڱ߱����������������,���ڱ߱��м���������
		{
			temp->next = new Link<listUnit>;
			temp->next->element.vertex = to;
			temp->next->element.weight = weight;
			numEdge++;
			Indegree[to]++;
			return;
		}
		if (temp->next->element.vertex == to) //��(from,to)��<from,to>�ڱ߱����Ѵ���,��ֻ��Ҫ�ı�ߵ�Ȩֵ
		{
			temp->next->element.weight = weight;
			return;
		}
		if (temp->next->element.vertex>to) //��(from,to)��<from,to>�ڱ߱��в�����,���ڱ߱���������������,���ڱ߱��в���������
		{
			Link<listUnit> *other = temp->next;
			temp->next = new Link<listUnit>;
			temp->next->element.vertex = to;
			temp->next->element.weight = weight;
			temp->next->next = other;
			numEdge++;
			Indegree[to]++;
		}
	}

	void delEdge(int from, int to)      //ɾ��ͼ��һ����
	{
		Link<listUnit> *temp = graList[from].head;      //graList[from].head������Ƕ���from�ı߱�temp->nextָ�򶥵�from�ĵ�һ����(���temp->next��Ϊnull)
		while (temp->next != NULL&&temp->next->element.vertex<to)   //ȷ����(from,to)��<from,to>�ڱ߱��е�λ��(����ñߴ���)
			temp = temp->next;
		if (temp->next == NULL) return;   //��(from,to)��<from,to>�ڱ߱��в�����,����Ҫ���κβ���	
		if (temp->next->element.vertex == to)  //��(from,to)��<from,to>�ڱ߱��д�����ȷ���˸ñ��ڱ߱��е�λ��,��ӱ߱��н���ɾ��
		{
			Link<listUnit> *other = temp->next->next;
			delete temp->next;
			temp->next = other;
			numEdge--;
			Indegree[to]--;
		}
	}
};
int main() {
	int choice,s;
	int isDirected;                        //����Ƿ�����ͼ
	int numVertex;                         //ͼ�Ķ����������������setEdge�б��Զ��޸ģ�
	int from, to, weight;                    //����ÿ���ߵ���㣬�յ��Ȩ
	char filename[20];
	Dist *D = {0};
	ifstream GraphSou;                     //�����ļ���
	string str;
	cout << "************�ϻ�4*****************" << endl;
	cout << "1�����빹ͼ�Ĳ�������ͼ�Ĺ��죡" << endl;
	cout << "2��ѡ���Ѿ���õ��ļ�����ͼ�Ĺ��죡" << endl;
	cout << "������ѡ���enter��������";
	cin >> choice;
	if (choice != 1 && choice != 2) {
		cout << "��������" << endl;
		exit(0);
	}
	if (choice == 1) {
		cout << "********************************************************************" << endl;
		cout << "     0                 ��ʾ����ͼΪ����ͼ������1��Ϊ����ͼ" << endl;
		cout << "     6                 ��ʾ����ͼ�Ķ������" << endl;
		cout << "     0 1 12            ���α�ʾΪͼ����㡢�յ��Լ�Ȩֵ" << endl;
		cout << "     1 2 21   " << endl;
		cout << "     ......" << endl;
		cout << "********************************************************************" << endl;
		cout << "�����ϸ�ʽ���빹ͼ�Ĳ���������#������" << endl;
		getline(cin, str, '#');
		cout << "��������Ҫ����ͼ���ļ�����" << endl;
		cin >> filename;                         //��ȡ�ļ���
		ofstream GraphSave(filename, ios::trunc);
		GraphSave << str;
		GraphSave.close();
	}
	if (choice == 2) {
		cout << "�������ļ����ƣ�����test.txt����";
		cin >> filename;
	}
	GraphSou.open(filename);
	GraphSou >> isDirected;                  //�Ƿ�����
	if (isDirected != 1 && isDirected != 0)
	{
		cout << "��ʽ����ȷ��" << endl;
	}

	GraphSou >> numVertex;                   //�������
	Graph *myGra;                                                            //��Ϊ�ڽӶ��ر���ͨ���ڽӱ�����ʼ����
	myGra = new Graphl(numVertex);

	while (!GraphSou.eof())                 //˳�ζ�ȡ�ߵ���Ϣ
	{
		GraphSou >> from >> to >> weight;
		if (from >= 0 && to >= 0 && weight>0 && from<numVertex&&to<numVertex)  //�жϴ��ļ������ı��Ƿ���Ч
		{
			myGra->setEdge(from, to, weight);
			if (!isDirected)
				myGra->setEdge(to, from, weight);
		}
		else
		{
			cout << "���ݷǷ���" << endl;
		}
	}

	cout << endl;
	cout << "*****************�������ͼ����������£�****************" << endl;
	if (isDirected)
		cout << "��ͼΪ����ͼ��" << endl;
	else
		cout << "��ͼΪ����ͼ��" << endl;
	cout << "������Ϊ��" << myGra->VerticesNum() << endl;
	cout << "���ڱ����£�" << endl;
	for (int i = 0; i<myGra->VerticesNum(); i++)
	{
		for (Edge e = myGra->FirstEdge(i); myGra->IsEdge(e); e = myGra->NextEdge(e))
		{
			cout << "��㣺" << e.from << " �յ㣺" << e.to << " Ȩֵ��" << e.weight << endl;
		}
		cout << endl;
	}
	cout << "****************************************************************" << endl;
	cout << "�������s" << endl;
	cin >> s;
	cout << "                 " << endl;
	Dijkstra(*myGra, s);
	cout << "                 " << endl;
	Floyd(*myGra);
	cout << "                 " << endl;
	Prim(*myGra, s);
	cout << "****************************************************************" << endl;
	system("pause");
	return 0;
}


