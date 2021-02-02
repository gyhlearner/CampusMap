#include<iostream>
#include<vector>

using namespace std;


template<typename T>
void Quicksort(vector<T>& a, int* b);
template<typename T>
void Quicksort(vector<T>& a, int* b, int left, int right);
template<typename T>
int findmidnum(vector<T> array, int a, int b, int c);
template<typename T>
void swapdata(vector<T>& array, int a, int b);
void swapdata(int* array, int a, int b);



template<typename T>
void Quicksort(vector<T>& a,int* b)
{
	Quicksort(a,b, 0, a.size() - 1);
}

template<typename T>
void Quicksort(vector<T>& a,int* b, int left, int right)
{
	//cout << left << right << endl;//for test

	if (left >= right)
	{
		return;
	}
	int mid = (left + right) / 2;
	//找a[left]、a[mid]、a[right]的中位数做枢纽
	T pivot;
	int pivotnum;
	//pivot = findmid(a[left], a[mid], a[right]);
	pivotnum = findmidnum(a, left, mid, right);
	pivot = a[pivotnum];
	//将中位数放到left位置
	swapdata(a, left, pivotnum);
	swapdata(b, left, pivotnum);
	//开始划分a[left:right]
	int i = left, j = right;
	int i_flag = 0, j_flag = 1;
	while (i != j)
	{
		while (a[i] <= pivot && i_flag && i < j)
		{
			i++;
		}
		while (a[j] >= pivot && j_flag && i < j)
		{
			j--;
		}
		if (i < j)
		{
			swapdata(a, i, j);
			swapdata(b, i, j);
			i_flag = !i_flag;
			j_flag = !j_flag;
		}
	}
	//printarray(a);//for test
	Quicksort(a,b, left, i - 1);
	Quicksort(a,b, i + 1, right);
}

template<typename T>
int findmidnum(vector<T> array, int a, int b, int c)
{
	if (array[a] == array[b])
	{
		return a;
	}
	if ((array[a] - array[b]) * (array[a] - array[c]) <= 0)
	{
		return a;
	}

	if ((array[b] - array[a]) * (array[b] - array[c]) <= 0)
	{
		return b;

	}

	if ((array[c] - array[a]) * (array[c] - array[b]) <= 0)
	{
		return c;
	}
	return a;
}

template<typename T>
void swapdata(vector<T>& array, int a, int b)
{
	if (a == b)
	{
		return;
	}
	T temp;
	temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}

void swapdata(int* array, int a, int b)
{
	if (a == b)
	{
		return;
	}
	int temp;
	temp = array[a];
	array[a] = array[b];
	array[b] = temp;
}