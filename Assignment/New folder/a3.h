#ifndef A3_H
#define A3_H
struct Building{
	int left_;          //x position of left side of building
	int right_;         //x position of right side of building
	int height_;        //height of the building
};

int findSilhouette(Building buildingList[], int numBuildings, int silhouette[]);

/*put your unique header file code here if you need to*/

struct Pos {
	int pos;
	int height;
	bool isLeft;
	Pos(int a, int b, bool c) {
		pos = a;
		height = b;
		isLeft = c;
	}
};

#endif