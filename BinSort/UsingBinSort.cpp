#include <iostream>
#include <string>
#include <iomanip>     //����ָ�������ʽ
#include "ChainList.h"
#include "BinSortBeta.h"
#include "Xcept.h"

using namespace std;

class Node
{
	friend ostream& operator<<(ostream&, const Node &); //����Chain<T>������T��Ҫ��
	friend int F1(Node& x), F2(Node& x), F3(Node& x);
	friend void main(void);
public:
	int operator !=(Node x) const
	{
		return (exam1 != x.exam1 || exam2 != x.exam2
			|| exam3 != x.exam3 || name != x.name);
	}
private:
	int exam1;
	int exam2;
	int exam3;
	string name; //ԭ��Ϊchar* name���������÷�������ͨ�������ǵ���ʱ���쳣�жϡ�
				 //����������x.name��ֵʱ�ж�
};
ostream& operator<<(ostream& out, const Node& x)
{
	out << setw(3) << x.exam1 << " " << setw(3) << x.exam2 << " "
		<< setw(3) << x.exam3 << " " << x.name << endl;
	return out;
}

inline int F1(Node& x) { return x.exam1; }
inline int F2(Node& x) { return x.exam2; }
inline int F3(Node& x)
{
	return (x.exam1 + x.exam2 + x.exam3);
}
void main(void)
{
	Node p;
	Chain<Node> L;
	srand(1);
	for (int i = 1; i <= 20; i++)
	{
		p.exam1 = i / 2;           //range=10
		p.exam2 = 20 - i;          //range=20
		p.exam3 = rand()%101;      //������Բ���0��100�������
		p.name = 64 + i;  //ԭ����x.name = i;
		L.Insert(0, p);
	}
	cout << L << endl;//���ϴ˾���룬���ԭ˳������ɹ���
					  //˵��ԭ���޷�������ݵ�ԭ���п��ܳ���BinSort�����ϡ�
	L.BinSort(10, F1);
	cout << "Sort on exam 1" << endl;
	cout << L << endl;
	L.BinSort(20, F2);
	cout << "Sort on exam 2" << endl;
	cout << L << endl;
	L.BinSort(130, F3);  //����range�����������Ǹ����������100��
						 //��Ϊ������Ҫ������γɼ���ӣ�����rangeֵ����100��
						 //rangeӦ����Ϊ���γɼ��������ֵ��ӣ���130
	cout << "Sort on sum of exams" << endl;
	cout << L << endl;
}