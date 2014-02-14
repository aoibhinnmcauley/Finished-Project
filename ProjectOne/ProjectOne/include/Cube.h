#ifndef __Cube_h_
#define __Cube_h_

#include "Ogre.h" 
#include <cstdio>
#include "BaseApplication.h"
#include <ctime>

class Cube
{
public:
	        /*! constructor  */
			Cube(); 
			/*! constructor  */
			Cube(Ogre::SceneManager *,int,int,int,string, string,string, string,string, string,string,string, Ogre::Vector3,string);  
			/*!  destructor  */
			~Cube(void);
			/*! returns m_position  */
			Ogre::Vector3 getPosition(); 
			/*! returns m_velocity  */
		    Ogre::Vector3 getVelocity();
			/*! returns SceneNode pointer  */
            Ogre::SceneNode* getNode();
			/*! returns m_radius  */
            double getLenth();  
			/*! // returns m_move  */
            bool getMove();  
			/*! gets the time  */
			int getTime();
			/*! sets m_position  */
			void setPosition(Ogre::Vector3);
			/*! sets m_velocity  */
	    	void setVelocity(Ogre::Vector3);
			/*! setsMove  */
			void setMove(bool); 	
			/*! sets dropped  */
			void setDropped(bool);
			/*! set checked  */
			void setChecked(bool);
			/*! set alive  */
			void setAlive(bool);
			/*! set begin  */
			void setBegin(bool);
			/*! ogre timer  */
			Ogre::Timer _timer;
			/*! ogrer timer  */
			Ogre::Timer drop_timer;
			/*! set timer  */
			void setTime(int); 
			/*! set drop  */
			void setDrop(bool);
			/*! Update method  */
			void Update(double,OIS::Keyboard*, vector<vector<vector<Cube*>>> & array3D, int boundaryX, int boundaryX2, int boundaryZ, int boundaryZ2); 
			/*! drop the cube down the screen  */
			void droppingCube(vector<vector<vector<Cube*>>> & array3D);
			/*! drop the cube into place below   */
			void instantDrop(vector<vector<vector<Cube*>>> & array3D);
			/*! move the shadow appropriately with the shape  */
			void moveShadow(vector<vector<vector<Cube*>>> & array3D);
			/*! turn the shadow on and off  */
			void turnShadowOffOn();
			/*! get the X position of m_postion */
			int getGridPosX();
			/*! get the y positon of m_postion   */
			int getGridPosY();
			/*! get the z positon of m_postion  */
			int getGridPosZ();
			/*! alive or not  */			
			bool alive;
			/*! checked or not  */
			bool checked;
			/*! merger or not   */
			bool mergeArray;
			/*!  oger clock  */	 
			std::clock_t clock;
			/*! move the cube left */
			Ogre::Vector3 moveLeft;
			/*! move the cube right  */
			Ogre::Vector3 moveRight;
			/*! move the cube forward  */
			Ogre::Vector3 moveForward;
			/*! move the cube backward  */
			Ogre::Vector3 moveBackward;
			/*! move the cube down  */
			Ogre::Vector3 moveDown;

			/*! stores the x postion of m_postion  */
			int gridPosX;
			/*! stores the y postion of m_postion   */
			int gridPosY;
			/*! stores the z postion of m_postion   */
			int gridPosZ;
			/*! check whats below   */
			int gridBelow;
			/*! the name of the cube enity  */
			string entityName;
			/*! the name of the  cube node  */
			string nodeName;
			/*! the name of the shadow1 enity  */
			string entityName2;
			/*!the name of the shadow1 node  */
			string nodeName2;
			/*!  the name of the shadow2 enity  */  
			string entityName3;
			/*! the name of the shadow2 node  */
			string nodeName3;
			/*! the name of the shadow3 node  */
			string shadowName3;
			/*!the name of the shadow node  */
			string shadowNodeName3;
			/*! the name of the enity node  */
			Ogre::Entity *targetCube;
			/*! the name of the node  */
			Ogre::SceneNode *targetNode;
			/*! check if moving */
			bool m_move;
			/*! check if dropped  */
			bool dropped;
			/*! check if dropping  */
			bool drop;
			/*! check if finished dropping  */
			bool finishedDrop;
			/*! check if starting */
			bool begin;
			/*! check if visible  */
			bool flipVisibility;					
			/*! shadow plane */
			Ogre::Plane shadowPlane;
			/*! shadow entity  */
			Ogre::Entity *shadow;
			/*! shadowNode  */
			Ogre::SceneNode *shadowNode; 
			/*! shadow position  */
			Ogre::Vector3 m_shadowPos; 
			/*! shadow length  */
			float m_shadowLen; 
			/*! constructor  */

			/*! shadowNode  */
			Ogre::Plane shadowPlane2;
			/*! EntityNode  */
			Ogre::Entity *shadow2; 
			/*! SceneNode  */
			Ogre::SceneNode *shadowNode2; 
			/*! shadow positoin  */
			Ogre::Vector3 m_shadowPos2; 		
			/*! constructor  */
			Ogre::Plane shadowPlane3;
			/*! shadow plam  */
			Ogre::Entity *shadow3; 
			/*! scene node  */
			Ogre::SceneNode *shadowNode3; 
			/*! shadow position  */
			Ogre::Vector3 m_shadowPos3; 
			/*! cube position  */
			Ogre::Vector3 m_position; 
			/*! timer  */
			int m_timer;
			/*! tick amount  */
			double tick;
		

 private:
		/*! cube velocity  */
		Ogre::Vector3 m_velocity;  
		/*! cube length  */
        double m_lenth;		
		/*! Scenenode  */
		Ogre::SceneNode *m_objectNode;//graphics node of model	
		/*! timer per drop  */
		int dropTimer;
};
#endif 