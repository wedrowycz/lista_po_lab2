#include "List.h"
#include <vector>
#include <iostream>
using namespace std;


List::Node * List::find(const size_t idx)
{
	Node * node = first;

	for (size_t i = 0; i < idx; i++)
	{
		node = node->next;
	}

	return node;
}

/// <summary>
/// Wstawienie nowego punktu wmiejsce idx
/// </summary>
/// <param name="point"></param>
/// <param name="idx"></param>
void List::push(const Point & point, const size_t idx)
{
	if (idx == 0)
	{
		Node * tail = first;
		first = new Node(point);
		first->next = tail;
	}
	else
	{
		Node * prev = find(idx - 1);
		Node * tail = prev->next;
		prev->next = new Node(point);
		prev->next->next = tail;
	}
	size++;
}

void List::push(const List & list, const size_t idx)
{
	List copy(list);//konstruktor kopiuj¹cy
	Node * it = copy.first;
	if (idx == 0)
	{
		Node * tail = first;
		Node * last = nullptr;
		if (it)
		{
			first = new Node(it->point);
			last = first;
			it = it->next;
		}
		while (it)
		{
			last->next = new Node(it->point);
			last = last->next;
			it = it->next;
		}
		if(last) last->next = tail;
	}
	else
	{
		Node * prev = find(idx - 1);
		Node * tail = prev->next;
		while (it)
		{
			prev->next = new Node(it->point);
			prev = prev->next;
			it = it->next;
		}
		prev->next = tail;
	}
	size += copy.size;
}

/// <summary>
/// usuwanie idx elementu
/// </summary>
/// <param name="idx">numer elementu do usuniêcia, 0-based</param>
void List::pop(const size_t idx)
{
	if (idx == 0)
	{
		Node * tail = first->next;
		delete first;
		first = tail;
	}
	else
	{
		Node * prev = find(idx - 1);
		Node * tail = prev->next->next;
		delete prev->next;
		prev->next = tail;
	}
	size--;
}

void List::multiply(const size_t idx, const Point& punkt) {
	if (idx == 0) {
		int t = size;
		for (int i = t; i >= 0; i--) {
			pop_back();
			size--;
		}
	}
	else {
		const int ile = size;
		//push(punkt, size == 0 ? 0 : size - 1);
		for (int i = 0; i < idx; i++) {
			for (int j=0;j<ile;j++)
			{
				push_back(punkt);
			}
		}
	}
}

/// <summary>
/// multiply operator - lista jest kopiowana idx-1 razy - ¿eby byy³o arytmetycznie
/// wynikowy rozmiar to rozmiar startowy + idx-1 razy rozmiar startowy - ³¹cznie rozmiar ma rozmiar startowy * idx
/// </summary>
/// <param name="idx">multiplier-mno¿nik</param>
void List::multiply(const size_t idx)
{
	if (idx == 0) {
		int t = size;
		for (int i = t; i >= 0; i--) {
			pop_back();
			size--;
		}
	}
	else
	{
		int startsize = this->size;
		
		for (int i = 0; i < idx-1; i++) {
			Node* tmp = first;
			int tmpcnt = 0;
			do {
				Point *pkt = new Point(tmp->point);
				this->push_back(*pkt);
				tmpcnt++;
				tmp = tmp->next;
			} while (tmp != NULL && tmpcnt < startsize);
		}
	}

}

/// <summary>
/// default constructor
/// </summary>
List::List() : size(0), first(nullptr){	
}

/// <summary>
/// copy constructor
/// </summary>
/// <param name="list"></param>
List::List(const List & list) : size(list.size), first(nullptr)
{
	Node * it = list.first;
	Node * last = first;
	if (it)
	{
		first = new Node(it->point);
		last = first;
		it = it->next;
	}
	while (it)
	{
		last->next = new Node(it->point);
		last = last->next;
		it = it->next;
	}
}

