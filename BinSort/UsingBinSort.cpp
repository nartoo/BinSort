#include <iostream>
#include <string>
#include <iomanip>     //可以指定输出格式
#include "ChainList.h"
#include "BinSortBeta.h"
#include "Xcept.h"

using namespace std;

class Node
{
	friend ostream& operator<<(ostream&, const Node &); //满足Chain<T>对类型T的要求
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
	string name; //原作为char* name，这样的用法，编译通过，但是调试时会异常中断。
				 //在主函数给x.name赋值时中断
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
		p.exam3 = rand()%101;      //这里可以产生0到100的随机数
		p.name = 64 + i;  //原作是x.name = i;
		L.Insert(0, p);
	}
	cout << L << endl;//加上此句代码，输出原顺序，输出成功。
					  //说明原先无法输出数据的原因极有可能出在BinSort函数上。
	L.BinSort(10, F1);
	cout << "Sort on exam 1" << endl;
	cout << L << endl;
	L.BinSort(20, F2);
	cout << "Sort on exam 2" << endl;
	cout << L << endl;
	L.BinSort(130, F3);  //这里range并不是最大的那个随机数，即100了
						 //因为这里是要输出三次成绩相加，所以range值大于100，
						 //range应该设为三次成绩各个最大值相加，即130
	cout << "Sort on sum of exams" << endl;
	cout << L << endl;
}