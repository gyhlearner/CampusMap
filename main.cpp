/*
程序功能：1.使用邻接表表示图，实现迪杰斯特拉算法；
		  2.使用邻接矩阵表示图，实现克鲁斯卡尔最小生成树算法
作    者：郭雨豪-19S053037
创建时间：2020.7.1
备    注：建立顶点和边时可以分别输入以下两行内容以快捷建立(也可自行输入建立)
			//1 2 3 4 5 6 7 ?
			//1 2 2 1 3 4 1 4 1 2 4 3 2 5 10 3 6 5 4 3 2 4 6 8 4 7 4 5 4 2 5 7 6 7 6 1 ？
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
	cout << "系统即将关闭，感谢您的使用。";
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
	cout << "        大聪明地图持续为您导航~~" << endl
		<< "    ==============================" << endl
		<< "   ||   作者：郭雨豪-19S053037   ||" << endl
		<< "   ||     版权所有，侵权无究     ||" << endl
		<< "    ==============================" << endl << endl << endl;
}

void GUI(int& option,int list[5])
{
	cout << "/* * * * * * * * 主菜单 * * * * * * * */" << endl;
	cout << "请选择您所需的功能(输入编号，如：1）" << endl << endl
		<< "	==>1.哈深校园建筑列表查看" << endl << endl
		<< "	==>2.建筑点相关信息查询  " << endl << endl
		<< "	==>3.n建筑点最短路径查询 " << endl << endl
		<< "	==>4.建筑点问路查询（最短路径顺序排列）  " << endl << endl
		<< "	==>0.退出  " << endl << endl
		<< "/* * * * * * * * 主菜单 * * * * * * * */" << endl
		<< "请输入您的选择：" ;
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
	cout << "/* * * * * * * * 功能一：建筑列表查看 * * * * * * * */" << endl;
	cout << "建筑点列表如下：" << endl<<endl;
	map.printVertex();
	cout <<endl<< "建筑点列表输出完成，欢迎您使用其他功能~" << endl ;
	cout << "/* * * * * * * * 功能一：建筑列表查看 * * * * * * * */" << endl << endl;
}

void function2(GraphMatrix map)
{
	cout << "/* * * * * * * * 功能二：建筑点信息查询 * * * * * * * */" << endl;
	string keywords;
	int continusearch = 1;
	while (continusearch)
	{
		cout << "请输入您要查询地点的关键字(如“食堂”等)，返回主菜单请输入“？”：";
		cin >> keywords;
		//改良后的第二种选择继续的方式
		if (keywords=="？"||keywords=="?")
		{
			break;
		}
		map.keywordSearch(keywords);
		//第一种选择继续的方式
		/*cout << endl << "继续输入关键字进行建筑点信息查询请输入1,退出查询请输入0：";
		cin >> continusearch;
		while (cin.fail()==true||(continusearch!=1&&continusearch != 0))
		{
			deletecinfail();
			cin >> continusearch;
		}*/
	}
	cout << "建筑点信息查询即将退出，欢迎您使用其他功能~" << endl ;
	cout << "/* * * * * * * * 功能二：建筑点信息查询 * * * * * * * */" << endl << endl;
}

void function3(GraphMatrix map)
{
	cout << "/* * * * * * * 功能三：途径n建筑点最短路径查询 * * * * * * */" << endl;
	//根据关键字确定起点
	string now;
	int continusearch = 0;
	int lastvw[2] = { -1,-1 };
	while (true)
	{
		int v = -1, w = -1, n;
		if (!continusearch)
		{
			cout << "请输入起点关键字，以确定搜索起点(如“G”等)，返回主菜单请输入“？”：";
			cin >> now;
			//改良后的第二种选择继续的方式
			if (now == "？" || now == "?")
			{
				break;
			}
			map.Keyword2Vertex(v, now);
			//cout << now << v << endl;//for test
			cout << "请输入终点关键字，以确定搜索终点(如“G”等)，返回主菜单请输入“？”：";
			cin >> now;
			//改良后的第二种选择继续的方式
			if (now == "？" || now == "?")
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
		cout << "请输入想要经过的建筑点数量（2~18之间）：";
		cin >> n;
		while (cin.fail() == true || n < 2 || n > 18)
		{
			deletecinfail();
			cin >> n;
		}
		if (!map.nplaceShortPath(v, w, n))
		{
			cout << endl << "继续使用上次的起终点查询吗？1是，0否：";
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
	cout << "途径n建筑点最短路径查询即将退出，欢迎您使用其他功能~" << endl ;
	cout << "/* * * * * * * 功能三：途径n建筑点最短路径查询 * * * * * * */" << endl << endl;
}

void function4(GraphMatrix map)
{
	cout << "/* * * * * * * * * 功能四：建筑点问路查询 * * * * * * * * */" << endl;
	string keywords;
	int continusearch = 1;
	while (continusearch)
	{
		cout << "请输入建筑点的关键字(如“食堂”等)，返回主菜单请输入“？”：";
		cin >> keywords;
		//改良后的第二种选择继续的方式
		if (keywords == "？" || keywords == "?")
		{
			break;
		}
		map.searchShortPath(keywords);
		//第一种选择继续的方式
		/*cout << endl << "继续输入当前位置关键字进行查询请输入1,退出查询请输入0：";
		cin >> continusearch;
		while (cin.fail() == true || (continusearch != 1 && continusearch != 0))
		{
			deletecinfail();
			cin >> continusearch;
		}*/
	}
	cout << "建筑点问路查询即将退出，欢迎您使用其他功能~" << endl ;
	cout << "/* * * * * * * * * 功能四：建筑点问路查询 * * * * * * * * */" << endl << endl;
	
}


