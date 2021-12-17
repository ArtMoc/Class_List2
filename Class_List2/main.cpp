#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "E_Constructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "E_Destructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail;//��������� ��� ��������� ����� �� ����� �������� ������
	//��� ��������� ����� ����������� ������� ������ List
	size_t size;//������ ������
public:
	List()
	{
		Head = Tail = nullptr;//���� ������ ����. ��� ������ � ����� ��������� �� 0
		size = 0;
		cout << "L_Constructor:\t" << this << endl;
	}
	~List()
	{
		cout << "L_Destructor:\t" << this << endl;
	}

	//               ADDING ELEMENTS:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			//����� � ������ ���������� ������ �������, �� ������������ 
			//�������� � ������� � �������
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		Head = Head->pPrev = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index >= size)
		{
			cout << "Error: ����� �� �������� ������!" << endl;
			return;
		}
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}

	//                 REMOVING ELEMENTS:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	//                 METHODS:
	void print()const
	{
		cout << "Head:\t" << Head << endl;
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Tail:\t" << Tail << endl;
		cout << "���������� ��������� ������: " << size << endl;
	}
	void print_reverse()const
	{
		cout << "Tail:\t" << Tail << endl;
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
			cout << "Head:\t" << Head << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "������� ������ ������: ";cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.print_reverse();
	cout << "\n---------------------------------------------\n";
	/*list.pop_front();
	list.pop_back();*/
	int index;
	int value;
	cout << "������� ������ ������������ ��������: ";cin >> index;
	cout << "������� �������� ������������ ��������: ";cin >> value;
	list.insert(value, index);
	list.print();
	list.print_reverse();
}