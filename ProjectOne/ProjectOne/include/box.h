#ifndef __box_h_
#define __box_h_

#include "Ogre.h" 
#include <cstdio>
#include "BaseApplication.h"
#include <ctime>
#include "Cube.h"


class box
{
	public:
    /*! keeps the cube at postion 0 inside the matrix */
	int cube0boundaryX, cube0boundaryX2;
	 /*! keeps the cube at postion 1 inside the matrix */
	int cube1boundaryX, cube1boundaryX2;
	 /*! keeps the cube at postion 2 inside the matrix */
	int cube2boundaryX, cube2boundaryX2;
	 /*! keeps the cube at postion 0 inside the matrix */
	int cube0boundaryZ, cube0boundaryZ2;
	 /*! keeps the cube at postion 1 inside the matrix */
	int cube1boundaryZ, cube1boundaryZ2;
	 /*! keeps the cube at postion 2 inside the matrix */
	int cube2boundaryZ, cube2boundaryZ2;
	 /*! keeps the cube at postion 0 inside the matrix */
	int cube0BoundaryY; 
	 /*! stores if the shape is alive */
	bool alive;
	 /*! stores the shapes name */
	string myName;
	 /*! checks if shadow is on */
	bool shadowOff;
	 /*! the amount of cubes in the shapes array */
	int cubeAmount;
	 /*! tracks the orientation of the shape */
	enum Orientation {xAlligned, zAlligned, yAlligned} orientation;
	 /*! constructor */
	box(Ogre::SceneManager *, string, string); 
    /*! update method */
	void Update(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D,int mainTickValue); 
	 /*! checks if the cube is dropping method */
	void isDropping(vector<vector<vector<Cube*>>> & array3D);
	 /*! checks if the last cube is ready to drop */
	bool cubeReadyToDrop[8];
	 /*! the size of the cells in the matrix */
	int cellSize;
	 /*!rotate the shape right */
	void rotateRight(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);


	 /*! stores time */
	int time; 
	 /*! stores zDiretion */
	int zDirection;
	 /*! strores xDiretion */
	int xDirection;
	 /*! array of cube objects */
	vector<Cube*> cubes;
	 /*! oger timer */
	Ogre::Timer rotate_timer;
	 /*! counts ticks per rotation */
	double rotateTick;
	 /*! tracks movement time */
	Ogre::Timer move_timer;
	 /*! counts movment ticks */
	double moveTick;
	 /*! oger timer */
	Ogre::Timer _timer;
	 /*! stores ticks */
	double tick;
	 /*! tracks tick value */
	double tickValue;

};
#endif