#pragma once
#include <vector>
#include "Point.h"
#include <iostream>
using namespace std;
class List
{
	size_t size;
	struct Node
	{
		Point point;
		Node * next;
		Node(const Point & p) : point(p.x, p.y, p.z), next(nullptr){}
	};
	Node * first;

	Node * find(const size_t);
	void push(const Point &, const size_t);
	void push(const List &, const size_t);
	void pop(const size_t);
	void multiply(const size_t, const Point& );
	void multiply(const size_t);

public:
	List();
	List(const List&);
	~List();
	enum Error
	{
		SUCCESS,
		LIST_EMPTY,
		OUT_OF_BOUNDS
	};
	Error pop_back();
	Error pop_front();
	size_t getSize();
	Error push_back(const Point&);
	Error find(Point&, const std::size_t);
	Error insert(const Point&, const std::size_t);
	List operator+(const List&);
	List& operator+=(const List&);
	List& operator=(const List&);
	List operator--(int);
	List operator*(const List&);
	List operator*(const int);
	List operator[](Point&);
	List operator++(int);
	//List operator<<(const List& list);
	friend ostream& operator<<(ostream& os, const List& li);
	//Proszê pamiêtaæ, ¿e to nie jest pe³na implementacja, nale¿y kod uzupe³niæ zgodnie z instrukcj¹
};

