#ifndef QUADTREE
#define QUADTREE

#include "ME\MyEngine.h"
#include "GameObject.h"

using namespace std;

class QuadTree
{
public:
	vector<vector<GameObject*>> groups; // List containing groups of gameobjects
	int minNumObjects; // Minimum number of gameobjects per quad

	struct Square{
		matrix4 position;
		vector3 scale;

		Square() {};

		Square(matrix4 p, vector3 s) {
			position = p;
			scale = s;
		}

		void Draw() {
			MeshManagerSingleton* meshManager = MeshManagerSingleton::GetInstance();
			meshManager->AddCubeToQueue(position * glm::scale(scale), MERED, MERENDER::WIRE);
		}
	};

	vector<Square*> squares; // Used to draw quadtree to screen

	Square* drawTest;


	/* Constructor */
	QuadTree();

	/* Destructor */
	~QuadTree(void);

	/* GetGroups */
	/* Returns list of lists containing objects */
	vector<vector<GameObject*>> GetGroups();

	/* GetSquares */
	/* Returns list containing list of squares in quadtree */
	vector<Square*> GetSquares();

	/* GenerateGroups */
	/* Generates quadtree and returns list of groups */
	vector<vector<GameObject*>> GenerateGroups(vector<GameObject*> gameObjects, matrix4 pos, vector3 scale);

	/* GenerateQuadTree */
	/* Generates quadtree from gameobjects in game */
	void GenerateQuadTree(vector<GameObject*> gameObjects, matrix4 pos, vector3 scale);

	/* DrawTree */
	/* Draws QuadTree to screen */
	void DrawTree();
};
#endif

