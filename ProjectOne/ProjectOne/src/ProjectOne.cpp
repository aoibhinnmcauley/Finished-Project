/*
-----------------------------------------------------------------------------
Filename:    ProjectOne.cpp
-----------------------------------------------------------------------------


This source file is generated by the
   ___                   _              __    __ _                  _ 
  /___\__ _ _ __ ___    /_\  _ __  _ __/ / /\ \ (_)______ _ _ __ __| |
 //  // _` | '__/ _ \  //_\\| '_ \| '_ \ \/  \/ / |_  / _` | '__/ _` |
/ \_// (_| | | |  __/ /  _  \ |_) | |_) \  /\  /| |/ / (_| | | | (_| |
\___/ \__, |_|  \___| \_/ \_/ .__/| .__/ \/  \/ |_/___\__,_|_|  \__,_|
      |___/                 |_|   |_|                                 
      Ogre 1.7.x Application Wizard for VC10 (July 2011)
      http://code.google.com/p/ogreappwizards/
-----------------------------------------------------------------------------
*/

#include "ProjectOne.h"



//-------------------------------------------------------------------------------------
ProjectOne::ProjectOne(void)
{
}
//-------------------------------------------------------------------------------------
ProjectOne::~ProjectOne(void)
{
}

//-------------------------------------------------------------------------------------
void ProjectOne::createScene(void)
{
    // Create the ground with grass on it

	mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox", 1000.0f);
   	Ogre::Plane plane;

   	plane.normal = Ogre::Vector3::UNIT_Y;

    // horizontal plane with normal up in y-direction
   	plane.d = 0;//Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("floor",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
            30,30,10,10,true,1,10,10,Ogre::Vector3::UNIT_Z);
   	Ogre::Entity* pPlaneEnt = mSceneMgr->createEntity("plane", "floor");
    pPlaneEnt->setMaterialName("Examples/Dirt");
    pPlaneEnt->setCastShadows(false);
    Ogre::SceneNode* floorNode = mSceneMgr->createSceneNode("floor1");
	mSceneMgr->getRootSceneNode()->addChild(floorNode);
	floorNode->attachObject(pPlaneEnt);
	floorNode->setPosition(8,0,8);

	 //Create plane for grid 
   	Ogre::Plane grid;

   	grid.normal = Ogre::Vector3::UNIT_Y;

    // horizontal plane with normal up in y-direction
   	grid.d = -0.10;//Plane passes through the origin i.e. plane at y = 0

	Ogre::MeshManager::getSingleton().createPlane("grid",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, grid, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);
   	Ogre::Entity* pGridEnt = mSceneMgr->createEntity("grid", "grid");
    pGridEnt->setMaterialName("Examples/MRAMOR-bump2");
    pGridEnt->setCastShadows(false);
    Ogre::SceneNode* gridNode = mSceneMgr->createSceneNode("grid1");
	mSceneMgr->getRootSceneNode()->addChild(gridNode);
	gridNode->attachObject(pGridEnt);
	gridNode->scale(2,2,2);
	gridNode->setPosition(8,-0.10,8);


	  	Ogre::Plane gridX;
   	gridX.normal = Ogre::Vector3::UNIT_X;
    // horizontal plane with normal up in X-direction
   	gridX.d = +5;//Plane passes through the origin i.e. plane at y = 0
    //gridX.projectVector(Ogre::Vector3(100,100,100));
	Ogre::MeshManager::getSingleton().createPlane("gridX",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, gridX, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);
   	Ogre::Entity* pGridXEnt = mSceneMgr->createEntity("gridX", "gridX");
    pGridXEnt->setMaterialName("Examples/MRAMOR-bump2");
    pGridXEnt->setCastShadows(false);
    Ogre::SceneNode* gridXNode = mSceneMgr->createSceneNode("gridX");
	mSceneMgr->getRootSceneNode()->addChild(gridXNode);
	gridXNode->attachObject(pGridXEnt);
	gridXNode->scale(2,2,2);
	gridXNode->setPosition(8,10,8);



	Ogre::Plane gridX2;
   	gridX2.normal = Ogre::Vector3::UNIT_X;
    // horizontal plane with normal up in X-direction
   	gridX2.d = +5;//Plane passes through the origin i.e. plane at y = 0
    //gridX.projectVector(Ogre::Vector3(100,100,100));
	Ogre::MeshManager::getSingleton().createPlane("gridX2",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, gridX2, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_Z);
   	Ogre::Entity* pGridXEnt2 = mSceneMgr->createEntity("gridX2", "gridX2");
    pGridXEnt2->setMaterialName("Examples/MRAMOR-bump2");
    pGridXEnt2->setCastShadows(false);
    Ogre::SceneNode* gridXNode2 = mSceneMgr->createSceneNode("gridX2");
	mSceneMgr->getRootSceneNode()->addChild(gridXNode2);
	gridXNode2->attachObject(pGridXEnt2);
	gridXNode2->scale(2,2,2);
	gridXNode2->setPosition(8,30,8);

		// Create plane for grid 
   	Ogre::Plane gridZ;
   	gridZ.normal = Ogre::Vector3::UNIT_Z ;
    // horizontal plane with normal up in X-direction
   	gridZ.d;//Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("gridZ",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, gridZ, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_X);
   	Ogre::Entity* pGridZEnt = mSceneMgr->createEntity("gridZ", "gridZ");
    pGridZEnt->setMaterialName("Examples/MRAMOR-bump2");
    pGridZEnt->setCastShadows(false);
    Ogre::SceneNode* gridZNode = mSceneMgr->createSceneNode("gridZ");
	mSceneMgr->getRootSceneNode()->addChild(gridZNode);
	gridZNode->attachObject(pGridZEnt);
	gridZNode->scale(2,2,2);
	gridZNode->setPosition(8,10,-2);

	// Create plane for grid 
   	Ogre::Plane gridZ2;
   	gridZ2.normal = Ogre::Vector3::UNIT_Z ;
    // horizontal plane with normal up in X-direction
   	gridZ2.d;//Plane passes through the origin i.e. plane at y = 0
	Ogre::MeshManager::getSingleton().createPlane("gridZ2",
   	Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, gridZ2, 10,10,1,1,true,1,5,5,Ogre::Vector3::UNIT_X);
   	Ogre::Entity* pGridZEnt2 = mSceneMgr->createEntity("gridZ2", "gridZ2");
    pGridZEnt2->setMaterialName("Examples/MRAMOR-bump2");
    pGridZEnt2->setCastShadows(false);
    Ogre::SceneNode* gridZNode2 = mSceneMgr->createSceneNode("gridZ2");
	mSceneMgr->getRootSceneNode()->addChild(gridZNode2);
	gridZNode2->attachObject(pGridZEnt2);
	gridZNode2->scale(2,2,2);
	gridZNode2->setPosition(8,30,-2);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20,80,50);
	
	Ogre::Light* li = mSceneMgr->createLight("AmbientLight");
    li->setPosition(Ogre::Vector3(-50,35,10));
	li->setCastShadows(true);
	li->setDirection(Ogre::Vector3(30,15,5));

	Ogre::Light* light = mSceneMgr->createLight("AmbientLight2");
    light->setPosition(Ogre::Vector3(10,35,-50));
	light->setCastShadows(true);
	light->setDirection(Ogre::Vector3(5,15,30));

	Ogre::Light* light3 = mSceneMgr->createLight("AmbientLight3");
    light3->setPosition(Ogre::Vector3(400,10,10));
	light3->setPowerScale(0.1);
	light3->setCastShadows(true);
	light3->setDirection(Ogre::Vector3(5,15,10));

	//li->setDiffuseColour(Ogre::Real(1),Ogre::Real(0),Ogre::Real(0));
	  //myCube = new Cube(mSceneMgr); 
   // Now initialise all of it�s properties to match the //graphics model of the sphere as in ballNode

	  
	  int width = 5;
	  int height = 14;
	  int depth = 5;
	  int shapeArraySize = 100;
	 
	//array3D = new vector<Cube*>;	
	 //sizing the 3D array

		array3D.resize(width);
		for (int i = 0; i < width; ++i) 
		{
			array3D[i].resize(height);

			for (int j = 0; j < height; ++j)
			{
				array3D[i][j].resize(depth);
			}
		}

	 // cubes.resize(30);
  //    for(int i = 0; i< 30; i++)
	 // {
		//stringstream ss;
		//ss << i;
		//string entityName = "cube" +ss.str();
		//string nodeName = "cubeNode" +ss.str();
		//string entityName2 = "shadow" +ss.str();
		//string nodeName2 = "shadowNode" +ss.str();
		//string entityName3 = "2shadow" +ss.str();
		//string nodeName3 = "2shadowNode" +ss.str();
		//string entityName4 = "3shadow" +ss.str();
		//string nodeName4 = "3shadowNode" +ss.str();
		//Ogre::Vector3 tempPos = Ogre::Vector3(8,42,8);
		//cubes[i] = new Cube(mSceneMgr,2,10,2,entityName,nodeName,entityName2,nodeName2,entityName3,nodeName3,entityName4,nodeName4,tempPos);
	 // }

	  //zShape1 = new zShape(mSceneMgr,blueBox);
		string blueBox = "Examples/MRAMOR-bumpBlue";
		string yellowBox = "Examples/MRAMOR-bumpYellow";


		zShapes.resize(shapeArraySize);
		boxes.resize(shapeArraySize);
		tShapes.resize(shapeArraySize);      
		tOppShapes.resize(shapeArraySize);
		lShapes.resize(shapeArraySize);
		lOppShapes.resize(shapeArraySize);
	  //box1 = new zShape(mSceneMgr, yellowBox);
	  //box2 = new zShape(mSceneMgr, yellowBox);

}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        ProjectOne app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif