#include "Cube.h" 

Cube::Cube(Ogre::SceneManager * mSceneMgr,int newgridPosX, int newgridPosY,int newgridPosZ, string myEntityName, string myNodeName,string myEntityName2, string myNodeName2,
			string myEntityName3,string myNodeName3,string shadowName3,string shadowNodeName3,Ogre::Vector3 tempPosition, string materialName)
{
	
	 // The scene node for the model
	setMove(true); // Or to true if you want the sphere to move now
	// fix the radius the same as the model
	 // fix velocity
	// fix position
	flipVisibility = false;
	dropped = false;
	entityName = myEntityName;
	nodeName = myNodeName;
	entityName2 = myEntityName2;
	nodeName2 = myNodeName2;
	entityName3 = myEntityName3;
	nodeName3 = myNodeName3;
	
	clock = std::clock();
	m_timer = 1;
	tick = 1;
	dropTimer = 1;
	moveLeft = Ogre::Vector3(-4, 0, 0); 
	moveRight = Ogre::Vector3(4, 0, 0); 
	moveForward = Ogre::Vector3(0,0,-4);
	moveBackward = Ogre::Vector3(0,0,4);
	moveDown = Ogre::Vector3(0,-4,0);
	gridPosX = newgridPosX;
	gridPosZ = newgridPosZ;
	gridPosY = newgridPosY;

	mergeArray = false;
	
	targetCube = mSceneMgr->createEntity(entityName, "cube.mesh");
	// Choose a material texture for the cube
	targetCube->setMaterialName(materialName);
	// Create a new sceneNode for the cube, attach it to the rootSceneNode 
	//as a child of the scene manager
	targetNode = mSceneMgr->createSceneNode(nodeName);
	mSceneMgr->getRootSceneNode()->addChild(targetNode);
	targetNode->attachObject( targetCube );
	targetCube->setCastShadows(true);
	float cubeModelLength = 100;
	float cubeLength = 4;
	// Change size of graphics cube to that of cubeLength
	double cubeScale = cubeLength/cubeModelLength;
	targetNode->scale(cubeScale, cubeScale, cubeScale);
	m_lenth = cubeLength/2;
	m_position = tempPosition; 
	// Position the cube to sit exactly on the ground
	targetNode-> setPosition(Ogre::Vector3(m_position));
	alive = true;
	checked = false;
	finishedDrop = false;
	begin = false;

	shadowPlane.normal = Ogre::Vector3::UNIT_Y;
    // horizontal plane with normal up in X-direction
   	shadowPlane.d = +5;//Plane passes through the origin i.e. plane at y = 0
    //gridX.projectVector(Ogre::Vector3(100,100,100));
	Ogre::MeshManager::getSingleton().createPlane("shadowPlane",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, shadowPlane, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);
   	shadow = mSceneMgr->createEntity(entityName2, "shadowPlane");
    shadow->setMaterialName("Examples/MRAMOR-shadow");
    shadow->setCastShadows(false);
    shadowNode = mSceneMgr->createSceneNode(nodeName2);
	mSceneMgr->getRootSceneNode()->addChild(shadowNode);
	shadowNode->attachObject(shadow);
	shadowNode->scale(0.42,0.42,0.42);
	shadowNode->setPosition(8,30,8);

	
	
   	shadowPlane2.normal = Ogre::Vector3::UNIT_X;
    // horizontal plane with normal up in X-direction
   	shadowPlane2.d = +5;//Plane passes through the origin i.e. plane at y = 0
    //gridX.projectVector(Ogre::Vector3(100,100,100));
	Ogre::MeshManager::getSingleton().createPlane("shadowPlane2",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, shadowPlane2, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);
   	shadow2 = mSceneMgr->createEntity(entityName3, "shadowPlane2");
    shadow2->setMaterialName("Examples/MRAMOR-shadow");
    shadow2->setCastShadows(false);
    shadowNode2 = mSceneMgr->createSceneNode(nodeName3);
	mSceneMgr->getRootSceneNode()->addChild(shadowNode2);
	shadowNode2->attachObject(shadow2);
	shadowNode2->scale(0.42,0.42,0.42);

	shadowPlane3.normal = Ogre::Vector3::UNIT_Z;
    // horizontal plane with normal up in X-direction
   	shadowPlane3.d = +5;//Plane passes through the origin i.e. plane at y = 0
    //gridX.projectVector(Ogre::Vector3(100,100,100));
	Ogre::MeshManager::getSingleton().createPlane("shadowPlane3",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, shadowPlane3, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_X);
   	shadow3 = mSceneMgr->createEntity(shadowName3, "shadowPlane3");
    shadow3->setMaterialName("Examples/MRAMOR-shadow");
    shadow3->setCastShadows(false);
    shadowNode3 = mSceneMgr->createSceneNode(shadowNodeName3);
	mSceneMgr->getRootSceneNode()->addChild(shadowNode3);
	shadowNode3->attachObject(shadow3);
	shadowNode3->scale(0.42,0.42,0.42);
	


	targetNode->flipVisibility();
	shadowNode->flipVisibility();
	shadowNode2->flipVisibility();
	shadowNode3->flipVisibility();
}

