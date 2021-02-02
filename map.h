
#include<iostream> 
#include <string>
#include<vector>
#include <iomanip>
#include"Algorithm.h"

#define _int_INFINITY 99999
#define UnDirectedGraph 1
#define DirectedGraph 0

using namespace std;

struct Edge
{
	int head, tail;//存的值为顶点的编号，用于数组时需-1 
	float Weight;
};

struct MapNode
{
	float coor[2];
	string intro;
};

void deletecinfail()
{
	if (cin.fail() == true)
	{
		string ss;
		cin.clear();//清除cin.fail()的错误状态
		cin >> ss;//取走流中的字符，避免影响下次输入
		cout  << "请输入正确格式的编号，不要乱输哦亲v_v：";
	}
	else
	{
		cout  << "请输入范围内的编号，不要乱输哦亲╰(`□′)╯：";
	}

}

class GraphMatrix
{
public:
	GraphMatrix();
	~GraphMatrix();
	//一些公有的成员函数
	void printVertex();
	void printGraph();
	void keywordSearch(string keyword);
	void searchShortPath(string now);
	int nplaceShortPath(int v,int w,int n);
	void Keyword2Vertex(int& current, string now);
private:
	//顶点集、边集、邻接矩阵、顶点数、边数
	MapNode data[18];//存放顶点数据，地图中有18个顶点
	Edge Edges[30];//图的边集 //不一定有用!!!
	float adjMatrix[18][18];//邻接矩阵
	int nVertex = 18;//18个顶点
	int nEdge = 30;//30条边
	//用于最短路径搜索、存储的变量
	float ShortPathLengthMatrix[18][18];//存放每个顶点对的路径长度
	int ShortPathMatrix[18][18];//存放每个顶点对的最短路径信息
	bool ShortPathSearched = false;
	//顶点和边的一些数据
	float coorlist[18][2] = { 0,0,3,3,5,3,3,5,0,5,-2,5,1.5,5,5,2.5,11,-1,9,1,10,2,10,3,9,-2,1,1,-0.5,2,5,-2.5,-1,2.5,5,6 };
	string introlist[18] = { "校门","A栋，教学楼Ⅰ","B栋，社科楼","C栋，机电楼","D栋，材料楼","E栋，水木楼","F栋，学术楼",
							"G栋，理学楼","H栋，主楼","J栋，活动中心","K栋，实训楼","L栋，信息楼","T栋，教学楼区" ,
							"荔园1食堂","荔园2食堂","荔园3食堂","运动场","大沙河" };
	int edgelist[30][2] = { 1,14,1,15,1,16,14,15,14,17,14,16,14,2,15,17,17,6,17,5,
							6,5,6,18,5,7,5,18,7,4,7,2,4,2,2,3,2,8,3,18,
							3,8,3,12,8,12,8,11,12,11,11,10,10,13,10,9,9,13,13,16 };
	float weightlist[30] = { 1.5, 2, 8, 2, 4, 11, 6, 2, 4, 4, 2, 11, 1, 11, 1, 3, 3, 2.5, 3, 5, 2, 6, 6, 8, 3, 1, 3, 2, 3, 5 };
	//一些私有的成员函数
	void createUnDirectGraph();
	void Floyd();
	void ShortPathPrint(int v,int w);
	int nplaceShortPathPrint(int path[][18], int num_path, float min_pathlength, int num_vertex);
	
};


GraphMatrix::GraphMatrix()
{
	createUnDirectGraph();
	//printGraph();
	cout << "地图初始化成功！祝您参观愉快~" << endl << endl;
}

GraphMatrix::~GraphMatrix()
{

}

inline void GraphMatrix::createUnDirectGraph()
{
	//初始化顶点数据
	for (int i = 0; i < nVertex; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			data[i].coor[j] = coorlist[i][j];
			//cout << coorlist[i][j] << "  ";//for test
		}
		//cout << endl;//for test
		data[i].intro = introlist[i];
	}
	//邻接矩阵初始化
	for (int i = 0; i < nVertex; i++)
	{
		for (int j = 0; j < nVertex; j++)
		{
			if (i == j)
			{
				adjMatrix[i][j] = 0;
			}
			else
			{
				adjMatrix[i][j] = _int_INFINITY;
			}
		}
	}
	//建立边
	for (int i = 0; i < nEdge; i++)
	{
		Edges[i].head = edgelist[i][0];
		Edges[i].tail = edgelist[i][1];
		Edges[i].Weight = weightlist[i];
		adjMatrix[edgelist[i][0]-1][edgelist[i][1]-1] = weightlist[i];
		adjMatrix[edgelist[i][1]-1][edgelist[i][0]-1] = weightlist[i];
	}
}

