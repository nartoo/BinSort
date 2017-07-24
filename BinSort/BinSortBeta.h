#pragma once
#include <iostream>
#include "ChainList.h"
using namespace std;

////��Ķ���Ӧ�÷���cpp�ļ���
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

//���԰���ͬ����������BinSort�汾��
//�ð汾������һ������value������ָ��Node�Ĳ�ͬ��
//ͨ�����岻ͬ�汾��value��ʵ����ʵ�֡�

template<class T>
void Chain<T>::BinSort(int range,int(*value)(T& x))
{
	// ����������
	int b; // ����������
	ChainNode<T> **bottom, **top;
	//���ӳ�ʼ��
	//������װ�ŵ�Ԫ����ָ��Chain<Node>���͵�ָ��
	bottom = new ChainNode<T>*[range + 1];//���������װ�ŵ�Ԫ����
										  //ָ��ÿ������β��ChainNode
										  //�ڵ��ָ��
	top = new ChainNode<T>*[range + 1];//���������װ�ŵ�Ԫ����
									   //ָ��ÿ�������ײ�ChainNode
									   //�ڵ��ָ�루��Ϊ�ף���Ϊβ��
	for (b = 0; b <= range; b++)
		bottom[b] = 0;
	// �ѽڵ���䵽��������
	for (; first; first = first->link)//�����Chain�������������������
									  //��ΪBinSort֮�󣬴�����firstָ��
									  //ָ��NULL����Chain���е�<<������
									  //������Ҫ�õ�ָ��Chain������ͷ��
									  //firstָ�룬��Ͳ���ì���ˡ�
	{
		// ��ӵ�������
		//�˴������޸�
		b = value(first->data);	//firstָ��һ��ChainNode�ڵ㣬ChainNode�ڵ�
								//��������Ӧ����Node���ͣ�b��һ��int�͡�
								//value��һ������ָ�룬���������F1��F2��F3
								//�滻�����������н���Щ��������BinSortʱ��
								//û�и����Ǵ��ݲ�������Щ������ʵ����
								//���forѭ���д��ݵġ�
		if (bottom[b])
		{
			//���ӷǿ�
			top[b]->link = first;//��first��ָ�ڵ���ӵ�����,
			top[b] = first;      //���Ѷ����ڵ�ָ��top[b]ָ��
								 //�������ӵĽڵ�
		}
		else // ����Ϊ��
			bottom[b] = top[b] = first;
	}
	//�ռ��������е�Ԫ�أ�����һ����������
	//ֻ�轫���������е���������������
	ChainNode<T> *y = 0;
	for (b = 0; b <= range; b++)
		if (bottom[b])
		{
			//���ӷǿ�
			if (y) // ���ǵ�һ���ǿյ�����
				y->link = bottom[b];
			else   // ��һ���ǿյ�����
			{
				y = bottom[b];
				first = bottom[b];  //��һ���ǿ�������forѭ����ֻ������һ��
			}

			y = top[b];  //��yָ��ǰ������β�ڵ㣬
						 //Ϊ�����¸����ӵ�����׼��
		}
	if (y) y->link = 0;
	//first = bottom[0];  //�����������룬��firstָ��ָ���ź����Chain������ͷ
						//Ȼ���������γɼ���ӵ������first�Ͳ�һ��Ҫָ��bottom[0]��
						//���ԣ�Ӧ�ø�Ϊfirstָ���һ���ǿ����ӵĵײ��ڵ㡣
	delete[]bottom;
	delete[]top;
}