Cube::~Cube(void)
{
}
//Ogre::Vector3 getPosition();// returns m_position
Ogre::Vector3 Cube::getPosition()
{
			return m_position;
}

//Ogre::Vector3 getVelocity();//returns m_velocity
Ogre::Vector3 Cube::getVelocity()
{
			return m_velocity;
}
//Ogre::SceneNode* getNode();//returns SceneNode pointer
Ogre::SceneNode* Cube::getNode()
{
			    return m_objectNode; 
}
 //double getLenth();  // returns m_lenth
double Cube::getLenth()
{
			return m_lenth;
}

int Cube::getGridPosX()
{
			return gridPosX;
}
int Cube::getGridPosY()
{
			return gridPosY;
}
int Cube::getGridPosZ()
{
			return gridPosZ;
}
void Cube::turnShadowOffOn()
{
	shadowNode->flipVisibility();
	shadowNode2->flipVisibility();
	shadowNode3->flipVisibility();

}

//bool getMove();  // returns m_move
bool Cube::getMove()
{
			return m_move;
}

int Cube::getTime()
{
	return m_timer;
}

//void setPosition(Ogre::Vector3);// sets m_position
void Cube::setPosition(Ogre::Vector3 myPosition)
{
		m_position = myPosition; 
}
//void setVelocity(Ogre::Vector3);//sets m_velocity
void Cube::setVelocity(Ogre::Vector3 myVelocity)
{
		m_velocity = myVelocity;
}

//void setMove(bool);  // sets m_move
void Cube::setMove(bool myBool)
{
	m_move = myBool; 
}
void Cube::setDropped(bool myBool)
{
	dropped = myBool; 

}
void Cube::setChecked(bool myBool)
{
	checked = myBool; 

}
void Cube::setAlive(bool myBool)
{
	alive = myBool; 
}
void Cube::setDrop(bool myBool)
{
	drop = myBool; 
}
void Cube::setBegin(bool myBool)
{
	begin = myBool;
	targetNode->flipVisibility();
	turnShadowOffOn();
}


void Cube::setTime(int myTime){
  m_timer  = myTime;
}



void Cube::instantDrop(vector<vector<vector<Cube*>>>  & array3D)
{
	int yCell = 0;

	if(array3D[getGridPosX()][10][getGridPosZ()] == 0)
	{
		for(int i = 0;array3D[getGridPosX()][i][getGridPosZ()] != 0; i++)
		{	
		
			yCell++;
		}
	}


	gridPosY = yCell;
	m_position.y = 2 + yCell * 4;
	targetNode->setPosition(m_position);
	dropped = true;
	drop = false;
	m_move = false;



}

void Cube::moveShadow(vector<vector<vector<Cube*>>>  & array3D)
{
	int yCell = 0;

	if(array3D[getGridPosX()][10][getGridPosZ()] == 0)
	{
		for(int i = 0;i < 10; i++)
		{	
		
			if(array3D[getGridPosX()][i][getGridPosZ()] != 0)
			{
			  yCell = i + 1;
			}

		}
	}

	
	//shadowNode->setPosition(Ogre::Vector3(m_position.x,0.1,m_position.z)); 
	
	m_shadowPos.y = 2.3 + yCell * 4;
	m_shadowPos2.x = 0.2;
	m_shadowPos3.z = 0.2;

	shadowNode->setPosition(Ogre::Vector3(m_position.x,m_shadowPos.y,m_position.z));
	shadowNode2->setPosition(Ogre::Vector3(m_shadowPos2.x,m_position.y,m_position.z));
	shadowNode3->setPosition(Ogre::Vector3(m_position.x,m_position.y,m_shadowPos3.z));


}

