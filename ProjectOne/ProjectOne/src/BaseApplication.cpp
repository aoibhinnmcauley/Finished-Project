/*
-----------------------------------------------------------------------------
Filename:    BaseApplication.cpp
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
#include "BaseApplication.h"


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "../res/resource.h"
#endif


//-------------------------------------------------------------------------------------
BaseApplication::BaseApplication(void)
    : mRoot(0),
    mCamera(0),
    mSceneMgr(0),
    mWindow(0),
    mResourcesCfg(Ogre::StringUtil::BLANK),
    mPluginsCfg(Ogre::StringUtil::BLANK),
    mTrayMgr(0),
    mCameraMan(0),
    mDetailsPanel(0),
    mCursorWasVisible(false),
    mShutDown(false),
    mInputManager(0),
    mMouse(0),
    mKeyboard(0)
{

	timerCHECK = 0;
	music = true;
	effects = true;

	init = false;
	arrayClearHeight = 0;
	arrayHeight = 10;
	arrayWidth = 5;
	arrayDepth = 5;

	layersCleared = 0;
	nextLevelInt = 0;
	nextLevelAmount = 2;
	currentLevel = 1;
	scoreMultiplier = 500;
	score = 0;

	mainTickValue = 2500.00;

	usedZShape = false;
	usedBoxShape = false;
	usedTShape = false;
	usedTShapeOpp = false;
	usedlShape = false;
	usedlShapeOpp = false;

	currentZShapeCell = 0;
	currentBoxShapeCell = 0;
	currentTShapeCell = 0;
	currentTShapeOppCell = 0;
	currentlShapeCell = 0;
	currentlShapeOppCell = 0;

	

	//randomShape();

	//setup FMOD
	result = FMOD::System_Create(&FMODsys);     // Create the main system object.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" <<result;// << FMOD_ErrorString(result);
		exit(-1);
	}

	result = FMODsys->init(100, FMOD_INIT_NORMAL, 0);   // Initialize FMOD.

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;// << FMOD_ErrorString(result);
		exit(-1);
	}
	result = FMODsys->createSound("C:/Users/Darren/Desktop/finished/ProjectColour/ProjectOne/ProjectOne/sounds/Robix.mp3",FMOD_LOOP_OFF|FMOD_3D,0,&soundStart);

	result = FMODsys->createSound("C:/Users/Darren/Desktop/finished/ProjectColour/ProjectOne/ProjectOne/sounds/sound.wav",FMOD_LOOP_OFF|FMOD_3D,0,&sound);

	result = FMODsys->createSound("C:/Users/Darren/Desktop/finished/ProjectColour/ProjectOne/ProjectOne/sounds/successful.mp3",FMOD_LOOP_OFF|FMOD_3D,0,&soundDrop);

	if (result != FMOD_OK)
	{
		std::cout << "FMOD error! (%d) %s\n" << result;
		exit(-1);
	}
	
	if(music == true)
	{
	  FMODsys->playSound(FMOD_CHANNEL_FREE,soundStart,music,0);
	}
	
	Ogre::LogManager* logMgr = new Ogre::LogManager();
 
    m_pLog = Ogre::LogManager::getSingleton().createLog("OgreLogfile.log", true, true, false);
    m_pLog->setDebugOutputEnabled(true);


}

//-------------------------------------------------------------------------------------
BaseApplication::~BaseApplication(void)
{
    if (mTrayMgr) delete mTrayMgr;
    if (mCameraMan) delete mCameraMan;

    //Remove ourself as a Window listener
    Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    windowClosed(mWindow);
    delete mRoot;
}

//-------------------------------------------------------------------------------------
bool BaseApplication::configure(void)
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(mRoot->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        mWindow = mRoot->initialise(true, "ProjectOne Render Window");

        // Let's add a nice window icon
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
        HWND hwnd;
        mWindow->getCustomAttribute("WINDOW", (void*)&hwnd);
        LONG iconID   = (LONG)LoadIcon( GetModuleHandle(0), MAKEINTRESOURCE(IDI_APPICON) );
        SetClassLong( hwnd, GCL_HICON, iconID );
#endif
        return true;
    }
    else
    {
        return false;
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::chooseSceneManager(void)
{
    // Get the SceneManager, in this case a generic one
    mSceneMgr = mRoot->createSceneManager(Ogre::ST_GENERIC);
}
//-------------------------------------------------------------------------------------
void BaseApplication::createCamera(void)
{
    // Create the camera
    mCamera = mSceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
     mCamera->setPosition(Ogre::Vector3(40,60,80));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(-20,-10,-50));
    mCamera->setNearClipDistance(5);

    mCameraMan = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}
//-------------------------------------------------------------------------------------
void BaseApplication::createFrameListener(void)
{
    Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

    mInputManager = OIS::InputManager::createInputSystem( pl );

    mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
    mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

    //Set initial mouse clipping size
    windowResized(mWindow);

    //Register as a Window listener
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

    mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mWindow, mMouse, this);
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    mTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    mTrayMgr->hideCursor();

    // create a params panel for displaying sample details
    Ogre::StringVector items;

	 items.push_back("Current Level");
    items.push_back("Score");
    items.push_back("Layers Cleared");
    items.push_back("Sound effects (V/B): ");
    items.push_back("Music (2/3): ");
    items.push_back("");
    items.push_back("");
    items.push_back("");
    items.push_back("");
    items.push_back("");
    items.push_back("");

    mDetailsPanel = mTrayMgr->createParamsPanel(OgreBites::TL_NONE, "DetailsPanel", 200, items);
    mDetailsPanel->setParamValue(9, "Bilinear");
    mDetailsPanel->setParamValue(10, "Solid");
    mDetailsPanel->hide();

    mRoot->addFrameListener(this);
}
//-------------------------------------------------------------------------------------
void BaseApplication::destroyScene(void)
{
}
//-------------------------------------------------------------------------------------
void BaseApplication::createViewports(void)
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}
//-------------------------------------------------------------------------------------
void BaseApplication::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;
            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}
//-------------------------------------------------------------------------------------
void BaseApplication::createResourceListener(void)
{

}
//-------------------------------------------------------------------------------------
void BaseApplication::loadResources(void)
{
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}
//-------------------------------------------------------------------------------------
void BaseApplication::go(void)
{
#ifdef _DEBUG
    mResourcesCfg = "resources_d.cfg";
    mPluginsCfg = "plugins_d.cfg";
#else
    mResourcesCfg = "resources.cfg";
    mPluginsCfg = "plugins.cfg";
#endif

    if (!setup())
        return;

    mRoot->startRendering();

    // clean up
    destroyScene();
}
//-------------------------------------------------------------------------------------
bool BaseApplication::setup(void)
{
    mRoot = new Ogre::Root(mPluginsCfg);

    setupResources();

    bool carryOn = configure();
    if (!carryOn) return false;

    chooseSceneManager();
    createCamera();
    createViewports();

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // Create any resource listeners (for loading screens)
    createResourceListener();
    // Load resources
    loadResources();

    // Create the scene
    createScene();
	createGUI();

    createFrameListener();

	
    //cubes[currentCube]->setBegin(true);
	

	return true;
};
//-------------------------------------------------------------------------------------
bool BaseApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	

    if(mWindow->isClosed())
        return false;

    if(mShutDown)
        return false;

	FMOD_VECTOR listerThing = {0.0f,0.0f,0.0f};
	FMOD_VECTOR listerPos = {mCamera->getPosition().x,0.0f,mCamera->getPosition().z};
	FMODsys->set3DListenerAttributes(0, &listerPos, &listerThing,0,0);

	//update position of sound 
	if(channel){
		FMOD_VECTOR soundScorce = {0.0f,0.0f,0.0f};
		//scorce fixed
		channel->set3DAttributes(&soundScorce, 0);
	}
	FMODsys->update();

    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();


    mTrayMgr->frameRenderingQueued(evt);

    if (!mTrayMgr->isDialogVisible())
    {
        mCameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
        if (mDetailsPanel->isVisible())   // if details panel is visible, then update its contents
        {
            mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(currentLevel));
            mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(score));
            mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(layersCleared));
            mDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(effects));
            mDetailsPanel->setParamValue(4, Ogre::StringConverter::toString(music));
           // mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(music));
           // mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));
        }


	}
		double timeChange = evt.timeSinceLastFrame;

		if(init == false)
		{
		   randomShape();
		   //TrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
		   mDetailsPanel->show();
		   init = true;
		}
		

		if(mKeyboard->isKeyDown(OIS::KC_1))
		{
			
			mCamera->setPosition(Ogre::Vector3(10,80,10));
			// Look back along -Z
			mCamera->lookAt(Ogre::Vector3(0,-10,0));
			mCamera->setNearClipDistance(5);
		}
		else if(mKeyboard->isKeyDown(OIS::KC_2))
		{
			
			mCamera->setPosition(Ogre::Vector3(-50,35,10));
			// Look back along -Z
			mCamera->lookAt(Ogre::Vector3(30,15,5));
			mCamera->setNearClipDistance(5);
		}
		else if(mKeyboard->isKeyDown(OIS::KC_3))
		{
			mCamera->setPosition(Ogre::Vector3(70,35,10));
			// Look back along -Z
			mCamera->lookAt(Ogre::Vector3(5,15,10));
			mCamera->setNearClipDistance(5);	
		}
		else if(mKeyboard->isKeyDown(OIS::KC_4))
		{
			
			mCamera->setPosition(Ogre::Vector3(10,35,-50));
			// Look back along -Z
			mCamera->lookAt(Ogre::Vector3(5,15,30));
			mCamera->setNearClipDistance(5);	
		}
		else
		{
			mCamera->setPosition(Ogre::Vector3(40,60,80));
			// Look back along -Z
			mCamera->lookAt(Ogre::Vector3(-20,-10,-50));
			mCamera->setNearClipDistance(5);
		}
		

		if(currentShapeType == zShapeType)
		{
			
				zShapes[currentZShapeCell]->Update(timeChange,mKeyboard,array3D, mainTickValue);
				if(zShapes[currentZShapeCell]->alive == false)
				{
					currentZShapeCell++;
					randomShape();
				}

		
		}
		else if(currentShapeType == boxType)
		{
				boxes[currentBoxShapeCell]->Update(timeChange,mKeyboard,array3D,mainTickValue);

				if(boxes[currentBoxShapeCell]->alive == false)
				{
					currentBoxShapeCell++;
					randomShape();
				}
		}
		else if(currentShapeType == tShapeType)
		{
				tShapes[currentTShapeCell]->Update(timeChange,mKeyboard,array3D,mainTickValue);

				if(tShapes[currentTShapeCell]->alive == false)
				{
					currentTShapeCell++;
					randomShape();
				}
		}
		else if(currentShapeType == tShapeOppType)
		{
				tOppShapes[currentTShapeOppCell]->Update(timeChange,mKeyboard,array3D,mainTickValue);

				if(tOppShapes[currentTShapeOppCell]->alive == false)
				{
					currentTShapeOppCell++;
					randomShape();
				}
		}
		else if(currentShapeType == lShapeType)
		{
				lShapes[currentlShapeCell]->Update(timeChange,mKeyboard,array3D,mainTickValue);

				if(lShapes[currentlShapeCell]->alive == false)
				{
					currentlShapeCell++;
					randomShape();
				}
		}
		else if(currentShapeType == lShapeOppType)
		{
				lOppShapes[currentlShapeOppCell]->Update(timeChange,mKeyboard,array3D,mainTickValue);

				if(lOppShapes[currentlShapeOppCell]->alive == false)
				{
					currentlShapeOppCell++;
					randomShape();
				}
		}


		if(usedZShape == true && usedBoxShape == true && usedTShape == true && usedTShapeOpp == true && usedlShape == true && usedlShapeOpp == true)
		{
			usedZShape = false;
			usedBoxShape = false;
			usedTShape = false;
			usedTShapeOpp = false;
			usedlShape = false;
			usedlShapeOpp = false;
		}



		for(int i = 0; i <= currentZShapeCell - 1; i++)
		{
			if(currentZShapeCell != 0)
			zShapes[i]->isDropping(array3D);

		}
		for(int i = 0; i <= currentTShapeCell - 1; i++)
		{
			if(currentTShapeCell != 0)
			tShapes[i]->isDropping(array3D);

		}
		for(int i = 0; i <= currentTShapeOppCell - 1; i++)
		{
			if(currentTShapeOppCell != 0)
			tOppShapes[i]->isDropping(array3D);

		}
		for(int i = 0; i <= currentBoxShapeCell - 1; i++)
		{
			if(currentBoxShapeCell != 0)
			boxes[i]->isDropping(array3D);

		}
		for(int i = 0; i <= currentlShapeCell - 1; i++)
		{
			if(currentlShapeCell != 0)
			lShapes[i]->isDropping(array3D);

		}
		for(int i = 0; i <= currentlShapeOppCell - 1; i++)
		{
			if(currentlShapeOppCell != 0)
			lOppShapes[i]->isDropping(array3D);

		}

		//moving onto next level
		if(nextLevelInt >= nextLevelAmount)
		{
			nextLevel();
			nextLevelInt = nextLevelInt - nextLevelAmount;
		}



		if(scoreMultiplier >= 400 && scoreMultiplier <= 500)
		{

			if(_timer.getMilliseconds() > 1000)
			{
				scoreMultiplier--;
				_timer.reset();
			}

		}
		else if(scoreMultiplier >= 300 && scoreMultiplier < 500)
		{
			if(_timer.getMilliseconds() > 2000)
			{
				scoreMultiplier--;
				_timer.reset();
			}

		}
		else if(scoreMultiplier >= 200 && scoreMultiplier < 300)
		{
			if(_timer.getMilliseconds() > 3000)
			{
				scoreMultiplier--;
				_timer.reset();
			}
		}
		else if(scoreMultiplier >= 100 && scoreMultiplier < 200)
		{
			if(_timer.getMilliseconds() > 5000)
			{
				scoreMultiplier--;
				_timer.reset();
			}

		}
		else
		{
			scoreMultiplier = 100;

		}
		
			for(int y = 0; y < arrayHeight; y++)
			{
				int count = 0;
				int fullGrid = 25;
				for(int i = 0; i < arrayWidth; i++)
				{
					for(int j = 0; j < arrayDepth; j++)
					{
						if(array3D[i][y][j] != 0)
						{	
								count++;		
						}
					}
				}
				if(count == fullGrid)
				{
					int arrayClearHeightNo = y;
					for(int x = 0; x < arrayWidth; x++)
					{
						for(int z = 0; z < arrayDepth; z++)
						{
							if(array3D[x][y][z] != 0)
							{
								//m_pLog->logMessage("x: " + Ogre::StringConverter::toString(x));

								array3D[x][y][z]->setAlive(false);
								array3D[x][y][z]  = 0;
								count = 0;
								
							}
						}
					}
					layersCleared++;
					nextLevelInt++;
 					dropLevelIn3DArray(arrayClearHeightNo);
				
				}
			}
	

	checkForEndGame();

    return true;
	
}


void BaseApplication::nextLevel()
{

	currentLevel++;
	mainTickValue = mainTickValue - 250.00;


}

void BaseApplication::checkForEndGame()
{
	int aboveArrayHeight = 11;
	int maxCheck = 14;
	for(int y = aboveArrayHeight; y < maxCheck; y++)
	{		
		for(int i = 0; i < arrayWidth; i++)
		{
			for(int j = 0; j < arrayDepth; j++)
			{
				if(array3D[i][y][j] != 0)
				{
					  mShutDown = true;
				}
			}
		}
	}

}
void BaseApplication::randomShape()
{
	int randomValue = rand() % 6;        

	string lightBlueBox = "Examples/MRAMOR-bumpBlue";
	string darkBlueBox = "Examples/MRAMOR-bumpDarkBlue";
	string yellowBox = "Examples/MRAMOR-bumpYellow";
	string greenBox = "Examples/MRAMOR-bumpGreen";
	string redBox = "Examples/MRAMOR-bumpRed";
	string orangeBox = "Examples/MRAMOR-bumpOrange";
	string purpleBox = "Examples/MRAMOR-bumpPurple";
	


	stringstream ss;

	if(randomValue == 0 && usedZShape == false) 
	{
		ss << currentZShapeCell;

		zShapes[currentZShapeCell] = new zShape(mSceneMgr,"myZShape" + ss.str(), darkBlueBox);

		currentShapeType = zShapeType;

		usedZShape = true;
	}
	else if(randomValue == 1 && usedBoxShape == false) //&&
	{
		ss << currentBoxShapeCell;

		boxes[currentBoxShapeCell] = new box(mSceneMgr,"myBox" + ss.str(), yellowBox);

		currentShapeType = boxType;

		usedBoxShape = true;
	}
	else if(randomValue == 2 && usedTShape == false) //&&
	{
		ss << currentTShapeCell;

		tShapes[currentTShapeCell] = new tShape(mSceneMgr,"myT" + ss.str(), greenBox);

		currentShapeType = tShapeType;

		usedTShape = true;
	}
	else if(randomValue == 3 && usedTShapeOpp == false) //&&
	{
		ss << currentTShapeOppCell;

		tOppShapes[currentTShapeOppCell] = new tShapeOpp(mSceneMgr,"myTOpp" + ss.str(), purpleBox);

		currentShapeType = tShapeOppType;

		usedTShapeOpp = true;
	}
	else if(randomValue == 4 && usedlShape == false) //&&
	{
		ss << currentlShapeCell;

		lShapes[currentlShapeCell] = new lShape(mSceneMgr,"myl" + ss.str(), redBox);

		currentShapeType = lShapeType;

		usedlShape = true;
	}
	else if(randomValue == 5 && usedlShapeOpp == false) //&&
	{
		ss << currentlShapeOppCell;

		lOppShapes[currentlShapeOppCell] = new lShapeOpp(mSceneMgr,"mylOpp" + ss.str(), orangeBox);

		currentShapeType = lShapeOppType;

		usedlShapeOpp = true;
	}
	else
	{
		randomShape();
	}

}
//-------------------------------------------------------------------------------------
void BaseApplication::dropLevelIn3DArray(int arrayClearHeightNew)
{
	for(int y = arrayClearHeightNew + 1; y < arrayHeight; y++)
	{		
		for(int i = 0; i < arrayWidth; i++)
		{
			for(int j = 0; j < arrayDepth; j++)
			{
				if(array3D[i][y][j] != 0)
				{

					if(array3D[i][y][j]->gridPosY != 0)
					{
						array3D[i][y][j]->m_position.y = array3D[i][y][j]->m_position.y - 4;
						
						array3D[i][y][j]->targetNode->setPosition(Ogre::Vector3(array3D[i][y][j]->m_position));

						array3D[i][y][j]->gridPosY = array3D[i][y][j]->gridPosY - 1;

						Cube* tempPos = array3D[i][y][j];

						array3D[i][y - 1][j] = tempPos;
						array3D[i][y][j] = 0;

					}
					

				}
			}
		}
	}

	score = score + (scoreMultiplier * currentLevel);
	scoreMultiplier = 500;
	_timer.reset();

}
bool BaseApplication::keyPressed( const OIS::KeyEvent &arg )
{
	
	if (arg.key == OIS::KC_SPACE)   // toggle visibility of advanced frame stats
    {
		if(effects == true)
		{
			FMODsys->playSound(FMOD_CHANNEL_FREE, soundDrop,false, &channel3);
		}

	}

    if (mTrayMgr->isDialogVisible()) return true;   // don't process any more keys if dialog is up

    if (arg.key == OIS::KC_F)   // toggle visibility of advanced frame stats
    {
        mTrayMgr->toggleAdvancedFrameStats();
    }
    else if (arg.key == OIS::KC_G)   // toggle visibility of even rarer debugging details
    {
        if (mDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            //mTrayMgr->moveWidgetToTray(mDetailsPanel, OgreBites::TL_TOPRIGHT, 0);
            mDetailsPanel->show();
        }
        else
        {
            mTrayMgr->removeWidgetFromTray(mDetailsPanel);
            mDetailsPanel->hide();
        }
    }
    else if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::TextureFilterOptions tfo;
        unsigned int aniso;

        switch (mDetailsPanel->getParamValue(9).asUTF8()[0])
        {
        case 'B':
            newVal = "Trilinear";
            tfo = Ogre::TFO_TRILINEAR;
            aniso = 1;
            break;
        case 'T':
            newVal = "Anisotropic";
            tfo = Ogre::TFO_ANISOTROPIC;
            aniso = 8;
            break;
        case 'A':
            newVal = "None";
            tfo = Ogre::TFO_NONE;
            aniso = 1;
            break;
        default:
            newVal = "Bilinear";
            tfo = Ogre::TFO_BILINEAR;
            aniso = 1;
        }

        Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
        Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
        mDetailsPanel->setParamValue(9, newVal);
    }
    else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
    {
        Ogre::String newVal;
        Ogre::PolygonMode pm;

        switch (mCamera->getPolygonMode())
        {
        case Ogre::PM_SOLID:
            newVal = "Wireframe";
            pm = Ogre::PM_WIREFRAME;
            break;
        case Ogre::PM_WIREFRAME:
            newVal = "Points";
            pm = Ogre::PM_POINTS;
            break;
        default:
            newVal = "Solid";
            pm = Ogre::PM_SOLID;
        }

        mCamera->setPolygonMode(pm);
        mDetailsPanel->setParamValue(10, newVal);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
        Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
    }
	if(arg.key == OIS::KC_LEFT)   // refresh all textures
    {
		
		if(effects == true)
		{
	   	FMODsys->playSound(FMOD_CHANNEL_FREE, sound,false, &channel2);
		}
		
		
	}
	else if(arg.key == OIS::KC_UP)   // refresh all textures
    {
		if(effects == true)
		{
		FMODsys->playSound(FMOD_CHANNEL_FREE, sound,false, &channel2);
		}
		
		
	}
	else if(arg.key == OIS::KC_RIGHT)   // refresh all textures
    {
		if(effects == true)
		{
		FMODsys->playSound(FMOD_CHANNEL_FREE, sound,false, &channel2);
		}
		
				
	}
	else if(arg.key == OIS::KC_DOWN)   // refresh all textures
    {
	 if(effects == true)
		{
		FMODsys->playSound(FMOD_CHANNEL_FREE, sound,false, &channel2);
	    }
	 
	
	}
	
	else if(arg.key == OIS::KC_2)   // refresh all textures
    {
		result = FMODsys->createReverb(&reverb);
		FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_UNDERWATER;
		reverb->setProperties(&prop);
		FMOD_VECTOR pos = {mCamera->getPosition().x, 0.0f ,mCamera->getPosition().z};
		float minDistance = 80.0f;
		float maxDistance = 200.0f;
		reverb->set3DAttributes(&pos,minDistance,maxDistance);
		reverb->setActive(true);
		float volume = 2.0f;
		FMODsys->playSound(FMOD_CHANNEL_FREE, soundStart, false, &channel);
		channel->set3DMinMaxDistance(50,1000);
		channel->setPaused(false);
		music = true;

	}
	else if(arg.key == OIS::KC_3)   // refresh all textures
    {
		channel->setPaused(true);
		music = false;
		
	}
	
	 if(arg.key == OIS::KC_B)   // refresh all textures
	 {
		//FMODsys->playSound(FMOD_CHANNEL_FREE, sound,true, &channel2);
		 effects = true;
	}
	 if(arg.key == OIS::KC_V)   // refresh all textures
	 {
		//FMODsys->playSound(FMOD_CHANNEL_FREE, sound,true, &channel2);
		 effects = false;
	 }

   // mCameraMan->injectKeyDown(arg);
    return true;
}

bool BaseApplication::keyReleased( const OIS::KeyEvent &arg )
{


   // mCameraMan->injectKeyUp(arg);
    return true;
}

bool BaseApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    if (mTrayMgr->injectMouseMove(arg)) return true;
    mCameraMan->injectMouseMove(arg);
    return true;
}

bool BaseApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseDown(arg, id)) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}

bool BaseApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if (mTrayMgr->injectMouseUp(arg, id)) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}

//Adjust mouse clipping area
void BaseApplication::windowResized(Ogre::RenderWindow* rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void BaseApplication::windowClosed(Ogre::RenderWindow* rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow )
    {
        if( mInputManager )
        {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );

            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}

void BaseApplication::createGUI() 
{ 
	mGui3D = new Gui3D::Gui3D(&mMySimpleDemoPanelColors); 
	mGui3D->createScreen(mWindow->getViewport(0), "simpleDemo", "mainScreen");
	mPanel = new Gui3D::Panel( mGui3D, mSceneMgr, Ogre::Vector2(4000, 4000), 10, "simpleDemo", "test_panel");
	mPanel->mNode->setPosition(-100,-100,-50); 
}