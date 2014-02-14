#include "tShape.h" 

tShape::tShape(Ogre::SceneManager * mSceneMgr, string mName, string materialName)
{
	alive = true;
	time = 0;
	myName = mName;
    cubeAmount = 4; 

	
	 for(int i = 0; i < cubeAmount; i++)
	 {

		cubeReadyToDrop[i] = false;

	 }

	cubes.resize(4);
	shadowOff = false; 
	int cellX = 1;
	int cellY = 11;
	int cellZ = 2;
	rotatedX = false;
	rotatedY = false; 
	cellSize = 4;
	xDirection = 4;
	zDirection = -4;
    yDirection = -8;

	cube0boundaryX = 0;
    cube0boundaryX2 = 2;
	cube0boundaryZ = 0;
	cube0boundaryZ2 = 4;

	cube1boundaryX = 1;
	cube1boundaryX2 = 3;
	cube1boundaryZ = 0;
	cube1boundaryZ2 = 4;

	cube2boundaryX = 1;
	cube2boundaryX2 = 3;
	cube2boundaryZ = 0;
	cube2boundaryZ2 = 4;

	cube3boundaryX = 2;
	cube3boundaryX2 = 4;
	cube3boundaryZ = 0;
	cube3boundaryZ2 = 4;

	directionFacing = xAxis;

	rotateTick = 100;
	moveTick = 80;
	tickValue = 1500.00;
	tick = tickValue;

	// Choose a material texture for the cube
	

	for(int i = 0; i< cubeAmount; i++)
	{
		stringstream ss;
		ss << i;

		string entityName = myName + "boxShapeCube" +ss.str();
		string nodeName = myName + "boxShapecubeNode" +ss.str();
		string shadowName = myName + "boxShapeshadow" +ss.str();
		string shadowNodeName = myName + "boxShapeshadowNode" +ss.str();
		//
		string shadowName2 = myName  + "2boxShapeshadow" +ss.str();
		string shadowNodeName2 = myName + "2boxShapeshadowNode" +ss.str();
		
		string shadowName3 = myName + "3boxShapeshadow" +ss.str();
		string shadowNodeName3 = myName + "3boxShapeshadowNode" +ss.str();
	
		Ogre::Vector3 tempPos = Ogre::Vector3(cellX*cellSize,cellY *cellSize + 2,cellZ * cellSize);
		cubes[i] = new Cube(mSceneMgr,cellX,cellY,cellZ,entityName,nodeName,shadowName,shadowNodeName,shadowName2,shadowNodeName2,shadowName3,shadowNodeName3,tempPos, materialName);
		cubes[i]->setBegin(true);
		cubes[i]->setDrop(true);
		cellX++;

		if(i == 1 )
		{
			cellY++;
			cellX--;
		}
		if(i > 1)
		{
			cellY--; 
		}		
	}
}