//Update method
void Cube::Update(double timeChange, OIS::Keyboard* mKeyboard, vector<vector<vector<Cube*>>>  & array3D, int boundaryX, int boundaryX2,int boundaryZ, int boundaryZ2)
{
	//Ogre::Vector3 m_NextPostion;
	//Ogre::Vector3  accel = Ogre::Vector3(0, 9.81, 0);
	//if(dropped == true)
	//array3D[getGridPosX()][getGridPosY()][getGridPosZ()] = this;
	
    //m_timer = (std::clock() - clock ) / (double) CLOCKS_PER_SEC;
	
	//m_timer = m_timer + 1;
	
	


	if(m_move == true)
	{
	
		if (mKeyboard->isKeyDown(OIS::KC_LEFT))
		{		
			//if(m_timer >= 40)
			//{
				if(m_position.x > boundaryX)
				{
					if(array3D[getGridPosX() - 1][getGridPosY()][getGridPosZ()] == 0)
					{
						m_position = m_position + moveLeft;
						targetNode->setPosition(m_position);
						gridPosX = gridPosX - 1;
						m_timer = 0;

					}
				}
			//}
		}
		else if(mKeyboard->isKeyDown(OIS::KC_RIGHT))
		{
			//if(m_timer >= 40)
			//{
				if(m_position.x < boundaryX2)
				{
					if(array3D[getGridPosX() + 1][getGridPosY()][getGridPosZ()] == 0)
					{
						m_position = m_position + moveRight;
						targetNode->setPosition(m_position);
						gridPosX = gridPosX + 1;
						m_timer = 0;
					}
				}
			//}
		}

		if (mKeyboard->isKeyDown(OIS::KC_UP))
		{		
			//if(m_timer >= 40)
		//{
				if(m_position.z > boundaryZ)
				{
					if(array3D[getGridPosX()][getGridPosY()][getGridPosZ() - 1] == 0)
					{
						m_position = m_position + moveForward;
						targetNode->setPosition(m_position);
						gridPosZ = gridPosZ - 1;
						m_timer = 0;
					}
				}
			//}
		}
		else if(mKeyboard->isKeyDown(OIS::KC_DOWN))
		{
			//if(m_timer >= 40)
			//{
				if(m_position.z < boundaryZ2)
				{
					if(array3D[getGridPosX()][getGridPosY()][getGridPosZ() + 1] == 0)
					{
						m_position = m_position + moveBackward;
						targetNode->setPosition(m_position);
						gridPosZ = gridPosZ + 1;
						m_timer = 0;
					}
				}
			//}
		}
		
		
	}
	
	
}
void Cube::droppingCube(vector<vector<vector<Cube*>>>  & array3D)
{
	if(dropped == true)
	{
		if(mergeArray = true)
		{
			array3D[gridPosX][gridPosY][gridPosZ] = this;
			mergeArray = false;
		}
	}

	//dropTimer = dropTimer + tick;

	if(begin == true)
	{
		if(finishedDrop == false)
		{
			if(drop == true)
			{
		
				if(alive == true)
				{
					//if(BaseApplication._timer.getMilliseconds() > 1000)
					//{
						m_position = m_position + moveDown;

						targetNode->setPosition(m_position);
						gridPosY = gridPosY - 1;
				
					//	BaseApplication._timer.reset();
					//}

					if(getGridPosY() != 0)
					{
						if(array3D[getGridPosX()][getGridPosY()-1][getGridPosZ()] != 0)
						{
							m_move = false; 
							dropped = true;
							drop = false;
							mergeArray = true;
							finishedDrop = true;
						}
						
					}
					else if(getGridPosY() == 0)
					{

						m_move = false; 
						dropped = true;
						drop = false;
						mergeArray = true;
						finishedDrop = true;

					}
				}

			}
		}
	}
}


