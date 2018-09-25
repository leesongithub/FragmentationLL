// TESTING linked lists
#include <string>
#include <cstdlib>
using namespace std;
class LinkedList{
private:	
	struct Node {
		string data;
		Node *next;
	};
	typedef struct Node * nodePointer;
	nodePointer head;
	nodePointer tail;
	
	//public member
public:
		// constructor 
		LinkedList(){
			head = NULL; // set head to NULL
			tail = NULL;
		}
		// destructor
		~LinkedList(){
			Node *next = head;
			
			while(next) {
				Node *deleteMe = next;
				next = next->next;
				delete deleteMe;
			}
		}
		void addNode(string valueToBeAdded);

		// mine: 
		void printMemory();
		void fragmentation();
		void killProgram();
		void addProgram();
		

}; // ends class LinkedList
int menu();
