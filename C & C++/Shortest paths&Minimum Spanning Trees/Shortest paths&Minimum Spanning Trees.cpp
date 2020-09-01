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
	};                                        //重载赋值操作符
	bool operator> (Dist& Node)
	{
		return this->length>Node.length;
	};                                       //重载>操作符
	bool operator< (Dist& Node)
	{
		return this->length<Node.length;
	};                                       //重载<操作符
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
	int numVertex;//图中顶点的个数
	int numEdge; //图中边的条数
	int *Mark;//标记图的顶点是否被访问过
	int *Indegree;//存放图中顶点的入度
	Graph(int numVert) {                  //有参构造函数，动态创建标记和度的数组，初始化边数、度数和访问
		numVertex = numVert;
		numEdge = 0;
		Indegree = new int[numVertex];
		Mark = new int[numVertex];
		for (int i = 0; i<numVertex; i++) {
			Mark[i] = UNVISITED;
			Indegree[i] = 0;
		}
	}
	~Graph() {                                //析构函数，删除数组
		delete[]Mark;
		delete[]Indegree;
	}
	int VerticesNum() {                           //返回顶点个数
		return numVertex;
	}
	bool IsEdge(Edge oneEdge) {                     //判断是否是图的边
		if (oneEdge.weight>0 && oneEdge.weight<INFINITY&&oneEdge.to >= 0)
			return true;
		else return false;
	}
	virtual Edge FirstEdge(int oneVertex) = 0;  //返回与顶点oneVertex相关联的第一条边
	virtual Edge NextEdge(Edge preEdge) = 0;    //返回与边PreEdge有相同关联顶点oneVertex的下一条边
	int EdgesNum()                 //返回图的边数
	{
		return numEdge;
	}
	int FromVertex(Edge oneEdge)   //返回边oneEdge的始点
	{
		return oneEdge.from;
	}
	int ToVertex(Edge oneEdge)     //返回边oneEdge的终点
	{
		return oneEdge.to;
	}
	int Weight(Edge oneEdge)	   //返回边oneEdge的权
	{
		return oneEdge.weight;
	}
	virtual void setEdge(int from, int to, int weight) = 0;     //虚函数，设置边的起点终点以及权值，在子类实例化
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
void Dijkstra(Graph &G, int s) {			//s是源点
	Dist *D;
	 D = new Dist[G.VerticesNum()];					//数组D记录当前找到的最短特殊路径长度
	for (int i = 0; i < G.VerticesNum(); i++) {		//初始化Mark数组，D数组
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
	//输出
	cout << "Dijkstra算法" << endl;
	cout << endl << "起始点为" << s << "的单源最短路径如下：" << endl;
	for (int i = 0; i<G.VerticesNum(); i++) {
		if (D[i].length != INFINITY && s != i) {
			cout << "起始点" << s << "到点" << i << "的单源最短路径为：" << D[i].length << "\t前驱为：" << D[i].pre << endl;
		}
		else if (s != i) {
			cout << "起始点" << s << "到点" << i << "无路径" << endl;
		}
	}

	//删除D数组 
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
	//顶点i到顶点j的路径经过顶点v如果变短，则更新路径长度
	for (v = 0; v < G.VerticesNum(); v++)
		for (i = 0; i < G.VerticesNum(); i++)
			for (j = 0; j < G.VerticesNum();j++)
				if (D[i][j].length>(D[i][v].length + D[v][j].length)) {
					D[i][j].length = D[i][v].length + D[v][j].length;
					D[i][j].pre = D[v][j].pre;
				}
	//输出
	cout << "Floyd算法" << endl;
	cout << "                 " << endl;
	for (int i = 0; i<G.VerticesNum(); i++) {
		for (int j = 0; j<G.VerticesNum(); j++) {
			if (D[i][j].length != INFINITY && i != j) {
				cout << "点" << i << "到点" << j << "的最短路径为：" << D[i][j].length << "\t前驱为：" << D[i][j].pre << endl;
			}
			else if (i != j) {
				cout << "点" << i << "到点" << j << "无路径" << endl;
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
	int MSTtag = 0;//最小生成树的边计数
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
		if (D[v].length == INFINITY) {               // i与v无边,非连通,有不可达顶点
			cout << "该图为非连通图，无最小生成树" << endl;
			return;
		}
		//因为v的加入，需要刷新与v相邻接的顶点的D值
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
	//输出	
	cout << "Prim算法" << endl;
	cout << "                 " << endl;
	for (int i = 0; i<G.VerticesNum(); i++)
		if (i != D[i].pre)
			cout << "点" << i << "的前驱为：" << D[i].pre<< "\t其权值为：" << D[i].length << endl;
	//删除D数组 
	delete[] D;

}

template<class Elem>
class Link
{
public:
	Elem element;      //表目的数据
	Link *next;        //表目指针，指向下一个表目
	Link(const Elem& elemval, Link *nextval = NULL)  //构造函数
	{
		element = elemval; next = nextval;
	}
	Link(Link *nextval = NULL)                        //构造函数
	{
		next = nextval;
	}
};

//链表
template<class Elem>
class LList
{
public:
	Link<Elem>* head;  //head指针并不储存任何实际元素，其存在只是为了操作方便

	LList()            //构造函数
	{
		head = new Link<Elem>();
	}

	void removeall()        //释放边表所有表目占据的空间
	{
		Link<Elem> *fence;
		while (head != NULL)   //逐步释放每个表目占据的空间
		{
			fence = head;
			head = head->next;
			delete fence;
		}
	}

	~LList() { removeall(); } //析构函数
};
struct listUnit      //邻接表表目中数据部分的结构定义
{
	int vertex;      //边的终点
	int weight;      //边的权
};
class Graphl : public Graph
{
private:
	LList<listUnit> *graList;    //graList是保存所有边表的数组

public:
	Graphl(int numVert) :Graph(numVert)          //构造函数
	{
		graList = new LList<listUnit>[numVertex]; //为graList数组申请空间，图有numVertex个顶点，则有numVertex个边表
	}

	~Graphl()                                   //析构函数
	{
		delete[] graList;						//释放空间
	}

	Edge FirstEdge(int oneVertex)              //返回顶点oneVertex的第一条边
	{
		Edge myEdge;                           //边myEdge将作为函数的返回值
		myEdge.from = oneVertex;                 //将顶点oneVertex作为边myEdge的始点
		Link<listUnit> *temp = graList[oneVertex].head;  //graList[oneVertex].head保存的是顶点oneVertex的边表，temp->next指向顶点oneVertex的第一条边(如果temp->next不为null)
		if (temp->next != NULL)                   //如果顶点oneVertex的第一条边确实存在
		{
			myEdge.to = temp->next->element.vertex;
			myEdge.weight = temp->next->element.weight;
		}
		return myEdge;	                      //如果找到了顶点oneVertex的第一条边,则返回的myEdge确实是一条边;如果没有找到顶点oneVertex的第一条边,则myEdge的成员变量to为-1,根据IsEdge函数判断可知myEdge不是一条边
	}

	Edge NextEdge(Edge preEdge)               //返回与边PreEdge有相同关联顶点oneVertex的下一条边
	{
		Edge myEdge;                          //边myEdge将作为函数的返回值
		myEdge.from = preEdge.from;             //将边myEdge的始点置为与上一条边preEdge的始点相同
		Link<listUnit> *temp = graList[preEdge.from].head;           //graList[oneVertex].head保存的是顶点oneVertex的边表，temp->next指向顶点oneVertex的第一条边(如果temp->next不为null)
		while (temp->next != NULL&&temp->next->element.vertex <= preEdge.to)  //确定边preEdge在边表中的位置,如果边preEdge的下一条边确实存在，则temp->next指针指向下一条边的表目
			temp = temp->next;
		if (temp->next != NULL)                 //边preEdge的下一条边存在			                                
		{
			myEdge.to = temp->next->element.vertex;
			myEdge.weight = temp->next->element.weight;
		}
		return myEdge;
	}

	void setEdge(int from, int to, int weight)   //为图设定一条边
	{
		Link<listUnit> *temp = graList[from].head;  //graList[from].head保存的是顶点from的边表，temp->next指向顶点from的第一条边(如果temp->next不为null)
		while (temp->next != NULL&&temp->next->element.vertex<to)   //确定边(from,to)或<from,to>在边表中的位置,如果不存在,则边(from,to)或<from,to>为新加的一条边
			temp = temp->next;
		if (temp->next == NULL)                //边(from,to)或<from,to>在边表中不存在且在边表中其后已无其它边,则在边表中加入这条边
		{
			temp->next = new Link<listUnit>;
			temp->next->element.vertex = to;
			temp->next->element.weight = weight;
			numEdge++;
			Indegree[to]++;
			return;
		}
		if (temp->next->element.vertex == to) //边(from,to)或<from,to>在边表中已存在,故只需要改变边的权值
		{
			temp->next->element.weight = weight;
			return;
		}
		if (temp->next->element.vertex>to) //边(from,to)或<from,to>在边表中不存在,但在边表中其后存在其它边,则在边表中插入这条边
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

	void delEdge(int from, int to)      //删掉图的一条边
	{
		Link<listUnit> *temp = graList[from].head;      //graList[from].head保存的是顶点from的边表，temp->next指向顶点from的第一条边(如果temp->next不为null)
		while (temp->next != NULL&&temp->next->element.vertex<to)   //确定边(from,to)或<from,to>在边表中的位置(如果该边存在)
			temp = temp->next;
		if (temp->next == NULL) return;   //边(from,to)或<from,to>在边表中不存在,则不需要做任何操作	
		if (temp->next->element.vertex == to)  //边(from,to)或<from,to>在边表中存在且确定了该边在边表中的位置,则从边表中将其删掉
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
	int isDirected;                        //标记是否有向图
	int numVertex;                         //图的顶点个数（边数将在setEdge中被自动修改）
	int from, to, weight;                    //读入每条边的起点，终点和权
	char filename[20];
	Dist *D = {0};
	ifstream GraphSou;                     //输入文件流
	string str;
	cout << "************上机4*****************" << endl;
	cout << "1：输入构图的参数进行图的构造！" << endl;
	cout << "2：选择已经存好的文件进行图的构造！" << endl;
	cout << "请输入选项并按enter键继续：";
	cin >> choice;
	if (choice != 1 && choice != 2) {
		cout << "输入有误！" << endl;
		exit(0);
	}
	if (choice == 1) {
		cout << "********************************************************************" << endl;
		cout << "     0                 表示构造图为无向图，若是1则为有向图" << endl;
		cout << "     6                 表示构造图的顶点个数" << endl;
		cout << "     0 1 12            依次表示为图的起点、终点以及权值" << endl;
		cout << "     1 2 21   " << endl;
		cout << "     ......" << endl;
		cout << "********************************************************************" << endl;
		cout << "按以上格式输入构图的参数，并以#结束：" << endl;
		getline(cin, str, '#');
		cout << "请输入想要保存图的文件名：" << endl;
		cin >> filename;                         //获取文件名
		ofstream GraphSave(filename, ios::trunc);
		GraphSave << str;
		GraphSave.close();
	}
	if (choice == 2) {
		cout << "请输入文件名称（例：test.txt）：";
		cin >> filename;
	}
	GraphSou.open(filename);
	GraphSou >> isDirected;                  //是否有向
	if (isDirected != 1 && isDirected != 0)
	{
		cout << "格式不正确。" << endl;
	}

	GraphSou >> numVertex;                   //顶点个数
	Graph *myGra;                                                            //因为邻接多重表是通过邻接表来初始化的
	myGra = new Graphl(numVertex);

	while (!GraphSou.eof())                 //顺次读取边的信息
	{
		GraphSou >> from >> to >> weight;
		if (from >= 0 && to >= 0 && weight>0 && from<numVertex&&to<numVertex)  //判断从文件读出的边是否有效
		{
			myGra->setEdge(from, to, weight);
			if (!isDirected)
				myGra->setEdge(to, from, weight);
		}
		else
		{
			cout << "数据非法。" << endl;
		}
	}

	cout << endl;
	cout << "*****************所构造的图具体情况如下：****************" << endl;
	if (isDirected)
		cout << "该图为有向图。" << endl;
	else
		cout << "该图为无向图。" << endl;
	cout << "顶点数为：" << myGra->VerticesNum() << endl;
	cout << "存在边如下：" << endl;
	for (int i = 0; i<myGra->VerticesNum(); i++)
	{
		for (Edge e = myGra->FirstEdge(i); myGra->IsEdge(e); e = myGra->NextEdge(e))
		{
			cout << "起点：" << e.from << " 终点：" << e.to << " 权值：" << e.weight << endl;
		}
		cout << endl;
	}
	cout << "****************************************************************" << endl;
	cout << "输入起点s" << endl;
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


