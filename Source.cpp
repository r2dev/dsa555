#include "Stack.h"
#include "Queue.h"
int main()
{

	Stack<int> a;
	a.push(10);
	a.push(20);
	a.push(30);
	a.pop();
	a.printEverything();
	system("pause");

}