#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Node {
public:
	int element;
	Node* next;
	Node* prev;
};

class LinkedList {
public:
	Node* head;
	Node* tail;
	void moveToHead(Node*);
	void push(int);
	LinkedList();
};

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
}

void LinkedList :: push(int element)
{
	// I created a node like this, since I did not want to change the given skeleton code
	// Creating a constructor for Node class would be nicer
	Node* node = new Node();
	node->element = element;
	node->next = NULL;
	if(head == NULL)
	{
		head = node;
		tail = node;
		node->prev = NULL;
		return;
	}
	node->prev = tail;
	tail->next = node;
	tail = node;
}


void LinkedList :: moveToHead(Node* node)
{
	if(node == head)
	{
		return;
	}
	for(Node* n = node->prev; node != head; n = node->prev)
	{
		// swap node with its prev

		if(node == tail)
		{
			tail = n;
		}
		if(n == head)
		{
			head = node;
		}
		n->next = node->next;
		if(n->next != NULL) n->next->prev = n; // if n is not tail
		node->next = n;

		node->prev = n->prev;
		if(node->prev != NULL) node->prev->next = node; // if node is not head
		n->prev = node;
	}

}


int main(int argc, char** argv) {
	ifstream testfile;
	testfile.open(argv[1]); //read the inputs from test file

	int capacity; //capacity is the maximum number of elements in the cache, defined as k in pdf
	int element_number; //number of different elements that can possibly requested, equals to k+1 in our case
	int request_number; //number of requests, defined as n in pdf

	testfile >> capacity;
	element_number = capacity + 1;

	int cache_size = 0; //cache size keeps number of elements in the cache, initially zero
	vector<int> cache(element_number, 0); //cache is created as empty as all indexes are 0

	testfile >> request_number;
	vector<int> requests(request_number);
	for (int i = 0; i < request_number; i++)
		testfile >> requests[i];
	
	vector<int> fif(requests.size()); //to keep the farthest element for each request

	vector<int> elements(element_number); //elements array {0, 1, ... , k}
	for (int i = 0; i < element_number; i++)
		elements[i] = i;

	vector<Node*> addresses; //array for keeping the address of double linked list nodes of elements
	//addresses[i] keeps the node address for elements[i]

	/* IMPLEMENT HERE */

		// 1. create the double linked list for elements vector, you can use Node class defined above
		// keep each node's address in addresses array
		LinkedList* linked_list = new LinkedList();
		for(auto v: elements)
		{
			linked_list->push(v);
			addresses.push_back(linked_list->tail);
		}
	 
		// 2. fill the fif (farthest-in-future) array considering the pseudocode given in pdf.
	
		for(int i = request_number-1; i >= 0 ; i--)
		{
			Node* node = addresses[requests[i]];
			linked_list->moveToHead(node);
			fif[i] = linked_list->tail->element;
		}

		// 3. process the requests and print out necessary outputs, you can use following syntax:
		
		for (int i = 0; i < request_number; i++)
		{
			if(cache[requests[i]] == 0)
			{
				cout << "cache miss" << endl;
				int number_of_zeroes = 0;
				
				if(cache_size == capacity) // cache is full
				{
					cache[fif[i]] = 0;
					cache[requests[i]] = 1;
					cout << "cache is full, element " << fif[i] << " is evicted" << endl;
					cout << "element " << requests[i] << " is added into the cache" << endl;

				}
				else	// cache is not full
				{
					cache[requests[i]] = 1;
					cache_size += 1;
					cout << "element " << requests[i] << " is added into the cache" << endl;
				}
			}
			else
			{
				cout << "cache hit" << endl;
			}	
		}

	return 0;
}