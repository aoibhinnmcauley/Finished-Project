#ifndef __lShape_h_
#define __lShape_h_

#include "Ogre.h" 
#include <cstdio>
#include "BaseApplication.h"
#include <ctime>
#include "Cube.h"


class lShape
{
	public:
	/*! keeps the cube at postion 0 inside the matrix */
	int cube0boundaryX, cube0boundaryX2;
	/*! keeps the cube at postion 1 inside the matrix */
	int cube1boundaryX, cube1boundaryX2;
	/*! keeps the cube at postion 2 inside the matrix */
	int cube2boundaryX, cube2boundaryX2;
	/*! keeps the cube at postion 3 inside the matrix */
	int cube3boundaryX, cube3boundaryX2;
	/*! tracks m_postion.X */
	int cellX;
	/*! tracks m_postion.Y */
	int cellY;
	/*! tracks m_postion.Z */
	int cellZ;
	/*! keeps the cube at postion 0 inside the matrix */
	int cube0boundaryZ, cube0boundaryZ2;
	/*! keeps the cube at postion 1 inside the matrix */
	int cube1boundaryZ, cube1boundaryZ2;
	/*! keeps the cube at postion 2 inside the matrix */
	int cube2boundaryZ, cube2boundaryZ2;
	/*! keeps the cube at postion 3 inside the matrix */
	int cube3boundaryZ, cube3boundaryZ2;
	/*! amount of cubes in the Array */
	int cubeAmount; 
	/*! keeps the cube at postion 0 inside the matrix */
	int cube0BoundaryY; 
	/*! stoes if the shapes shadow is on or not */
	bool shadowOff; 
	/*! stores if the shape is alive or not */
	bool alive;
	/*! rotatedXYbool */
	bool rotatedY;
	/*! rotatedX bool */
	bool rotatedX;
	/*! shapes name */
	string myName;
	/*! oger timer */
	Ogre::Timer rotate_timer;
	/*! stores tick per rotation */
	double rotateTick;
	/*! oger timer  */
	Ogre::Timer move_timer;
	/*! stores move tick */
	double moveTick;
	/*! ogre timer */
	Ogre::Timer _timer;
	/*! stores tick */
	double tick;
	/*! keeps track of the tick value */
	double tickValue;
	/*!  constructor  */
	lShape(Ogre::SceneManager *, string, string); 
	/*! update method */
	void Update(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D,int mainTickValue); 
	/*! stores the size of a cell in the matrix */
	int cellSize;
	/*! rotates the shape right */
	void rotateRight(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	/*! rotates the shape left */
	void rotateLeft(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	/*! rotates the shape along the yAxis */
	void rotateY(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	/*! rotates the shape along the yAxis */
	void rotateYOpp(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	/*! checks if the shape is dropping method */
	void isDropping(vector<vector<vector<Cube*>>> & array3D);
	/*! keeps track of the time */
	int time;
	/*! stores the zDirection */
	int zDirection;
	/*! stores the xDirection */
	int xDirection;
	/*! stores yDirection */
	int yDirection; 
	/*! array of cube objects */
	vector<Cube*> cubes;
	/*! keeps track of the oriation of the shap */
	enum DirectionFacing {right, left, backwards, forwards} directionFacing;
	/*! keeps the shapes inside the matrix method */
	void CheckBounds(); 
};
#endif