void tShape::Update(double timeChange, OIS::Keyboard* mKeyboard,vector<vector<vector<Cube*>>>  & array3D,int mainTickValue)
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

	if(rotate_timer.getMilliseconds() > rotateTick)
	{
		if (mKeyboard->isKeyDown(OIS::KC_D)) // toggle visibility of advanced frame stats
		{
			rotateRight(timeChange,mKeyboard, array3D); 
		}

		if(mKeyboard->isKeyDown(OIS::KC_A))
		{
			rotateRight(timeChange,mKeyboard, array3D);
		}
		if (mKeyboard->isKeyDown(OIS::KC_W)) // toggle visibility of advanced frame stats
		{
			rotateY(timeChange,mKeyboard, array3D);  
		}

		if(mKeyboard->isKeyDown(OIS::KC_S))
		{
			rotateY(timeChange,mKeyboard, array3D);
		}
		rotate_timer.reset();
	}

	if(move_timer.getMilliseconds() > moveTick)
	{
		cubes[0]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize, cube0boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
		cubes[1]->Update(timeChange,mKeyboard,array3D,cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
		cubes[2]->Update(timeChange,mKeyboard,array3D, cube2boundaryX * cellSize,cube2boundaryX2 * cellSize,cube2boundaryZ * cellSize,cube2boundaryZ2 * cellSize);
		cubes[3]->Update(timeChange,mKeyboard,array3D,cube3boundaryX * cellSize, cube3boundaryX2 * cellSize,cube3boundaryZ * cellSize,cube3boundaryZ2 * cellSize);
		move_timer.reset();
	}

	if(shadowOff == true) 
	{
		cubes[0]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize, cube0boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
		cubes[1]->Update(timeChange,mKeyboard,array3D,cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
		cubes[2]->Update(timeChange,mKeyboard,array3D, cube2boundaryX * cellSize,cube2boundaryX2 * cellSize,cube2boundaryZ * cellSize,cube2boundaryZ2 * cellSize);
		cubes[3]->Update(timeChange,mKeyboard,array3D,cube3boundaryX * cellSize, cube3boundaryX2 * cellSize,cube3boundaryZ * cellSize,cube3boundaryZ2 * cellSize);
		for(int i = 0; i < cubeAmount; i++ )
	    { 
		   cubes[i]->turnShadowOffOn(); alive = false;  
		}
	}
}

//
//void tShape::checkIfReadyToDrop(vector<vector<vector<Cube*>>> & array3D)
//{
//
//		
//	for(int i = 0; i < cubeAmount; i++)
//	{
//		if(cubes[i]->alive == true)
//		{
//			
//			if(cubes[i]->getGridPosY() != 0)
//			{
//					if(array3D[cubes[i]->getGridPosX()][cubes[i]->getGridPosY()-1][cubes[i]->getGridPosZ()] == 0)
//					{
//
//						cubeReadyToDrop[i] = true;
//					}
//			}
//			else
//			{
//				cubeReadyToDrop[i] = false;
//			}
//		}
//		else
//		{
//			cubeReadyToDrop[i] = true;
//		}
//	}
//
//
//					
//		if(cubeReadyToDrop[0] == true && cubeReadyToDrop[1] == true && cubeReadyToDrop[2] == true && cubeReadyToDrop[3] == true)
//		{
//			for(int i = 0; i < cubeAmount; i++)
//			{
//				if(cubes[i]->alive == true)
//				{
//						cubes[i]->setDrop(true);
//						cubes[i]->setDropped(false);
//				}
//
//			}
//		}
//		else if(cubeReadyToDrop[0] == true && cubeReadyToDrop[1] == true && cubeReadyToDrop[3] == true)
//		{
//			for(int i = 0; i < cubeAmount; i++)
//			{
//
//				if(cubes[i]->alive == true)
//				{
//					if(cubes[i]->gridPosY != 0)
//					{
//						cubes[i]->setDrop(true);
//						cubes[i]->setDropped(false);
//					}
//				}
//
//			}
//		}
//
//}


void tShape::isDropping(vector<vector<vector<Cube*>>> & array3D)
{

	

	//for(int i = 0; i < cubeAmount; i++ )
	//{
	//		if(cubes[i]->alive == true)
	//		{
	//			if(cubes[i]->dropped == true)
	//			{
	//					for(int i = 0; i < cubeAmount; i++ )
	//					{
	//						cubes[i]->setMove(false);
	//						cubes[i]->setDrop(false);
	//						cubes[i]->setDropped(true);	
	//					}
	//			}
	//		 }
	//		
	//}

	//
/*

		for(int i = 0; i < cubeAmount; i++ )
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
		}
*/


		for(int i = 0; i < cubeAmount; i++ )
		{
			if(cubes[i] ->alive == true)
			{
				cubes[i]->droppingCube(array3D);
			}
			else if(cubes[i] ->alive == false)
			{

				if(cubes[i]->flipVisibility == false)
				{
					cubes[i]->targetNode->flipVisibility();
					cubes[i]->flipVisibility = true;
				}
			}
		}



		

}

void tShape::rotateY(double timeChange, OIS::Keyboard* mKeyboard,vector<vector<vector<Cube*>>>  & array3D)
{
			Ogre::Vector3 newPos =   Ogre::Vector3(cubes[2]->m_position.x ,cubes[2]->m_position.y + yDirection,cubes[2]->m_position.z);
			cubes[2]->setPosition(newPos);
			cubes[2]->targetNode->setPosition(newPos);
			cubes[2]->gridPosY = cubes[2]->gridPosY + (yDirection/4);
			yDirection = -yDirection;

		
	
}


void tShape::rotateRight(double timeChange, OIS::Keyboard* mKeyboard,vector<vector<vector<Cube*>>>  & array3D)
{
	
			if(  directionFacing == xAxis)
			{
					xDirection = 4;
					zDirection = -4; 
					directionFacing = zAxis; 
					
			} 

			else if( directionFacing == zAxis)
			{ 
					xDirection = -4;
					zDirection = 4; 
					directionFacing = xAxis;
					

			} 

		Ogre::Vector3 newPos =   Ogre::Vector3(cubes[0]->m_position.x + xDirection,cubes[0]->m_position.y ,cubes[0]->m_position.z +  zDirection);
			cubes[0]->setPosition(newPos);
			cubes[0]->targetNode->setPosition(newPos);
			cubes[0]->gridPosX = cubes[0]->gridPosX + (xDirection/4);
			cubes[0]->gridPosZ = cubes[0]->gridPosZ + (zDirection/4);

			xDirection = -xDirection;
			zDirection = -zDirection;

			Ogre::Vector3 newPos2 =   Ogre::Vector3(cubes[3]->m_position.x + xDirection,cubes[3]->m_position.y ,cubes[3]->m_position.z + zDirection);
			cubes[3]->setPosition(newPos2);
			cubes[3]->targetNode->setPosition(newPos2);
			cubes[3]->gridPosX = cubes[3]->gridPosX + (xDirection/4);
			cubes[3]->gridPosZ = cubes[3]->gridPosZ + (zDirection/4);

			if( directionFacing == zAxis)
			{
				 cube0boundaryX = 0;
				 cube0boundaryX2 = 4;
				 cube0boundaryZ = 0;
				 cube0boundaryZ2 = 2;

				 cube1boundaryX = 0;
				 cube1boundaryX2 = 4;
				 cube1boundaryZ = 1;
				 cube1boundaryZ2 = 3;

				 cube2boundaryX = 0;
				 cube2boundaryX2 = 4;
				 cube2boundaryZ = 1;
				 cube2boundaryZ2 = 3;

				 cube3boundaryX = 0;
				 cube3boundaryX2 = 4;
				 cube3boundaryZ = 2;
				 cube3boundaryZ2 = 4;
			}
	
			else if(directionFacing == xAxis)
			{	
				 cube0boundaryX = 0;
				 cube0boundaryX2 = 2;
				 cube0boundaryZ = 0;
				 cube0boundaryZ2 = 4;

				 cube1boundaryX = 1;
				 cube1boundaryX2 = 3;
				 cube1boundaryZ = 0;
				 cube1boundaryZ2 = 4;

				 cube2boundaryX = 1;
				 cube2boundaryX2 = 3;
				 cube2boundaryZ = 0;
				 cube2boundaryZ2 = 4;

				 cube3boundaryX = 2;
				 cube3boundaryX2 = 4;
				 cube3boundaryZ = 0;
				 cube3boundaryZ2 = 4;
			}
}

