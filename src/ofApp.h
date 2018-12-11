//
//  Blocks - Starter Source File for CS 116A Midterm Problem  - Fall 2018
//
//  
//  (c) Kevin M. Smith  - 27 October 2018
//
 

#include "ofMain.h"
#include "box.h"
#include "Primitives.h"


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		static void drawAxis(glm::mat4 transform = glm::mat4(1.0), float len = 1.0);
		void printChannels(SceneObject *);
		
		// Lights
		//
		ofLight light1;
	
		// Cameras
		//
		ofEasyCam  mainCam;
		ofCamera sideCam;
		ofCamera topCam;
		ofCamera  *theCam;    // set to current camera either mainCam or sideCam

		// Materials
		//
		ofMaterial material;


		// scene components
		//
		vector<SceneObject *> scene;
		SceneObject *selectedObj = NULL;
		ofPlanePrimitive plane;

		float mouseX, mouseY, mouseZ;

		ofVec3f scrnPos, newPos;

		bool ctrl;

		glm::mat4 matrix, rMatrix, tMatrix;

};