/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
			一元多项式相乘
----------------------------------------------------------------------------------------------------------------------------------------------------------------*/

#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct Linklist
{
	float coef;						//coefficient
	int expn;						//exponent
	struct Linklist *next;
}Node,*Link;

void attach(float coef, int expn, Link *L)			//attach the element to the end of linklist
{
	Node *P;
	P = new Node;
	P->coef = coef;
	P->expn = expn;
	P->next = NULL;
	(*L)->next = P;
	*L = P;
}

Link creatlist()
{
	Node *head,*cur,*temp;
	head = new Node;
	
	if (!head)
		cout << "Error!";

	head->next = NULL;
	cur = head;
	float a; int b;

	cout << "Please input the linkedlist:" << endl;
	scanf("%f %d", &a, &b);
	while (a!=0)
	{
		attach(a, b,& cur);
		scanf("%f %d", &a, &b);
	}

	temp = head;					//delete the head node
	head = head->next;
	delete temp;

	return head;
}

void destroylist(Node *head)
{
	Node *temp;
	
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

Link add(Link L1, Link L2)
{
	Node *head, *cur,*temp;
	float sum;
	head = new Node;
	head->next = NULL;
	cur = head;

	while (L1&&L2)
	{
		if (L1->expn == L2->expn)
		{
			sum = L1->coef + L2->coef;
			if (sum)
				attach(sum, L1->expn, &cur);
			L1 = L1->next;
			L2 = L2->next;
		}
		else if (L1->expn > L2->expn)
		{
			attach(L2->coef, L2->expn, &cur);
			L2 = L2->next;
		}
		else
		{
			attach(L1->coef, L1->expn, &cur);
			L1 = L1->next;
		}
	}

	for (; L1; L1 = L1->next)
		attach(L1->coef, L1->expn, &cur);
	for (; L2; L2 = L2->next)
		attach(L2->coef, L2->expn, &cur);

	temp = head;						//delete the head node
	head = head->next;
	delete temp;

	return head;
}

Link mult(Link L1, Link L2)
{
	Node *cur, *head, *temp,*startL2;
	head = new Node;
	head->next = NULL;
	cur = head;
	startL2 = L2;
	float c;
	int e;
	
	while (L2)							//the first number of item L1 multiply L2
	{
		attach(L1->coef*L2->coef, L1->expn + L2->expn, &cur);
		L2 = L2->next;
	}
	L1 = L1->next;
	L2 = startL2;

	for (cur = head; L1; L1 = L1->next)
	{
		for (; L2; L2 = L2->next)
		{
			c = L1->coef*L2->coef;
			e = L1->expn+L2->expn;

			while (cur->next&&cur->next->expn > e)
				cur = cur->next;
		
			if (cur->next&&cur->next->expn == e)
			{
				if (cur->next->coef + c)				//coef!=0
					cur->next->coef += c;
				else						        //delete the node
				{
					temp = cur->next;
					cur->next = cur->next->next;
					delete temp;
				}
			}
			else								//expn<e
			{
				temp = new Node;
				temp->coef = c;
				temp->expn = e;						//attach the new list to the result list
				temp->next = cur->next;
				cur->next = temp;
				cur = cur->next;
			}
		}
		L2 = startL2;
	}

	temp = head;									//delete the head node
	head = head->next;
	delete temp;

	return head;
}


void print(Link L)
{
	while (L)
	{
		cout << L->coef << '\t';
		cout << L->expn << '\t';
		L = L->next;
	}
}

int main(void)
{
	Link list1, list2, temp1, temp2;
	list1 = creatlist();
	list2 = creatlist();
	
	temp1=add(list1, list2);
	cout << "The added polynomial is:" << endl;
	print(temp1);
	cout << endl;

	temp2 = mult(list1, list2);
	cout << "The multiplied polynomial is:" << endl;
	print(temp2);

	destroylist(list1);
	destroylist(list2);


	system("Pause");
		
}