inline void GraphMatrix::printVertex()
{
	cout << setw(4) << "编号" << setw(15) << "简要介绍" << setw(8) << "坐标" << endl;
	for (int i = 0; i < nVertex; i++)
	{
		cout << setw(4) << i + 1 << setw(15) << data[i].intro << "  (" << data[i].coor[0]<<"，"<<data[i].coor[1]<<")" << endl;
	}
}

inline void GraphMatrix::printGraph()
{
	cout << "地图中建筑点个数为：" << nVertex << "  "
		<< "图中边的个数为：" << nEdge << endl
		<< "图的邻接矩阵为：" << endl;
	//输出表头行
	cout << "    ";
	for (int i = 0; i < nVertex; i++)
	{
		cout << setw(4) << i+1;
	}
	cout << endl;
	//输出表头列 及 矩阵内容
	for (int i = 0; i < nVertex; i++)
	{
		cout << setw(4) << i+1;
		for (int j = 0; j < nVertex; j++)
		{
			adjMatrix[i][j] != _int_INFINITY ? cout << setw(4) << adjMatrix[i][j] : cout << setw(4) << "∞";
		}
		cout << endl;
	}
}

inline void GraphMatrix::keywordSearch(string keyword)
{
	cout<<endl << "开始为您查找相关建筑点" << endl;
	int num=0;
	for (int i = 0; i < nVertex; i++)
	{
		if (data[i].intro.find(keyword)!=string::npos)
		{
			cout<<"  " << data[i].intro << "; 坐标（" << data[i].coor[0] << "，" << data[i].coor[1] << ")" << endl;
			num++;
		}
	}
	cout << "查找完毕，";
	if (0==num)
	{
		cout << "sorry~未找到相关建筑点" << endl << endl;
	}
	else
	{
		cout << "共找到 " << num << " 个相关建筑点" << endl << endl;
	}
}

inline void GraphMatrix::Floyd()
{
	for (int v = 0; v < nVertex; v++)
	{
		for (int w = 0; w < nVertex; w++)
		{
			//memcpy(ShortPathLengthMatrix, adjMatrix, sizeof(adjMatrix));
			ShortPathLengthMatrix[v][w] = adjMatrix[v][w];
			ShortPathMatrix[v][w] = w;
		}
	}
	for (int k= 0; k < nVertex; k++)
	{
		for (int v = 0; v < nVertex; v++)
		{
			for (int w = 0; w < nVertex; w++)
			{
				if (ShortPathLengthMatrix[v][w]> ShortPathLengthMatrix[v][k]+ ShortPathLengthMatrix[k][w])
				{
					ShortPathLengthMatrix[v][w] = ShortPathLengthMatrix[v][k] + ShortPathLengthMatrix[k][w];
					ShortPathMatrix[v][w] = ShortPathMatrix[v][k];
				}
			}
		}
	}
}

inline void GraphMatrix::ShortPathPrint(int v,int w)//起点v,终点w
{
	cout << "  去往【" << data[w].intro << "】的最短路径长度为" << ShortPathLengthMatrix[v][w]
		<< "。路径为：" << endl << "	" << data[v].intro;
	int k = ShortPathMatrix[v][w];
	while (k!=w)
	{
		cout << "->" << data[k].intro;
		k = ShortPathMatrix[k][w];
	}
	cout << "->" << data[w].intro << endl<<endl;
}

