#ifndef __zShape_h_
#define __zShape_h_

#include "Ogre.h" 
#include <cstdio>
#include "BaseApplication.h"
#include <ctime>
#include "Cube.h"


class zShape
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
	  /*! keeps the cube at postion 0 inside the matrix */
	int cube0boundaryZ, cube0boundaryZ2;
	  /*! keeps the cube at postion 1 inside the matrix */
	int cube1boundaryZ, cube1boundaryZ2;
	  /*! keeps the cube at postion 2 inside the matrix */
	int cube2boundaryZ, cube2boundaryZ2;
	  /*! keeps the cube at postion 3 inside the matrix */
	int cube3boundaryZ, cube3boundaryZ2;
	  /*! shapes name */
	string myName;
	  /*! ogre timer */
	Ogre::Timer rotate_timer;
	  /*! tracks the tick */
	double rotateTick;
	  /*! ogre timer */
	Ogre::Timer move_timer;
	  /*! tracks the tick */
	double moveTick;
	  /*! ogre timer  */
	Ogre::Timer _timer;
	  /*! tracks the tick  */
	double tick;
	  /*! tracks the tick value */
	double tickValue;
	  /*! tracks the orientation of the shape */
	enum DirectionFacing {forward, backward, left, right} directionFacing;
   /*! constructor method */
	zShape(Ogre::SceneManager *,string mName, string); // constructor 
	  /*! update method */
	void Update(double,OIS::Keyboard*,vector<vector<vector<Cube*>>> & array3D,int mainTickValue);
	/*!size of a cell in the matrix */
	int cellSize;
	  /*! rotate right method */
	void rotateRight(double,vector<vector<vector<Cube*>>> & array3D);
	  /*! rotate left method */
	void rotateLeft(double,vector<vector<vector<Cube*>>> & array3D);
	  /*! tracks if the cube is dropping method */
	void isDropping(vector<vector<vector<Cube*>>> & array3D);
	  /*! keeps the cube in side the matrix method */
	void checkBounds();
	  /*! tracks trime */
	int time; 
	  /*! stores xDirection */
	int zDirection;
	  /*! stores xDirection */
	int xDirection;
	  /*!  tracks if the cube is alive or not */
	bool alive;
	  /*! tracks if the shadow is on or off */
	bool shadowOff;
	  /*! amount of cubes in the array */
	int cubeAmount;
	  /*! store half*/
	int half;
	 /*! array of cube objects */
	vector<Cube*> cubes;

};
#endif