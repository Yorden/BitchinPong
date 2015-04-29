#ifndef QUADTREE
#define QUADTREE

#include "ME\MyEngine.h"
#include "GameObject.h"

using namespace std;

class QuadTree
{
	vector<vector<GameObject*>> groups; // List containing groups of gameobjects
	int minNumObjects; // Minimum number of gameobjects per quad

	struct Square{
		matrix4 position;
		vector3 scale;

		Square(matrix4 p, vector3 s) {

		}
	};

	vector<vector<Square>> squares; // Used to draw quadtree to screen

public:
	/* Constructor */
	QuadTree();

	/* Destructor */
	~QuadTree(void);

	/* GetGroups */
	/* Returns list of lists containing objects */
	vector<vector<GameObject*>> GetGroups();

	/* GetSquares */
	/* Returns list containing list of squares in quadtree */
	vector<vector<Square>> GetSquares();

	/* GenerateQuadTree */
	/* Generates quadtree from gameobjects in game */
	void GenerateQuadTree(vector<GameObject*> gameObjects, matrix4 pos, vector3 scale);
};
#endif

