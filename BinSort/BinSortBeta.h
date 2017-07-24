#pragma once
#include <iostream>
#include "ChainList.h"
using namespace std;

////类的定义应该放在cpp文件中
////class Node
////{
////	friend ostream& operator<<(ostream&, const Node &);
////public:
////	int operator !=(Node x) const
////	{
////		return (exam1 != x.exam1 || exam2 != x.exam2
////			|| exam3 != x.exam3 || name[0] != x.name[0]);
////	}
////private:
////	int exam1,exam2,exam3;
////	char *name;
////};
////ostream& operator<<(ostream& out, const Node& x)
////{
////	out << x.exam1 << ' ' << x.exam2 << ' ' << x.exam3 << x.name[0] << ' ';
////	return out;
////}

//可以按不同域进行排序的BinSort版本。
//该版本多增加一个参数value，可以指定Node的不同域。
//通过定义不同版本的value的实参来实现。

template<class T>
void Chain<T>::BinSort(int range,int(*value)(T& x))
{
	// 按分数排序
	int b; // 箱子索引号
	ChainNode<T> **bottom, **top;
	//箱子初始化
	//数组中装着的元素是指向Chain<Node>类型的指针
	bottom = new ChainNode<T>*[range + 1];//这个数组中装着的元素是
										  //指向每个箱子尾部ChainNode
										  //节点的指针
	top = new ChainNode<T>*[range + 1];//这个数组中装着的元素是
									   //指向每个箱子首部ChainNode
									   //节点的指针（底为首，顶为尾）
	for (b = 0; b <= range; b++)
		bottom[b] = 0;
	// 把节点分配到各箱子中
	for (; first; first = first->link)//排序后Chain大链不输出的问题所在
									  //因为BinSort之后，大链的first指针
									  //指向NULL，而Chain类中的<<操作符
									  //重载需要用到指向Chain大链链头的
									  //first指针，这就产生矛盾了。
	{
		// 添加到箱子中
		//此处做此修改
		b = value(first->data);	//first指向一个ChainNode节点，ChainNode节点
								//的数据域应该是Node类型，b是一个int型。
								//value是一个函数指针，这里具体由F1、F2、F3
								//替换。在主函数中将这些函数传入BinSort时并
								//没有给它们传递参数。这些函数的实参是
								//这个for循环中传递的。
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
			{
				y = bottom[b];
				first = bottom[b];  //第一个非空箱子在for循环中只会遇到一次
			}

			y = top[b];  //把y指向当前大链表尾节点，
						 //为链接下个箱子的链作准备
		}
	if (y) y->link = 0;
	//first = bottom[0];  //增加了这句代码，将first指针指向排好序的Chain大链链头
						//然而对于三次成绩相加的情况，first就不一定要指向bottom[0]了
						//所以，应该改为first指向第一个非空箱子的底部节点。
	delete[]bottom;
	delete[]top;
}