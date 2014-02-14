#include "zShape.h" 

zShape::zShape(Ogre::SceneManager * mSceneMgr,string mName, string materialName)
{
	 cubeAmount = 4;
	 half = 2;

	 myName = mName;

	 alive = true;
	 shadowOff = false;

	 int cellX = 1;
	 int cellY = 11;
	 int cellZ = 2;
	 cellSize = 4;

	 xDirection = 0;
	zDirection = 0;

	rotateTick = 100;
	moveTick = 80;
	tickValue = 1500.00;
	tick = tickValue;
	

	 cube0boundaryX = 0;
	 cube0boundaryX2 = 2;
	 cube1boundaryX = 1;
	 cube1boundaryX2 = 3;
	 cube2boundaryX = 1;
	 cube2boundaryX2 = 3;
	 cube3boundaryX = 2;
	 cube3boundaryX2 = 4;

	 cube0boundaryZ = 0;
	 cube0boundaryZ2 = 4;
	 cube1boundaryZ = 0;
	 cube1boundaryZ2 = 4;
	 cube2boundaryZ = 0;
	 cube2boundaryZ2 = 4;
	 cube3boundaryZ = 0;
	 cube3boundaryZ2 = 4;


	 directionFacing = right;

	 cubes.resize(cubeAmount);
	for(int i = 0; i< cubeAmount; i++)
	{
		stringstream ss;
		ss << i;
		string entityName =  myName + "zShapeCube" +ss.str();

		string nodeName =  myName + "zShapecubeNode" +ss.str();
		string shadowName =  myName + "zShapeshadow" +ss.str();
		string shadowNodeName =  myName + "zShapeshadowNode" +ss.str();
		string shadowName2 =  myName + "2zShapeshadow" +ss.str();
		string shadowNodeName2 =  myName + "2zShapeshadowNode" +ss.str();
		string shadowName3 =  myName + "3zShapeshadow" +ss.str();
		string shadowNodeName3 =  myName + "3zShapeshadowNode" +ss.str();
		time = 0;

		Ogre::Vector3 tempPos = Ogre::Vector3(cellX*cellSize,cellY *cellSize + 2,cellZ * cellSize);
	
		if(i < 2)
		{
		  cubes[i] = new Cube(mSceneMgr,cellX,cellY,cellZ,entityName,nodeName,shadowName,shadowNodeName,shadowName2,shadowNodeName2,shadowName3,shadowNodeName3,tempPos,materialName);
		  cellX++;
		}
		if(i == 1)
		{
			cellY++;
			cellX--;
		}
		if(i >=2 )
		{
			 cubes[i] = new Cube(mSceneMgr,cellX,cellY,cellZ,entityName,nodeName,shadowName,shadowNodeName,shadowName2,shadowNodeName2,shadowName3,shadowNodeName3,tempPos,materialName);
			 cellX++;
		}

		cubes[i]->setBegin(true);
		cubes[i]->setDrop(true);
		
	}
}

void zShape::Update(double timeChange, OIS::Keyboard* mKeyboard,vector<vector<vector<Cube*>>>  & array3D,int mainTickValue)
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
		

	
	if(rotate_timer.getMilliseconds() >= rotateTick)
	{
		if (mKeyboard->isKeyDown(OIS::KC_D)) // toggle visibility of advanced frame stats
		{
			rotateRight(timeChange,array3D);
		}
		else if (mKeyboard->isKeyDown(OIS::KC_A)) // toggle visibility of advanced frame stats
		{
			rotateLeft(timeChange,array3D);
		}

		rotate_timer.reset();
	}
	

	if(move_timer.getMilliseconds() > moveTick)
	{
		cubes[0]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize, cube0boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
		cubes[1]->Update(timeChange,mKeyboard,array3D,cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
		cubes[2]->Update(timeChange,mKeyboard,array3D, cube2boundaryX * cellSize,cube2boundaryX2 * cellSize,cube2boundaryZ * cellSize,cube2boundaryZ2 * cellSize);
		cubes[3]->Update(timeChange,mKeyboard,array3D, cube3boundaryX * cellSize,cube3boundaryX2 * cellSize,cube3boundaryZ * cellSize,cube3boundaryZ2 * cellSize);
		move_timer.reset();
	}

		if(shadowOff == true)
		{
				for(int i = 0; i < cubeAmount; i++ )
				{
					cubes[0]->Update(timeChange,mKeyboard,array3D,cube0boundaryX * cellSize, cube0boundaryX2 * cellSize,cube0boundaryZ * cellSize,cube0boundaryZ2 * cellSize);
					cubes[1]->Update(timeChange,mKeyboard,array3D,cube1boundaryX * cellSize,cube1boundaryX2 * cellSize,cube1boundaryZ * cellSize,cube1boundaryZ2 * cellSize);
					cubes[2]->Update(timeChange,mKeyboard,array3D, cube2boundaryX * cellSize,cube2boundaryX2 * cellSize,cube2boundaryZ * cellSize,cube2boundaryZ2 * cellSize);
					cubes[3]->Update(timeChange,mKeyboard,array3D, cube3boundaryX * cellSize,cube3boundaryX2 * cellSize,cube3boundaryZ * cellSize,cube3boundaryZ2 * cellSize);
					cubes[i]->turnShadowOffOn();
					alive = false;
				}
		}

}

