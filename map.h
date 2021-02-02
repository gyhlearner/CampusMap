
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
	int head, tail;//���ֵΪ����ı�ţ���������ʱ��-1 
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
		cin.clear();//���cin.fail()�Ĵ���״̬
		cin >> ss;//ȡ�����е��ַ�������Ӱ���´�����
		cout  << "��������ȷ��ʽ�ı�ţ���Ҫ����Ŷ��v_v��";
	}
	else
	{
		cout  << "�����뷶Χ�ڵı�ţ���Ҫ����Ŷ�רt(`����)�s��";
	}

}

class GraphMatrix
{
public:
	GraphMatrix();
	~GraphMatrix();
	//һЩ���еĳ�Ա����
	void printVertex();
	void printGraph();
	void keywordSearch(string keyword);
	void searchShortPath(string now);
	int nplaceShortPath(int v,int w,int n);
	void Keyword2Vertex(int& current, string now);
private:
	//���㼯���߼����ڽӾ��󡢶�����������
	MapNode data[18];//��Ŷ������ݣ���ͼ����18������
	Edge Edges[30];//ͼ�ı߼� //��һ������!!!
	float adjMatrix[18][18];//�ڽӾ���
	int nVertex = 18;//18������
	int nEdge = 30;//30����
	//�������·���������洢�ı���
	float ShortPathLengthMatrix[18][18];//���ÿ������Ե�·������
	int ShortPathMatrix[18][18];//���ÿ������Ե����·����Ϣ
	bool ShortPathSearched = false;
	//����ͱߵ�һЩ����
	float coorlist[18][2] = { 0,0,3,3,5,3,3,5,0,5,-2,5,1.5,5,5,2.5,11,-1,9,1,10,2,10,3,9,-2,1,1,-0.5,2,5,-2.5,-1,2.5,5,6 };
	string introlist[18] = { "У��","A������ѧ¥��","B�������¥","C��������¥","D��������¥","E����ˮľ¥","F����ѧ��¥",
							"G������ѧ¥","H������¥","J���������","K����ʵѵ¥","L������Ϣ¥","T������ѧ¥��" ,
							"��԰1ʳ��","��԰2ʳ��","��԰3ʳ��","�˶���","��ɳ��" };
	int edgelist[30][2] = { 1,14,1,15,1,16,14,15,14,17,14,16,14,2,15,17,17,6,17,5,
							6,5,6,18,5,7,5,18,7,4,7,2,4,2,2,3,2,8,3,18,
							3,8,3,12,8,12,8,11,12,11,11,10,10,13,10,9,9,13,13,16 };
	float weightlist[30] = { 1.5, 2, 8, 2, 4, 11, 6, 2, 4, 4, 2, 11, 1, 11, 1, 3, 3, 2.5, 3, 5, 2, 6, 6, 8, 3, 1, 3, 2, 3, 5 };
	//һЩ˽�еĳ�Ա����
	void createUnDirectGraph();
	void Floyd();
	void ShortPathPrint(int v,int w);
	int nplaceShortPathPrint(int path[][18], int num_path, float min_pathlength, int num_vertex);
	
};


GraphMatrix::GraphMatrix()
{
	createUnDirectGraph();
	//printGraph();
	cout << "��ͼ��ʼ���ɹ���ף���ι����~" << endl << endl;
}

GraphMatrix::~GraphMatrix()
{

}

inline void GraphMatrix::createUnDirectGraph()
{
	//��ʼ����������
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
	//�ڽӾ����ʼ��
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
	//������
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
	cout << setw(4) << "���" << setw(15) << "��Ҫ����" << setw(8) << "����" << endl;
	for (int i = 0; i < nVertex; i++)
	{
		cout << setw(4) << i + 1 << setw(15) << data[i].intro << "  (" << data[i].coor[0]<<"��"<<data[i].coor[1]<<")" << endl;
	}
}

inline void GraphMatrix::printGraph()
{
	cout << "��ͼ�н��������Ϊ��" << nVertex << "  "
		<< "ͼ�бߵĸ���Ϊ��" << nEdge << endl
		<< "ͼ���ڽӾ���Ϊ��" << endl;
	//�����ͷ��
	cout << "    ";
	for (int i = 0; i < nVertex; i++)
	{
		cout << setw(4) << i+1;
	}
	cout << endl;
	//�����ͷ�� �� ��������
	for (int i = 0; i < nVertex; i++)
	{
		cout << setw(4) << i+1;
		for (int j = 0; j < nVertex; j++)
		{
			adjMatrix[i][j] != _int_INFINITY ? cout << setw(4) << adjMatrix[i][j] : cout << setw(4) << "��";
		}
		cout << endl;
	}
}