/// <summary>
/// Custom-init constructor
/// </summary>
/// <param name=""></param>
List::List(const vector<Point>& inp): size(0), first(nullptr)
{
	for (int i = 0; i < inp.size(); i++)
	{
		push_back(inp[i]);
	}
	
}

/// <summary>
/// destructor
/// </summary>
List::~List()
{
	Node* tmp = this->first;
	while (tmp != NULL)
	{
		this->first = tmp->next;
		delete(tmp);
		tmp = this->first;
	}

}

/// <summary>
/// pops-removes first element
/// </summary>
/// <returns>result code</returns>
List::Error List::pop_front()
{
	List::Error error = List::Error::SUCCESS;

	if (size == 0)
	{
		error = List::Error::LIST_EMPTY;
	}
	else
	{
		pop(0);
	}

	return error;
}

/// <summary>
/// removes item from tail
/// </summary>
/// <returns></returns>
List::Error List::pop_back()
{
	List::Error error = List::Error::SUCCESS;

	if (size == 0)
	{
		error = List::Error::LIST_EMPTY;
	}
	else
	{
		pop(size-1);
	}

	return error;
}


/// <summary>
/// size getter
/// </summary>
/// <returns>int, number of elements</returns>
size_t List::getSize()
{
	return size;
}

/// <summary>
/// inserts punkt item to the end
/// </summary>
/// <param name="punkt"></param>
/// <returns></returns>
List::Error List::push_back(const Point& punkt)
{
	List::Error error = List::Error::SUCCESS;
	push(punkt, size == 0?0:size );

	return error;
}

List::Error List::find(Point& punkt, const std::size_t itemno)
{
	List::Error error = List::Error::SUCCESS;

	if ((itemno < 0) || (itemno > size - 1)){
		error = List::Error::OUT_OF_BOUNDS;
	}
	else if (size == 0) 	{
		error = List::Error::LIST_EMPTY;
	}
	else {
		Node* ff = find(itemno);
		punkt.x = ff->point.x;
		punkt.y = ff->point.y;		
	}


	return error;
}

List::Error List::insert(const Point& punkt, const std::size_t itemno)
{

	List::Error error = List::Error::SUCCESS;

	if ((itemno < 0) || (itemno > size )) {
		error = List::Error::OUT_OF_BOUNDS;
	}
	else if (size == 0) {
		error = List::Error::LIST_EMPTY;
	}
	else {
		push(punkt, itemno);
		
	}


	return error;
}

List List::operator+(const List& list)
{
	List copy(*this);
	copy.push(list, copy.size);
	return copy;
}

List& List::operator+=(const List& list)
{
	push(list, size);
	return *this;
}

List & List::operator=(const List & list)
{
	List copy(list);
	this->~List(); 
	push(copy, 0);
	return *this;
}

List List::operator--(int)
{
	List copy(*this);
	pop_back();
	return copy;
}
List List::operator*(const List& list)
{
	List copy(list);
	//multiply(idx???, punkt???);
	return *this;
}

/// <summary>
/// multiply operator - lista jest kopiowana cnt-1 razy - ¿eby byy³o arytmetycznie
/// wynikowy rozmiar to rozmiar startowy + cnt-1 razy rozmiar startowy
/// </summary>
/// <param name="cnt"></param>
/// <returns></returns>
List List::operator*(const int cnt)
{
	List copylist(*this);
	copylist.multiply(cnt);
	return copylist;
}

List List::operator[](Point& punkt)
{
	find(punkt, size);
	return *this;
}

List List::operator++(int)
{
	List copy(*this);
	//multiply(0,punkt???)
	return copy;
}

//operator przesuniêcia to nie ten
//List List::operator<<(const List& list)
//{
//	return list;
//}

/// <summary>
/// operator wypisania
/// </summary>
/// <param name="os"></param>
/// <param name="li"></param>
/// <returns></returns>
ostream& operator<<(ostream& os, const List& li)
{
	os <<"size:"<< li.size << " first : " << li.first->point.x << ":" << li.first->point.y << ":" << li.first->point.y;
	return os;
}
