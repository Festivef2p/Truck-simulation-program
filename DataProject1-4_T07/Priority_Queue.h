#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

template<typename T>
struct n {
	int p;
	T info;
	struct n *l;
};

template<typename T>
class Priority_Queue {
private:
	n<T> *f;
public:
	Priority_Queue() {
		f = NULL;
	}
	void insert(T i, int p) {
		n<T> *t, *q;
		t = new n;
		t->info = i;
		t->p = p;
		if (f == NULL || p < f->p) {
			t->l= f;
			f = t;
		} else {
			q = f;
			while (q->l != NULL && q->l->p <= p)
				q = q->l;
			t->l = q->l;
			q->l = t;
		}
	}
	void del() {
		n *t;
		if(f == NULL)
			cout<<"Queue Underflow\n";
		else {
			t = f;
			cout<<"Deleted item is: "<<t->info<<endl;
			f = f->l;
			free(t);
		}
	}
	void show(){
		n *ptr;
		ptr = f;
		if (f == NULL)
			cout<<"Queue is empty\n";
		else {
			cout<<"Queue is :\n";
			cout<<"Priority Item\n";
			while(ptr != NULL) {
				cout<<ptr->p<<" "<<ptr->info<<endl;
				ptr = ptr->l;
			}
		}
	}
};