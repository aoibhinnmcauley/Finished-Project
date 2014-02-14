#ifndef __tShape_h_
#define __tShape_h_

#include "Ogre.h" 
#include <cstdio>
#include "BaseApplication.h"
#include <ctime>
#include "Cube.h"


class tShape
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
	/*! stores m_postion.X */
	int cellX;
	/*! stores m_postion.Y */
	int cellY;
	/*! stores m_postion.Z */
	int cellZ;
    /*! keeps the cube at postion 0 inside the matrix */
	int cube0boundaryZ, cube0boundaryZ2;
	/*! keeps the cube at postion 1 inside the matrix */
	int cube1boundaryZ, cube1boundaryZ2;
	/*! keeps the cube at postion 2 inside the matrix */
	int cube2boundaryZ, cube2boundaryZ2;
	/*! keeps the cube at postion 3 inside the matrix */
	int cube3boundaryZ, cube3boundaryZ2;
	/*! the amouunt of cubes in the array */
	int cubeAmount; 
	/*! keeps the cube at postion 0 inside the matrix */
	int cube0BoundaryY; 
	/*! checks if  shadow is on */
	bool shadowOff; 
	/*! tracks if alive or not */
	bool alive;
	/*! rotateY */
	bool rotatedY; 
	/*! rotateX */
	bool rotatedX;
	/*! shape name */
	string myName;
	/*!oger timer */
	Ogre::Timer rotate_timer;
	/*! stores rotate tick */
	double rotateTick;
	/*! oger timer */
	Ogre::Timer move_timer;
	/*! stores move tick */
	double moveTick;
	/*! oger timer */
	Ogre::Timer _timer;
	/*! stores the tick */
	double tick;
	/*! stores the tick value  */
	double tickValue;
	/*! constructor */
	tShape(Ogre::SceneManager *, string, string);
	/*! update method */
	void Update(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D,int mainTickValue); 
	/*! stores the size of a matrix cell */
	int cellSize;
	/*! rotates the shape method */
	void rotateRight(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	/*! rotates the shape method */
	void rotateY(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D);
	/*! makes the cube drop method */
	void isDropping(vector<vector<vector<Cube*>>> & array3D);
	/*! tracks if cube readyto drop */
	bool cubeReadyToDrop[4];

	/*! stroes the time value  */
	int time; 
	/*! stroes the zDirection value  */
	int zDirection;
	/*! stroes the xDirection value */
	int xDirection;
	/*! stroes the yDirection value */
	int yDirection; 
	/*! array of cube objects */
	vector<Cube*> cubes;
	/*! keepstrack of the shapes orientation */
	enum DirectionFacing {xAxis, zAxis} directionFacing;



};
#endif