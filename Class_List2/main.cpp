﻿#include <iostream>
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
	}*Head, * Tail;//Объявляем два указателя сразу же после описания класса
	//Эти указатели будут переменными членами класса List
	size_t size;//размер списка
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
			cout << "I_Constructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "I_Destructor:\t" << this << endl;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		bool operator==(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
		
	};
	class ReverseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp) :Temp(Temp)
		{
			cout << "R_It_Constructor:\t" << this << endl;
		}
		~ReverseIterator()
		{
			cout << "R_It_Destructor:\t" << this << endl;
		}

		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		bool operator==(const ReverseIterator& other)
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)
		{
			return this->Temp != other.Temp;
		}

		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;//Если список пуст. его голова и хвост указывают на 0
		size = 0;
		cout << "L_Constructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);*/
		
		*this = other;//из конструктора копирования вызываем оператор присваивания
		cout << "L_Copy_Constructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "L_Destructor:\t" << this << endl;
		cout << "\n---------------------------------\n";
	}

	//               OPERATORS:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "L_Copy_Assignment:\t" << this << endl;
		return *this;
	}

	//               ADDING ELEMENTS:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			//Когда в списке появляется первый элемент, он одновременно 
			//является и головой и хвостом
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
			cout << "Error: Выход за переделы списка!" << endl;
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
		//New->pNext = Temp;
		//New->pPrev = Temp->pPrev;
		//Temp->pPrev->pNext = New;
		//Temp->pPrev = New;
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
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
	void erase(int Index)
	{
		if (Index >= size)
		{
			cout << "Error: Выход за переделы списка!" << endl;
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
		Element* Erased = Temp;
		Temp->pNext->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = Temp->pNext;
		delete Temp;
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
		cout << "Количество элементов списка: " << size << endl;
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

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: ";cin >> n;
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
	cout << "Введите индекс добавляемого элемента: ";cin >> index;
	cout << "Введите значение добавляемого элемента: ";cin >> value;
	list.insert(value, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: ";cin >> index;
	list.erase(index);
	list.print();
	list.print_reverse();

#endif // BASE_CHECK

	List list = { 3, 5, 8, 13, 21 };
	list.print();

	List list1;
	list1 = list;
	//list1.print();
	for (int i : list1)cout << i << tab; cout << endl;

	for (List::ReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;

}