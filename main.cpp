/*
�����ܣ�1.ʹ���ڽӱ��ʾͼ��ʵ�ֵϽ�˹�����㷨��
		  2.ʹ���ڽӾ����ʾͼ��ʵ�ֿ�³˹������С�������㷨
��    �ߣ������-19S053037
����ʱ�䣺2020.7.1
��    ע����������ͱ�ʱ���Էֱ������������������Կ�ݽ���(Ҳ���������뽨��)
			//1 2 3 4 5 6 7 ?
			//1 2 2 1 3 4 1 4 1 2 4 3 2 5 10 3 6 5 4 3 2 4 6 8 4 7 4 5 4 2 5 7 6 7 6 1 ��
*/

#include"map.h"
#include<windows.h>

void title();
void GUI(int& option,int list[5]);
void function1(GraphMatrix map);
void function2(GraphMatrix map);
void function3(GraphMatrix map);
void function4(GraphMatrix map);

int main()
{
	title();
	GraphMatrix map;

	bool Exit=false;
	int option = 0, optionList[5] = {1,2,3,4,0};
	while (!Exit)
	{
		GUI(option,optionList);
		switch (option)
		{
		case 1:
			function1(map);
			break;
		case 2:
			function2(map);
			break;
		case 3:
			function3(map);
			break;
		case 4:
			function4(map);
			break;
		case 0:
			Exit = true;
			break;
		default:
			break;
		}
	}
	cout << "ϵͳ�����رգ���л����ʹ�á�";
	for (int i = 0; i < 3; i++)
	{
		cout << ". ";
		Sleep(500);
	}
	cout << endl;

	return 1;
}

void title()
{
	cout << "        �������ͼ����Ϊ������~~" << endl
		<< "    ==============================" << endl
		<< "   ||   ���ߣ������-19S053037   ||" << endl
		<< "   ||     ��Ȩ���У���Ȩ�޾�     ||" << endl
		<< "    ==============================" << endl << endl << endl;
}

void GUI(int& option,int list[5])
{
	cout << "/* * * * * * * * ���˵� * * * * * * * */" << endl;
	cout << "��ѡ��������Ĺ���(�����ţ��磺1��" << endl << endl
		<< "	==>1.����У԰�����б�鿴" << endl << endl
		<< "	==>2.�����������Ϣ��ѯ  " << endl << endl
		<< "	==>3.n���������·����ѯ " << endl << endl
		<< "	==>4.��������·��ѯ�����·��˳�����У�  " << endl << endl
		<< "	==>0.�˳�  " << endl << endl
		<< "/* * * * * * * * ���˵� * * * * * * * */" << endl
		<< "����������ѡ��" ;
	cin >> option;
	while (cin.fail()==true||find(list,list+5,option)==list+5)
	{
		deletecinfail();
		cin >> option;
	}
	cout << endl;
}

void function1(GraphMatrix map)
{
	cout << "/* * * * * * * * ����һ�������б�鿴 * * * * * * * */" << endl;
	cout << "�������б����£�" << endl<<endl;
	map.printVertex();
	cout <<endl<< "�������б������ɣ���ӭ��ʹ����������~" << endl ;
	cout << "/* * * * * * * * ����һ�������б�鿴 * * * * * * * */" << endl << endl;
}

void function2(GraphMatrix map)
{
	cout << "/* * * * * * * * ���ܶ�����������Ϣ��ѯ * * * * * * * */" << endl;
	string keywords;
	int continusearch = 1;
	while (continusearch)
	{
		cout << "��������Ҫ��ѯ�ص�Ĺؼ���(�硰ʳ�á���)���������˵������롰������";
		cin >> keywords;
		//������ĵڶ���ѡ������ķ�ʽ
		if (keywords=="��"||keywords=="?")
		{
			break;
		}
		map.keywordSearch(keywords);
		//��һ��ѡ������ķ�ʽ
		/*cout << endl << "��������ؼ��ֽ��н�������Ϣ��ѯ������1,�˳���ѯ������0��";
		cin >> continusearch;
		while (cin.fail()==true||(continusearch!=1&&continusearch != 0))
		{
			deletecinfail();
			cin >> continusearch;
		}*/
	}
	cout << "��������Ϣ��ѯ�����˳�����ӭ��ʹ����������~" << endl ;
	cout << "/* * * * * * * * ���ܶ�����������Ϣ��ѯ * * * * * * * */" << endl << endl;
}

void function3(GraphMatrix map)
{
	cout << "/* * * * * * * ��������;��n���������·����ѯ * * * * * * */" << endl;
	//���ݹؼ���ȷ�����
	string now;
	int continusearch = 0;
	int lastvw[2] = { -1,-1 };
	while (true)
	{
		int v = -1, w = -1, n;
		if (!continusearch)
		{
			cout << "���������ؼ��֣���ȷ���������(�硰G����)���������˵������롰������";
			cin >> now;
			//������ĵڶ���ѡ������ķ�ʽ
			if (now == "��" || now == "?")
			{
				break;
			}
			map.Keyword2Vertex(v, now);
			//cout << now << v << endl;//for test
			cout << "�������յ�ؼ��֣���ȷ�������յ�(�硰G����)���������˵������롰������";
			cin >> now;
			//������ĵڶ���ѡ������ķ�ʽ
			if (now == "��" || now == "?")
			{
				break;
			}
			map.Keyword2Vertex(w, now);
			//cout << now << w << endl;//for test
		}
		else
		{
			v = lastvw[0];
			w = lastvw[1];
		}
		//cout << v<<w;//for test
		cout << "��������Ҫ�����Ľ�����������2~18֮�䣩��";
		cin >> n;
		while (cin.fail() == true || n < 2 || n > 18)
		{
			deletecinfail();
			cin >> n;
		}
		if (!map.nplaceShortPath(v, w, n))
		{
			cout << endl << "����ʹ���ϴε����յ��ѯ��1�ǣ�0��";
			cin >> continusearch;
			while (cin.fail() == true || (continusearch != 1 && continusearch != 0))
			{
				deletecinfail();
				cin >> continusearch;
			}
			lastvw[0] = v;
			lastvw[1] = w;
		}
		else
		{
			continusearch = 0;
		}
		cout << endl;
	}
	cout << ";��n���������·����ѯ�����˳�����ӭ��ʹ����������~" << endl ;
	cout << "/* * * * * * * ��������;��n���������·����ѯ * * * * * * */" << endl << endl;
}

void function4(GraphMatrix map)
{
	cout << "/* * * * * * * * * �����ģ���������·��ѯ * * * * * * * * */" << endl;
	string keywords;
	int continusearch = 1;
	while (continusearch)
	{
		cout << "�����뽨����Ĺؼ���(�硰ʳ�á���)���������˵������롰������";
		cin >> keywords;
		//������ĵڶ���ѡ������ķ�ʽ
		if (keywords == "��" || keywords == "?")
		{
			break;
		}
		map.searchShortPath(keywords);
		//��һ��ѡ������ķ�ʽ
		/*cout << endl << "�������뵱ǰλ�ùؼ��ֽ��в�ѯ������1,�˳���ѯ������0��";
		cin >> continusearch;
		while (cin.fail() == true || (continusearch != 1 && continusearch != 0))
		{
			deletecinfail();
			cin >> continusearch;
		}*/
	}
	cout << "��������·��ѯ�����˳�����ӭ��ʹ����������~" << endl ;
	cout << "/* * * * * * * * * �����ģ���������·��ѯ * * * * * * * * */" << endl << endl;
	
}


