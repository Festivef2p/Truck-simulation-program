#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"
#include "Cargo.h"

template <typename T>
class OriginalList
{
protected:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
public:


	OriginalList()
	{
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~OriginalList()
	{
		DeleteAll(); 
	}

	///////////////////////////////////////////////////////////

	void PrintList()	const
	{		
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}

	////////////////////////////////////////////////////////////////////////

	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
	}

	int getCounter()
	{
		int count = 0;
		Node<T>* P = Head;

		if(Head == nullptr)
			return count;

		while(P)
		{
			count++;
			P = P->getNext();
		}
		return count;
	}

	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		if(Head == nullptr)
			Head = R;
		else
		{
			Node<T>* P = Head;
			while(P->getNext() != nullptr)
			{
				P = P->getNext();
			}
			P->setNext(R);
			R->setNext(nullptr);
		}
	}	

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key);

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T &value);

	//[4] DeleteFirst
	//Deletes the first node in the list
	void DeleteFirst(T& FirstEntry)
	{
		FirstEntry = Head->getItem();
		Node<T> *P = Head;
		P = Head->getNext();
		delete Head;
		Head = P;

	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast();

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T &value);	

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T &value);	

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const OriginalList& L);

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse();

	bool isEmpty()  
	{
		if (Head == nullptr) 
			return true;
		return false;
	}

};

template< class T >
class LinkedList : public OriginalList<T>                         //List for all Data types
{
};

template<>
class LinkedList<Cargo*> :public  OriginalList<Cargo*>            //specialized list for Cargo data type
{
public:

	Cargo* CancelCargoFromList(int id)
	{
		if(isEmpty())
			return nullptr;

		bool exist = false;                 //To check if the cargo is exist or not

		if(Head->getItem()->getid() == id)
		{
			Node<Cargo*>* temp = Head;
			Head = Head->getNext();
			return temp->getItem();
			exist = true;
			delete temp;
			temp = nullptr;
		}

		Node<Cargo*>* cur = Head->getNext();
		Node<Cargo*>* prev = Head;

		while (cur)
		{
			if (cur->getItem()->getid() == id)
			{
				prev->setNext( cur->getNext() );
				exist =true;
				return cur->getItem();
			}
			else
			{
				cur = cur->getNext();
				prev = prev->getNext();
			}
		}

		if (exist == false)
			return nullptr;

		delete cur;
		cur = nullptr;
		delete prev;
		prev = nullptr;
	}

};
#endif	
