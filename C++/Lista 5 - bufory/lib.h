#pragma once

#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <conio.h>

using namespace std;

class Node
{
	public:
		double Value;
		Node *Next;
		Node *Prev;
		Node();
		double gotowy();
};

class List : public Node
{
	Node *First;
	Node *Last;
	int Size;
	protected:
		Node* GetFirst();
		Node* GetLast();
	public:
		List();
		List clone();
		friend istream& operator >> (istream &streamin, List &L);
		void Add(int Index, double Value);
		bool Remove(int Index = 0);
		virtual void WriteAll();
		bool Empty();
		double Indeks(int Index);
		int GetSize();
		double Front();
		double Back();
		
		virtual ~List();

};

class Queue : private List
{
	public:
		void operator+=(double Value);
		bool operator--();
		void WriteAll();
		int ile();
};
class Stack : private List
{
	public:
		void operator+=(double Value);
		bool operator--();
		void WriteAll();
		int ile();
};