#pragma once
#include <iostream>
#include "ChainList.h"

using namespace std;

////һ��������������Ľڵ���
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
////��һ�ִ�����������صķ���
//class Node
//{
//public:
//	// ��������ת��������
//	operator int() const { return score; }
//private:
//	int score;
//	char *name;
//};

//��һ�ִ�����������صķ������������ֵ�����ʹ��
//��������������!=��<<ʱ������int����ת��
//�����Node��ChainList�е�ChainNode��һ����
//Node��ֻ�������򣬶�ChainNode�л�����ָ����
//��������������֮��Ĺ�ϵ�����ߣ�Node�ͷ���ChainNode��������
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

////������������˵���汾�����ú����ٶ�BinSort��Node��һ����Ԫ
//template <class T> class Chain
//void BinSort(Chain<Node>& X, int range)
//{
//	// ����������
//	int len = X, Length();
//	Node x;
//	Chain<Node> *bin;  //����һ��ָ��Chain<Node>���͵�ָ��
//	bin = new Chain<Node>[range + 1];//����һ�����飬�������Ԫ��Ϊ
//									 //Chain<Node>���ͣ�����ָ��bin
//									 //ָ���������׵�ַ
//	//���䵽ÿ��������
//	for (int i = 1; i <= len; i++)
//	{
//		X.Delete(1, x);
//		bin[x.score].Insert(0, x);  //ÿ�ζ�ִ��Insert(0, x)��
//									//��ôÿ�ζ��������ӵ��ײ����롣
//	}
//	//���������ռ���Ԫ�أ������һ�����ӿ�ʼ
//	for (int j = range; j >= 0; j--)
//		while (!bin[j].IsEmpty()) 
//		{
//			bin[j].Delete(1, x);
//			X.Insert(0, x);  //���������ײ������������ɾ���Ľڵ�
//		}
//	delete[] bin;
//}

//��Ҫ��ChainList�����BinSort����������
template<class T>
void Chain<T>::BinSort(int range)
{
	// ����������
	int b; // ����������
	ChainNode<T> **bottom, **top;
	//���ӳ�ʼ��
	//������װ�ŵ�Ԫ����ָ��Chain<Node>���͵�ָ��
	bottom = new ChainNode<T>* [range + 1];//���������װ�ŵ�Ԫ����
										   //ָ��ÿ������β��ChainNode
										   //�ڵ��ָ��
	top = new ChainNode<T>* [range + 1];//���������װ�ŵ�Ԫ����
										//ָ��ÿ�������ײ�ChainNode
										//�ڵ��ָ�루��Ϊ�ף���Ϊβ��
	for (b = 0; b <= range; b++)
		bottom[b] = 0;
	// �ѽڵ���䵽��������
	for (; first; first = first->link)
	{
		// ��ӵ�������
		b = first->data;//firstָ��һ��ChainNode�ڵ㣬ChainNode�ڵ�
						//��������Ӧ����Node���ͣ�b��һ��int�ͣ�
						//�������Ӧ�üٶ��Ѿ������˴�Node��int
						//���͵�ת�������ܷ���Node�е�score��
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
				y = bottom[b];
			y = top[b];  //��yָ��ǰ����β�ڵ㣬
						 //Ϊ�����¸����ӵ�����׼��
		}
	if (y) y->link = 0;
	delete []bottom;
	delete []top;
}