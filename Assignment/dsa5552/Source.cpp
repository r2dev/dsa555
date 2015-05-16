#include "Table.h"
#include <cstdio>
#include <cstdlib>
int main()
{
	std::FILE* fp = fopen("dictionary.txt", "r");
	char ** wordlist = new char*[200000];
	char curr[50];
	SimpleTable<int> a(50000);
	for (int i = 0; i<200000; i++){
		fscanf(fp, "%s\n", curr);                 //read in a word from data file
		wordlist[i] = new char[strlen(curr) + 1];   //record it
		strcpy(wordlist[i], curr);
	}
	for (int i = 0; i < 50000; i++) {
		a.update(wordlist[i], i);
	}
	a.print();
	system("pause");
}