void zShape::isDropping(vector<vector<vector<Cube*>>> & array3D)
{
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

void zShape::rotateRight(double timeChange,vector<vector<vector<Cube*>>>  & array3D)
{	
				if(directionFacing == right)
				{
					xDirection = 4;
					zDirection = -4;
					directionFacing = backward;
						
				}
				else if(directionFacing == backward)
				{
					xDirection = 4;
					zDirection = 4;
					directionFacing = left;
						
				}
				else if(directionFacing == left)
				{
					xDirection = -4;
					zDirection = 4;
					directionFacing = forward;
						
				}
				else if(directionFacing == forward)
				{
					xDirection = -4;
					zDirection = -4;
					directionFacing = right;

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

				checkBounds();
		
		

}



void zShape::rotateLeft(double timeChange, vector<vector<vector<Cube*>>>  & array3D)
{
			
				if(directionFacing == right)
				{
					xDirection = 4;
					zDirection = 4;
					directionFacing = forward;
						
				}
				else if(directionFacing == backward)
				{
					xDirection = -4;
					zDirection = 4;
					directionFacing = right;
					
				}
				else if(directionFacing == left)
				{
						xDirection = -4;
						zDirection = -4;
						directionFacing = backward;
						
				}
				else if(directionFacing == forward)
				{
					xDirection = 4;
					zDirection = -4;
					directionFacing = left;
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

				checkBounds();
}



void zShape::checkBounds()
{

		if(directionFacing == forward)
			{
				 cube0boundaryX = 0;
				 cube0boundaryX2 = 4;
				 cube1boundaryX = 0;
				 cube1boundaryX2 = 4;
				 cube2boundaryX = 0;
				 cube2boundaryX2 = 4;
				 cube3boundaryX = 0;
				 cube3boundaryX2 = 4;

				 cube0boundaryZ = 2;
				 cube0boundaryZ2 = 4;
				 cube1boundaryZ = 1;
				 cube1boundaryZ2 = 3;
				 cube2boundaryZ = 1;
				 cube2boundaryZ2 = 3;
				 cube3boundaryZ = 0;
				 cube3boundaryZ2 = 2;
			}
			else if(directionFacing == backward)
			{
				 cube0boundaryX = 0;
				 cube0boundaryX2 = 4;
				 cube1boundaryX = 0;
				 cube1boundaryX2 = 4;
				 cube2boundaryX = 0;
				 cube2boundaryX2 = 4;
				 cube3boundaryX = 0;
				 cube3boundaryX2 = 4;

				 cube0boundaryZ = 0;
				 cube0boundaryZ2 = 2;
				 cube1boundaryZ = 1;
				 cube1boundaryZ2 = 3;
				 cube2boundaryZ = 1;
				 cube2boundaryZ2 = 3;
				 cube3boundaryZ = 2;
				 cube3boundaryZ2 = 4;
			}
			else if(directionFacing == right)
			{	
				 cube0boundaryX = 0;
				 cube0boundaryX2 = 2;
				 cube1boundaryX = 1;
				 cube1boundaryX2 = 3;
				 cube2boundaryX = 1;
				 cube2boundaryX2 = 3;
				 cube3boundaryX = 2;
				 cube3boundaryX2 = 4;

				 cube0boundaryZ = 0;
				 cube0boundaryZ2 = 4;
				 cube1boundaryZ = 0;
				 cube1boundaryZ2 = 4;
				 cube2boundaryZ = 0;
				 cube2boundaryZ2 = 4;
				 cube3boundaryZ = 0;
				 cube3boundaryZ2 = 4;
			}
			else if(directionFacing == left)
			{	
				 cube0boundaryX = 2;
				 cube0boundaryX2 = 4;
				 cube1boundaryX = 1;
				 cube1boundaryX2 = 3;
				 cube2boundaryX = 1;
				 cube2boundaryX2 = 3;
				 cube3boundaryX = 0;
				 cube3boundaryX2 = 2;

				 cube0boundaryZ = 0;
				 cube0boundaryZ2 = 4;
				 cube1boundaryZ = 0;
				 cube1boundaryZ2 = 4;
				 cube2boundaryZ = 0;
				 cube2boundaryZ2 = 4;
				 cube3boundaryZ = 0;
				 cube3boundaryZ2 = 4;
			}
}
