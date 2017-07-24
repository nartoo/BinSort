#pragma once
#include <iostream>
#include "ChainList.h"

using namespace std;

////一种用于箱子排序的节点类
//class Node
//{
//	friend ostream& operator<<(ostream&, const Node &);
//public:
//	int operator !=(Node x) const
//	{
//		return (score != x.score);
//	}
//private:
//	int score;
//	char *name;
//};
//ostream& operator<<(ostream& out, const Node& x)
//{
//	out << x.score << ' '; return out;
//}
//
////另一种处理操作符重载的方法
//class Node
//{
//public:
//	// 重载类型转换操作符
//	operator int() const { return score; }
//private:
//	int score;
//	char *name;
//};

//又一种处理操作符重载的方法，上述两种的联合使用
//仅当操作符不是!=和<<时才适用int类型转换
//这里的Node与ChainList中的ChainNode不一样，
//Node中只有数据域，而ChainNode中还包括指针域。
//那如何理解这两者之间的关系？或者，Node就放在ChainNode的数据域？
class Node
{
	friend ostream& operator<<(ostream&, const Node &);
public:
	int operator !=(Node x) const
	{
		return (score != x.score
			|| name[0] != x.name[0]);
	}
	operator int() const { return score; }
private:
	int score;
	char *name;
};
ostream& operator<<(ostream& out, const Node& x)
{
	out << x.score << ' ' << x.name[0] << ' ';
	return out;
}

////箱子排序函数（说明版本），该函数假定BinSort是Node的一个友元
//template <class T> class Chain
//void BinSort(Chain<Node>& X, int range)
//{
//	// 按分数排序
//	int len = X, Length();
//	Node x;
//	Chain<Node> *bin;  //声明一个指向Chain<Node>类型的指针
//	bin = new Chain<Node>[range + 1];//分配一个数组，该数组的元素为
//									 //Chain<Node>类型，并令指针bin
//									 //指向该数组的首地址
//	//分配到每个箱子中
//	for (int i = 1; i <= len; i++)
//	{
//		X.Delete(1, x);
//		bin[x.score].Insert(0, x);  //每次都执行Insert(0, x)，
//									//那么每次都是在箱子的首部插入。
//	}
//	//从箱子中收集各元素，从最后一个箱子开始
//	for (int j = range; j >= 0; j--)
//		while (!bin[j].IsEmpty()) 
//		{
//			bin[j].Delete(1, x);
//			X.Insert(0, x);  //在新链的首部插入从箱子中删除的节点
//		}
//	delete[] bin;
//}

//需要在ChainList中添加BinSort函数的声明
template<class T>
void Chain<T>::BinSort(int range)
{
	// 按分数排序
	int b; // 箱子索引号
	ChainNode<T> **bottom, **top;
	//箱子初始化
	//数组中装着的元素是指向Chain<Node>类型的指针
	bottom = new ChainNode<T>* [range + 1];//这个数组中装着的元素是
										   //指向每个箱子尾部ChainNode
										   //节点的指针
	top = new ChainNode<T>* [range + 1];//这个数组中装着的元素是
										//指向每个箱子首部ChainNode
										//节点的指针（底为首，顶为尾）
	for (b = 0; b <= range; b++)
		bottom[b] = 0;
	// 把节点分配到各箱子中
	for (; first; first = first->link)
	{
		// 添加到箱子中
		b = first->data;//first指向一个ChainNode节点，ChainNode节点
						//的数据域应该是Node类型，b是一个int型，
						//因此这里应该假定已经定义了从Node到int
						//类型的转换，才能返回Node中的score域。
		if (bottom[b]) 
		{
			//箱子非空
			top[b]->link = first;//把first所指节点添加到顶部,
			top[b] = first;      //并把顶部节点指针top[b]指向
								 //这个新添加的节点
		}
		else // 箱子为空
			bottom[b] = top[b] = first;
	}
	//收集各箱子中的元素，产生一个排序链表
	//只需将各个箱子中的链链接起来即可
	ChainNode<T> *y = 0;
	for (b = 0; b <= range; b++)
		if (bottom[b])
		{
			//箱子非空
			if (y) // 不是第一个非空的箱子
				y->link = bottom[b];
			else   // 第一个非空的箱子
				y = bottom[b];
			y = top[b];  //把y指向当前链表尾节点，
						 //为链接下个箱子的链作准备
		}
	if (y) y->link = 0;
	delete []bottom;
	delete []top;
}