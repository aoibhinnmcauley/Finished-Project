#ifndef __tShapeOpp_h_
#define __tShapeOpp_h_

#include "Ogre.h" 
#include <cstdio>
#include "BaseApplication.h"
#include <ctime>
#include "Cube.h"


class tShapeOpp
{

	/*! this is entire class is very similar to tShape although has some different bounds checking a rotation */
	public:
	int cube0boundaryX, cube0boundaryX2;
	int cube1boundaryX, cube1boundaryX2;
	int cube2boundaryX, cube2boundaryX2;
	int cube3boundaryX, cube3boundaryX2;
	int cellX;
	int cellY;
	int cellZ;
	int cube0boundaryZ, cube0boundaryZ2;
	int cube1boundaryZ, cube1boundaryZ2;
	int cube2boundaryZ, cube2boundaryZ2;
	int cube3boundaryZ, cube3boundaryZ2;
	int cubeAmount; 
	int cube0BoundaryY; 
	bool shadowOff; 
	bool alive;
	bool rotatedY; 
	bool rotatedX;

	string myName;

	//***************************
	Ogre::Timer rotate_timer;
	double rotateTick;
	Ogre::Timer move_timer;
	double moveTick;
	Ogre::Timer _timer;
	double tick;
	double tickValue;
	//****************************

	tShapeOpp(Ogre::SceneManager *, string, string); // constructor 
	void Update(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D,int mainTickValue); 
	int cellSize;
	void rotateRight(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	void rotateLeft(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);

	void isDropping(vector<vector<vector<Cube*>>> & array3D);

	int time; 
	int zDirection;
	int xDirection;
	int yDirection; 
	vector<Cube*> cubes;
	enum DirectionFacing {right, left, backwards, forwards} directionFacing;
	void CheckBounds(); 
};
#endif