inline int GraphMatrix::nplaceShortPathPrint(int path[][18], int num_path, float min_pathlength,int num_vertex)
{
	if (num_path==0)
	{
		cout << "未找到符合要求的路径，请尝试调整途经建筑物数量n" << endl;
		return 0;
	}
	float fangxiang;
	cout << endl;
	cout << "查找到符合要求路径数量为：" << num_path << "   最短路径长度为" << min_pathlength << endl
		<< "路径信息为：" << endl;
	for (int i = 0; i < num_path; i++)
	{
		cout << "	";
		for (int j = 0; j < num_vertex-1; j++)
		{
			//cout << "【" << data[path[i][j + 1]].coor[1] << data[path[i][j]].coor[1]<<data[path[i][j + 1]].coor[0] << data[path[i][j]].coor[0] << "】";//for test
			fangxiang = atan2(data[path[i][j + 1]].coor[1] - data[path[i][j]].coor[1] , data[path[i][j + 1]].coor[0] - data[path[i][j]].coor[0]);
			cout <<"【"<< path[i][j] + 1 << "、"
				<< data[path[i][j]].intro << "。向"
				<< int(fangxiang*180.0/3.14) << "°方向走距离"
				<< adjMatrix[path[i][j]][path[i][j + 1]] << "】走到-->";
		}
		cout << "【" << path[i][num_vertex-1] + 1 << "、" << data[path[i][num_vertex-1]].intro << "】" << endl;
	}
	return 1;
}

inline void GraphMatrix::Keyword2Vertex(int& current,string now)
{
	int num, nowtemp[18];
	while (current == -1)
	{
		num = 0;
		for (int i = 0; i < nVertex; i++)
		{
			if (data[i].intro.find(now) != string::npos)
			{
				nowtemp[num] = i;
				num++;
				//cout << "  " << data[i].intro << "; 坐标（" << data[i].coor[0] << "，" << data[i].coor[1] << ")" << endl;
			}
		}
		if (0 == num)
		{
			cout << "未找到相关建筑点，请您重新输入关键字,如：“G”、“校门”等：";
			cin >> now;
		}
		if (num > 1)
		{
			for (int i = 0; i < num; i++)
			{
				cout << "  " << i + 1 << ":" << data[nowtemp[i]].intro << endl;
			}
			cout << "共找到 " << num << " 个相关建筑点，请确定您所选的建筑点，输入上述序号之一：";
			int xuhao;
			cin >> xuhao;
			while (cin.fail() == true || xuhao<1 || xuhao>num)
			{
				deletecinfail();
				cin >> xuhao;
			}
			current = nowtemp[xuhao - 1];
		}
		if (1 == num)
		{
			current = nowtemp[0];
		}
	}
	cout << "根据关键字确定的位置为：" << data[current].intro << endl<<endl;
}

inline void GraphMatrix::searchShortPath(string now)
{
	//根据关键字，确定用户当前位置
	int current=-1;
	Keyword2Vertex(current,now);
	//第一次查找时，Floyd算法计算最小路径矩阵及路径长度长度矩阵
	if (!ShortPathSearched)
	{
		Floyd();
		ShortPathSearched = true;
	}
	//得到从current出发的最短路径与目的地序列
	vector<float> PathWeightTemp(18);
	int pathsorttemp[18];
	for (int i = 0; i < nVertex; i++)
	{
		PathWeightTemp[i] = ShortPathLengthMatrix[current][i];
		pathsorttemp[i] = i;
	}
	//得到排序后的最短路径与目的地序列
	Quicksort<float>(PathWeightTemp,pathsorttemp);
	//按顺序打印最短路径及路径信息
	cout << "从当前位置("<<data[current].intro<<")查询到的可到达目的地信息为（距离从小到大排序）：" << endl<<endl;
	for (int i = 1; i < nVertex; i++)//i从1开始，排除自己到自己的路径
	{
		ShortPathPrint(current, pathsorttemp[i]);
	}
	cout << endl;
}

