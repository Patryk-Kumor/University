#include "lib.h"

using namespace std;

Node::Node(): Next(NULL), Prev(NULL){;}

//----------------------------------------------

Node* List::GetFirst()
	{ return First; }

Node* List::GetLast()
	{ return Last; }

List::List()
		: First(NULL), Last(NULL), Size(0)
	{
		;
	}

istream& operator >> (istream &streamin, List &L)
{
	cout << "\nRozmiar: ";
	int rozmiar; cin >> rozmiar;
	double liczba;

	streamin.clear();
	streamin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	for (int i = 0; i < rozmiar; i++)
	{
		streamin >> liczba;
		L.Add(i,liczba);
	}

	return streamin;
}
List List::clone()
{
	return *this;
}
double Node::gotowy()
{
	return this->Value; 
}


void List::Add(int Index, double Value)
	{
		if (Index>Size  || Index<0 ) //Poza lista
		{
			cerr << "Error: [Element doesn't exist]\n";
			return;
		}

		Node *NewNode = new Node;
		NewNode->Value = Value;

		if (First)
		{
			if (Index == 0)
			{
				NewNode->Next = First;
				First->Prev = NewNode;
				First = NewNode;
			}
			else if (Index == Size)
			{
				NewNode->Prev = Last;
				Last->Next = NewNode;
				Last = NewNode;
			}
			else
			{
				Node *temp = First;
				while (temp->Next && Index)
				{
					temp = temp->Next;
					--Index;
				}
				Node *temp_before = temp->Prev;
				temp_before->Next = NewNode;
				NewNode->Prev = temp_before;
				NewNode->Next = temp;
				temp->Prev = NewNode;
			}
		}
		else
		{
			First = NewNode;
			Last = NewNode;
		}
		++Size;
	}

bool List::Remove(int Index)
	{
		if (!Size)
		{
			cout << "Error: [List is empty]\n";
			return false;
		}
		if (Index >= Size || Index<0) //Poza lista
		{
			cout << "Error: [Element doesn't exist]\n";
			return false;
		}
		if (Size == 1)
		{
			if (Index == 0)
			{
				delete First;
				First = NULL;
				Last = NULL;
			}
		}
		else
		{
			if (Index == 0)
			{
				Node *ToRemove = First;
				First = First->Next;
				First->Prev = NULL;
				delete ToRemove;
			}
			else if (Index == Size - 1)
			{
				Node *ToRemove = Last;
				Last = Last->Prev;
				Last->Next = NULL;
				delete ToRemove;
			}
			else
			{
				Node *temp = First;
				while (temp->Next && Index)
				{
					temp = temp->Next;
					--Index;
				}
				Node *ToRemove = temp;
				temp->Prev->Next = temp->Next;
				temp->Next->Prev = temp->Prev;
				delete ToRemove;
			}
		}
		--Size;
		return true;
	}

double List::Indeks(int Index)
{
	if (!Size)
	{
		cerr << "Error: [List is empty]\n";
		return 0;
	}
	if (Index >= Size || Index<0) //Poza lista
	{
		cerr << "Error: [Element doesn't exist]\n";
		return 0;
	}
	if (Size == 1)
	{
		if (Index == 0)
		{
			return First->Value;
		}
	}
	else
	{
		if (Index == 0)
		{
			return First->Value;
		}
		else if (Index == Size - 1)
		{
			return Last->Value;

		}
		else
		{
			Node *temp = First;
			while (temp->Next && Index)
			{
				temp = temp->Next;
				--Index;
			}
			return temp->Value;
			
		}
	}
}

void List::WriteAll()
	{
		cout << "List: ";
		if (First)
		{
			Node *temp = First;
			while (temp)
			{
				cout << temp->Value << ' ';
				temp = temp->Next;
			}
		}
		else cout << "[Is empty]";
		cout << '\n';
	}

bool List::Empty()
	{
		return !Size;
	}

int List::GetSize()
	{
		return Size;
	}

double List::Front()
	{
		if (Size)
		{
			return First->Value;
		}
		return 0;
	}

double List::Back()
	{
		if (Size)
		{
			return Last->Value;
		}
		return 0;
	}

List::~List()
{
	while(Size != 0);
	{this->Remove(); }

	cout << "<deleted>";
}


//----------------------------------------------

int Queue::ile()
{
	int i = 0;
	if (GetFirst())
	{
		Node *temp = GetFirst();
		while (temp)
		{
			i++;
			temp = temp->Next;

		}
		return i;
	}
	else return 0;
}

void Queue::operator+=(double Value)
	{
		Add(GetSize(), Value);
	}

bool Queue::operator--()
	{
		return Remove(0);
	}

void Queue::WriteAll()
	{
		cout << "Queue: ";
		if (GetFirst())
		{
			Node *temp = GetFirst();
			while (temp)
			{
				cout << temp->Value << ' ';
				temp = temp->Next;
			}
		}
		else cout << "[Is empty]";
		cout << '\n';
	}



//----------------------------------------------
int Stack::ile()
{
	int i = 0;
	if (GetFirst())
	{
		Node *temp = GetFirst();
		while (temp)
		{
			i++;
			temp = temp->Next;
		}
		return i;
	}
	else return 0;
}
void Stack::operator+=(double Value)
	{
		Add(GetSize(), Value);
	}

bool Stack::operator--()
	{
		return Remove((GetSize()) - 1);
	}

void Stack::WriteAll()
	{
		cout << "Stack: ";
		if (GetFirst())
		{
			Node *temp = GetFirst();
			while (temp)
			{
				cout << temp->Value << ' ';
				temp = temp->Next;
			}
		}
		else cout << "[Is empty]";
		cout << '\n';
	}