inline void GraphMatrix::keywordSearch(string keyword)
{
	cout<<endl << "��ʼΪ��������ؽ�����" << endl;
	int num=0;
	for (int i = 0; i < nVertex; i++)
	{
		if (data[i].intro.find(keyword)!=string::npos)
		{
			cout<<"  " << data[i].intro << "; ���꣨" << data[i].coor[0] << "��" << data[i].coor[1] << ")" << endl;
			num++;
		}
	}
	cout << "������ϣ�";
	if (0==num)
	{
		cout << "sorry~δ�ҵ���ؽ�����" << endl << endl;
	}
	else
	{
		cout << "���ҵ� " << num << " ����ؽ�����" << endl << endl;
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

inline void GraphMatrix::ShortPathPrint(int v,int w)//���v,�յ�w
{
	cout << "  ȥ����" << data[w].intro << "�������·������Ϊ" << ShortPathLengthMatrix[v][w]
		<< "��·��Ϊ��" << endl << "	" << data[v].intro;
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
		cout << "δ�ҵ�����Ҫ���·�����볢�Ե���;������������n" << endl;
		return 0;
	}
	float fangxiang;
	cout << endl;
	cout << "���ҵ�����Ҫ��·������Ϊ��" << num_path << "   ���·������Ϊ" << min_pathlength << endl
		<< "·����ϢΪ��" << endl;
	for (int i = 0; i < num_path; i++)
	{
		cout << "	";
		for (int j = 0; j < num_vertex-1; j++)
		{
			//cout << "��" << data[path[i][j + 1]].coor[1] << data[path[i][j]].coor[1]<<data[path[i][j + 1]].coor[0] << data[path[i][j]].coor[0] << "��";//for test
			fangxiang = atan2(data[path[i][j + 1]].coor[1] - data[path[i][j]].coor[1] , data[path[i][j + 1]].coor[0] - data[path[i][j]].coor[0]);
			cout <<"��"<< path[i][j] + 1 << "��"
				<< data[path[i][j]].intro << "����"
				<< int(fangxiang*180.0/3.14) << "�㷽���߾���"
				<< adjMatrix[path[i][j]][path[i][j + 1]] << "���ߵ�-->";
		}
		cout << "��" << path[i][num_vertex-1] + 1 << "��" << data[path[i][num_vertex-1]].intro << "��" << endl;
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
				//cout << "  " << data[i].intro << "; ���꣨" << data[i].coor[0] << "��" << data[i].coor[1] << ")" << endl;
			}
		}
		if (0 == num)
		{
			cout << "δ�ҵ���ؽ����㣬������������ؼ���,�磺��G������У�š��ȣ�";
			cin >> now;
		}
		if (num > 1)
		{
			for (int i = 0; i < num; i++)
			{
				cout << "  " << i + 1 << ":" << data[nowtemp[i]].intro << endl;
			}
			cout << "���ҵ� " << num << " ����ؽ����㣬��ȷ������ѡ�Ľ����㣬�����������֮һ��";
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
	cout << "���ݹؼ���ȷ����λ��Ϊ��" << data[current].intro << endl<<endl;
}

inline void GraphMatrix::searchShortPath(string now)
{
	//���ݹؼ��֣�ȷ���û���ǰλ��
	int current=-1;
	Keyword2Vertex(current,now);
	//��һ�β���ʱ��Floyd�㷨������С·������·�����ȳ��Ⱦ���
	if (!ShortPathSearched)
	{
		Floyd();
		ShortPathSearched = true;
	}
	//�õ���current���������·����Ŀ�ĵ�����
	vector<float> PathWeightTemp(18);
	int pathsorttemp[18];
	for (int i = 0; i < nVertex; i++)
	{
		PathWeightTemp[i] = ShortPathLengthMatrix[current][i];
		pathsorttemp[i] = i;
	}
	//�õ����������·����Ŀ�ĵ�����
	Quicksort<float>(PathWeightTemp,pathsorttemp);
	//��˳���ӡ���·����·����Ϣ
	cout << "�ӵ�ǰλ��("<<data[current].intro<<")��ѯ���Ŀɵ���Ŀ�ĵ���ϢΪ�������С�������򣩣�" << endl<<endl;
	for (int i = 1; i < nVertex; i++)//i��1��ʼ���ų��Լ����Լ���·��
	{
		ShortPathPrint(current, pathsorttemp[i]);
	}
	cout << endl;
}

inline int GraphMatrix::nplaceShortPath(int v,int w,int n)//���Ϊv+1�Ľ�����Ϊ��㣬w+1����Ϊ�յ㣬v��wΪ�������е����
{
	int numpath = 0, stackptr = 0, findvertexflag;//·��������ջ��ָ��
	int stack[18] , instackflag[18] , edgepassflag[18][18];//����ڽӶ����ջ���������Ƿ���ջ��ı�־;�ڽӶ����Ƿ��ѷ��ʵı�־
	int Paths[18][18];//������ҵ�������·����δ֪
	float pathlength,minpathlength=_int_INFINITY;
	stack[stackptr] = v;//�����ջ
	instackflag[v] = 1;//��ջ���־��1
	stackptr++;//ջ��ָ������һλ
	while (stackptr!=0)//ջ��Ϊ�վ�˵������·��û������
	{
		////for test
		//cout << "ջ���Ķ���Ϊ��" << stack[stackptr - 1] + 1 << endl;//for test
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

		int vertexTemp = stack[stackptr - 1];//ȡ��ջ��Ԫ��
		if (vertexTemp==w)//���ջ��Ԫ��ΪĿ�������,˵���ҵ���һ������Ŀ���·��
		{
			if (stackptr == n)//���·���ж�����Ϊ������n
			{
				//�����·���ĳ���
				pathlength = 0;
				for (int i = 0; i < stackptr - 1; i++)
				{
					pathlength += adjMatrix[stack[i]][stack[i + 1]];
					//cout << "·��Ϊ��" << stack[i]+1 << "->" << stack[i + 1]+1<<"  ";//for test
					//cout<<"�������" << pathlength ;//for test
				}
				//cout << endl;//for test
				//·������С���ϴδ������·����
				if (pathlength<minpathlength)
				{
					for (int i = 0; i < stackptr; i++)
					{
						Paths[0][i] = stack[i];//��ջ�д�Ķ��㣨��Ϊ��ǰ�ҵ���·����������·����������һ����
					}
					minpathlength = pathlength;
					numpath = 1;//·������Ϊ1
				}
				else if (pathlength == minpathlength)//����·�����ȵ�����һ�δ������·����
				{
					for (int i = 0; i < stackptr; i++)
					{
						Paths[numpath][i] = stack[i];//��ջ�д�Ķ��㣨��Ϊ��ǰ�ҵ���·����������·�����������
					}
					//·������+1
					numpath++;
				}
			}
			//���ջ��Ԫ��w
			stackptr--;
			stack[stackptr] = -1;
			//Ŀ�궥����ջ���־��0
			//cout << "yi  " << w << endl;//for test
			instackflag[w] = 0;
			//cout << "·������Ϊ��" << numpath <<"   ջ�����ݸ���"<<stackptr<< endl;//for test
		}
		//�ҵ�ǰջ���Ķ����δ��ջ��δ���ʵ��ڽӶ���
		findvertexflag = 0;//�ҵ�����Ҫ����ڽӶ��㣬��־
		for (int i = 0; i < nVertex; i++)
		{
			if (adjMatrix[stack[stackptr - 1]][i]!=0
				&& adjMatrix[stack[stackptr - 1]][i] != _int_INFINITY//�ҵ��ڽӶ���
				&& instackflag[i]!=1//�ж��ڽӶ����Ƿ���ջ��
				&& edgepassflag[stack[stackptr - 1]][i]!=1)//�ж��ڽӶ����Ƿ��ѷ���
			{
				//��ջ���־��1
				//cout << i << endl;//for test
				instackflag[i] = 1;
				//�ѷ��ʱ�־��1
				edgepassflag[stack[stackptr - 1]][i] = 1;
				//����Ҫ���ڽӶ������ջ
				stack[stackptr] = i;
				stackptr++;
				//�ҵ�����Ҫ�󶥵��־��1
				findvertexflag = 1;
				//cout << "�ҵ����¶���" << i + 1 << endl;//for test
				break;
			}
		}
		if (findvertexflag==0)//���û�ҵ�����Ҫ����ڽӶ��㣬˵���Ӹö�����������к�������·�����ѱ�����
		{
			//cout << "�߳�һ������ĵ�" << stack[stackptr - 1] + 1;//for test
			//ջ��������ڽӶ��㱻���ʹ��ı�־��0
			for (int i = 0; i < nVertex; i++)
			{
				edgepassflag[stack[stackptr - 1]][i] = 0;
			}
			//ջ���Ķ�����ջ���־��0
			//cout <<"er  "<< stack[stackptr - 1] << endl;//for test
			instackflag[stack[stackptr - 1]] = 0;
			//ջ���Ķ����ջ
			stackptr--;
			stack[stackptr] = -1;
			//cout << "�߳��ɹ�" << endl;//for test
		}
		//cout << "ջ���Ķ���Ϊ��" << stack[stackptr - 1]+1<<endl;//for test
		////for test
		//if (numpath==319)
		//{
		//	break;
		//}
	}
	return nplaceShortPathPrint(Paths, numpath, minpathlength, n);
}


