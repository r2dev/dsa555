#include "a3.h"
#include "timer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <map>
#define NUMBUILDINGS 200000
#define MAXWIDTH 500000
#define BINARY 0
#define ASCII 1
#define READFORMAT ASCII
#define TIMEDITERATIONS 100

using namespace std;

int findSilhouette(Building buildingList[], int numBuildings, int silhouette[])
{
	std::vector<Pos> ground;
	std::vector<int> heap;
	std::make_heap(heap.begin(), heap.end());
	int max = -1;
	for (int i = 0; i != numBuildings; i++) {
		Pos left(buildingList[i].left_, buildingList[i].height_, true);
		Pos right(buildingList[i].right_, buildingList[i].height_, false);
		ground.push_back(left);
		ground.push_back(right);
		if (buildingList[i].right_ > max) {
			max = buildingList[i].right_;
		}
	}
	std::sort(ground.begin(), ground.end(), [](const Pos& a, const Pos& b){
		if (a.pos == b.pos) {
			return (a.isLeft < b.isLeft);
		}
		return (a.pos < b.pos); 
	}
	);
	auto groundIter = ground.begin();
	auto iter = 0;
	while (true) {
		if (iter == groundIter->pos) {
			//hit the edge
			if (groundIter->isLeft == true) {
				//add to the heap
				heap.push_back(groundIter->height);
				std::push_heap(heap.begin(), heap.end());
			}
			else {
				auto found = std::find(heap.begin(), heap.end(), groundIter->height);
				if (found != heap.end())
					heap.erase(found);
				std::make_heap(heap.begin(), heap.end());
			}
			groundIter++;
		}
		if (groundIter == ground.end()) {
			break;
		}
		if (iter == groundIter->pos) {//again?
			//dont update i
			continue;
		}
		else {
			if (!heap.empty()) {
				silhouette[iter] = heap.front();
			}
			else {
				silhouette[iter] = 0;
			}
			iter++;
		}
	}
	return max;
}

int main(void){
	Building testerList[4] = { { 1, 4, 4 }, { 7, 12, 6 }, { 6, 8, 10 }, { 5, 14, 3 } };
	int testerSilhouette[14] = { 0 };
	int testerCorrect[14] = { 0, 4, 4, 4, 0, 3, 10, 10, 6, 6, 6, 6, 3, 3 };

	bool completed = true;
	Building* bList = new Building[NUMBUILDINGS];
	int* silhouette = new int[MAXWIDTH];
	int* correct = new int[MAXWIDTH];

	findSilhouette(testerList, 4, testerSilhouette);

	for (int i = 0; i < 14; i++){
		if (testerSilhouette[i] != testerCorrect[i]){
			completed = false;
			cout << "silhouette error" << endl;
			cout << "at position: " << i << endl;
			cout << "your height: " << testerSilhouette[i] << endl;
			cout << "correct height: " << testerCorrect[i] << endl;
		}
	}
	if (completed){
#if READFORMAT == BINARY
		ifstream fs("a3data.dat", ios::binary);
		ifstream fs2("a3output.dat", ios::binary);
#else
		ifstream fs("a3data.txt");
		ifstream fs2("a3output.txt");
#endif

		for (int i = 0; i < MAXWIDTH; i++){
			silhouette[i] = 0;
		}
		for (int i = 0; i < NUMBUILDINGS; i++){
#if READFORMAT == BINARY
			fs.read((char*)(bList + i), sizeof(int) * 3);
#else
			fs >> bList[i].left_ >> bList[i].right_ >> bList[i].height_;
#endif
		}

		findSilhouette(bList, NUMBUILDINGS, silhouette);
#if READFORMAT == BINARY
		fs2.read((char*)correct, sizeof(int)*MAXWIDTH);
#else
		for (int i = 0; i<MAXWIDTH; i++){
			fs2 >> correct[i];
	}
#endif
		for (int i = 0; i < MAXWIDTH; i++){
			if (silhouette[i] != correct[i]){
				completed = false;
				cout << "silhouette error" << endl;
				cout << "at position: " << i << endl;
				cout << "your height: " << silhouette[i] << endl;
				cout << "correct height: " << correct[i] << endl;
			}
		}
}
	if (completed){
		cout << "Testing passed, now to check speed..." << endl;
		cout << "The main will now call your findSilhouette() " << TIMEDITERATIONS << " times" << endl;
		Timer t;
		t.start();
		for (int i = 0; i < TIMEDITERATIONS; i++){
			findSilhouette(bList, NUMBUILDINGS, silhouette);
		}
		t.stop();
		cout << TIMEDITERATIONS << " calls to findSilhouette() took : " << t.currtime() << " seconds" << endl;
	}
	return 0;
}