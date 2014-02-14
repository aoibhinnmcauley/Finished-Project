#include "box.h" 

box::box(Ogre::SceneManager * mSceneMgr, string mName, string materialName)
{
	alive = true;

	myName = mName;
	 cubeAmount = 8;
	 cubes.resize(cubeAmount);

	 int cellX = 1;
	 int cellY = 12;
	 int cellZ = 2;

	rotateTick = 100;
	moveTick = 80;
	tickValue = 1500.00;
	tick = tickValue;

	 shadowOff = false;
	

	 cellSize = 4;

	 xDirection = 4;
	 zDirection = -4;

	 cube0boundaryX = 0;
	 cube0boundaryX2 = 3;
	 cube0BoundaryY = 1;

	 cube1boundaryX = 1;
	 cube1boundaryX2 = 4;

	 cube2boundaryX = 1;
	 cube2boundaryX2 = 4;

	 cube0boundaryZ = 1;
	 cube0boundaryZ2 = 4;

	 cube1boundaryZ = 0;
	 cube1boundaryZ2 = 3;

	 cube2boundaryZ = 0;
	 cube2boundaryZ2 = 4;

	 orientation = xAlligned;

	// Choose a material texture for the cube
	

	for(int i = 0; i< cubeAmount; i++)
	{
		stringstream ss;
		ss << i;

		string entityName = myName + "boxShapeCube" +ss.str();

		string nodeName = myName + "boxShapecubeNode" +ss.str();
		string shadowName = myName + "boxShapeshadow" +ss.str();
		string shadowNodeName = myName + "boxShapeshadowNode" +ss.str();
		string shadowName2 = myName  + "2boxShapeshadow" +ss.str();
		string shadowNodeName2 = myName + "2boxShapeshadowNode" +ss.str();
		string shadowName3 = myName + "3boxShapeshadow" +ss.str();
		string shadowNodeName3 = myName + "3boxShapeshadowNode" +ss.str();


		
	
		Ogre::Vector3 tempPos = Ogre::Vector3(cellX*cellSize,cellY *cellSize + 2,cellZ * cellSize);
		cubes[i] = new Cube(mSceneMgr,cellX,cellY,cellZ,entityName,nodeName,shadowName,shadowNodeName,shadowName2,shadowNodeName2,shadowName3,shadowNodeName3,tempPos, materialName);
		cubes[i]->setBegin(true);
		cubes[i]->setDrop(true);
		cellX++;

		if(i == 0 )
		{
			cellY--;
			cellX--;
		}
		if(i == 2 )
		{
			cellY++;
			cellX--;
	
		}
		if(i == 3)
		{ 
			cellZ--;
			cellX = 1;

		}
		if(i == 5)
		{
			cellY--;
			cellX = 1;
		}
		
	}
}

void box::Update(double timeChange, OIS::Keyboard* mKeyboard,vector<vector<vector<Cube*>>>  & array3D, int mainTickValue)
{
		tickValue = mainTickValue;
		if(alive == true)
		{
			if(_timer.getMilliseconds() > tick)
			{
				for(int i = 0; i < cubeAmount; i++ )
				{
					cubes[i]->droppingCube(array3D);
					
				}
				_timer.reset();
			}
			for(int i = 0; i < cubeAmount; i++ )
			{
				cubes[i]->moveShadow(array3D);
			}
			for(int i = 0; i < cubeAmount; i++ )
			{
				if(cubes[i]->dropped == true)
				{
					for(int i = 0; i < cubeAmount; i++ )
					{
						cubes[i]->setMove(false);
						cubes[i]->setDrop(false);
						cubes[i]->setDropped(true);
						shadowOff = true;
					}
				}

			}
			if(alive == true)
			{
				if (mKeyboard->isKeyDown(OIS::KC_SPACE))   // toggle visibility of advanced frame stats
				{
					for(int i = 0; i < cubeAmount; i++ )
					{ 
						tick =  40;
					}
				}
				else
				{
					for(int i = 0; i < cubeAmount; i++ )
					{ 
						tick =  tickValue;
					}

				}
			}
		

		if(move_timer.getMilliseconds() > moveTick)
		{

			cubes[0]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize, cube0boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
			cubes[1]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize,cube0boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
			cubes[2]->Update(timeChange,mKeyboard,array3D, cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
			cubes[3]->Update(timeChange,mKeyboard,array3D,cube1boundaryX * cellSize, cube1boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
			cubes[4]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize,cube0boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
			cubes[5]->Update(timeChange,mKeyboard,array3D, cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
			cubes[6]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize, cube0boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
			cubes[7]->Update(timeChange,mKeyboard,array3D,cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
			move_timer.reset();
		}	
			if(shadowOff == true)
			{
					for(int i = 0; i < cubeAmount; i++ )
					{
						cubes[i]->turnShadowOffOn();
						alive = false;
					}
			}
		}
	

}

void box::isDropping(vector<vector<vector<Cube*>>> & array3D)
{

		/*for(int i = 0; i < cubeAmount; i++ )
		{
			if(cubes[i]->alive == true)
			{
				if(cubes[i]->dropped == true)
				{
						for(int i = 0; i < cubeAmount; i++ )
						{
							cubes[i]->setMove(false);
							cubes[i]->setDrop(false);
							cubes[i]->setDropped(true);	
						}
				}
			}
			
		}*/


	/*	for(int i = 0; i < cubeAmount; i++ )
		{
			if(cubes[i]->alive == true)
			{
				if(cubes[i]->dropped == true)
				{
				
						array3D[cubes[i]->getGridPosX()][cubes[i]->getGridPosY()][cubes[i]->getGridPosZ()] = cubes[i];
				

				}
				else if(cubes[i]->dropped == false)
				{
						array3D[cubes[i]->getGridPosX()][cubes[i]->getGridPosY()][cubes[i]->getGridPosZ()] = 0;
				}
			}
		}*/

		for(int i = 0; i < cubeAmount; i++ )
		{
			if(cubes[i] ->alive == true)
			{
				cubes[i]->droppingCube(array3D);
			}
			else if(cubes[i]->alive == false)
			{

				if(cubes[i]->flipVisibility == false)
				{
					cubes[i]->targetNode->flipVisibility();
					cubes[i]->flipVisibility = true;
				}
			}
		}

}