inline int GraphMatrix::nplaceShortPath(int v,int w,int n)//编号为v+1的建筑点为起点，w+1建筑为终点，v、w为在数组中的序号
{
	int numpath = 0, stackptr = 0, findvertexflag;//路径数量；栈顶指针
	int stack[18] , instackflag[18] , edgepassflag[18][18];//存放邻接顶点的栈；各顶点是否在栈里的标志;邻接顶点是否已访问的标志
	int Paths[18][18];//最多能找到多少条路径？未知
	float pathlength,minpathlength=_int_INFINITY;
	stack[stackptr] = v;//起点入栈
	instackflag[v] = 1;//在栈里标志置1
	stackptr++;//栈顶指针下移一位
	while (stackptr!=0)//栈不为空就说明还有路径没遍历完
	{
		////for test
		//cout << "栈顶的顶点为：" << stack[stackptr - 1] + 1 << endl;//for test
		//for (int i = 0; i < nVertex; i++)
		//{
		//	cout << instackflag[i]<<" ";
		//}
		//cout << endl;
		//for (int i = 0; i < nVertex; i++)
		//{
		//	for (int j = 0; j < nVertex; j++)
		//	{
		//		cout << edgepassflag[i][j] << " ";
		//	}
		//	cout << endl;
		//}
		////for test

		int vertexTemp = stack[stackptr - 1];//取得栈顶元素
		if (vertexTemp==w)//如果栈顶元素为目标点的序号,说明找到了一条到达目标的路径
		{
			if (stackptr == n)//如果路径中顶点数为给定的n
			{
				//计算此路径的长度
				pathlength = 0;
				for (int i = 0; i < stackptr - 1; i++)
				{
					pathlength += adjMatrix[stack[i]][stack[i + 1]];
					//cout << "路径为：" << stack[i]+1 << "->" << stack[i + 1]+1<<"  ";//for test
					//cout<<"计算过程" << pathlength ;//for test
				}
				//cout << endl;//for test
				//路径长度小于上次存进来的路径的
				if (pathlength<minpathlength)
				{
					for (int i = 0; i < stackptr; i++)
					{
						Paths[0][i] = stack[i];//将栈中存的顶点（即为当前找到的路径），放入路径结果矩阵第一行中
					}
					minpathlength = pathlength;
					numpath = 1;//路径个数为1
				}
				else if (pathlength == minpathlength)//或者路径长度等于上一次存进来的路径的
				{
					for (int i = 0; i < stackptr; i++)
					{
						Paths[numpath][i] = stack[i];//将栈中存的顶点（即为当前找到的路径），放入路径结果矩阵中
					}
					//路径数量+1
					numpath++;
				}
			}
			//清除栈顶元素w
			stackptr--;
			stack[stackptr] = -1;
			//目标顶点在栈里标志置0
			//cout << "yi  " << w << endl;//for test
			instackflag[w] = 0;
			//cout << "路径数量为：" << numpath <<"   栈内数据个数"<<stackptr<< endl;//for test
		}
		//找当前栈顶的顶点的未入栈、未访问的邻接顶点
		findvertexflag = 0;//找到满足要求的邻接顶点，标志
		for (int i = 0; i < nVertex; i++)
		{
			if (adjMatrix[stack[stackptr - 1]][i]!=0
				&& adjMatrix[stack[stackptr - 1]][i] != _int_INFINITY//找到邻接顶点
				&& instackflag[i]!=1//判断邻接顶点是否在栈里
				&& edgepassflag[stack[stackptr - 1]][i]!=1)//判断邻接顶点是否已访问
			{
				//在栈里标志置1
				//cout << i << endl;//for test
				instackflag[i] = 1;
				//已访问标志置1
				edgepassflag[stack[stackptr - 1]][i] = 1;
				//满足要求邻接顶点放入栈
				stack[stackptr] = i;
				stackptr++;
				//找到满足要求顶点标志置1
				findvertexflag = 1;
				//cout << "找到个新顶点" << i + 1 << endl;//for test
				break;
			}
		}
		if (findvertexflag==0)//如果没找到满足要求的邻接顶点，说明从该顶点出发的所有后面所有路径都已遍历完
		{
			//cout << "踢出一个找完的点" << stack[stackptr - 1] + 1;//for test
			//栈顶顶点的邻接顶点被访问过的标志置0
			for (int i = 0; i < nVertex; i++)
			{
				edgepassflag[stack[stackptr - 1]][i] = 0;
			}
			//栈顶的顶点在栈里标志置0
			//cout <<"er  "<< stack[stackptr - 1] << endl;//for test
			instackflag[stack[stackptr - 1]] = 0;
			//栈顶的顶点出栈
			stackptr--;
			stack[stackptr] = -1;
			//cout << "踢出成功" << endl;//for test
		}
		//cout << "栈顶的顶点为：" << stack[stackptr - 1]+1<<endl;//for test
		////for test
		//if (numpath==319)
		//{
		//	break;
		//}
	}
	return nplaceShortPathPrint(Paths, numpath, minpathlength, n);
}


