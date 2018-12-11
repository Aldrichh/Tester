//
//  Blocks - Starter Source Files for CS 116A Midterm Problem  - Fall 2018
//
//  
//  (c) Kevin M. Smith  - 27 October 2018
//
//
//  Instructions:  Complete the code required to move/translate/rotate the blocks 
//  so they can be stacked (as in the video shown).  When translating a block, it should
//  track with the mouse pointer.
//
//  Note:  It is only required to modify ofApp.cpp and OfApp.h to solve the problem.
//                
//

#include "ofApp.h"



//--------------------------------------------------------------
//
void ofApp::setup() {

	ofSetBackgroundColor(ofColor::black);
	ofEnableDepthTest();
	mainCam.setDistance(15);
	mainCam.setNearClip(.1);
	
	sideCam.setPosition(25, 0, 0);
	sideCam.lookAt(glm::vec3(0, 0, 0));
	topCam.setNearClip(.1);
	topCam.setPosition(0, 16, 0);
	topCam.lookAt(glm::vec3(0, 0, 0));
	ofSetSmoothLighting(true);

	// setup one point light
	//
	light1.enable();
	light1.setPosition(5, 5, 0);
	light1.setDiffuseColor(ofColor(255.f, 255.f, 255.f));
	light1.setSpecularColor(ofColor(255.f, 255.f, 255.f));

	theCam = &mainCam;

	//  create a scene consisting of a ground plane with 2x2 blocks
	//  arranged in semi-random positions, scales and rotations
	//
	// ground plane
	//
	scene.push_back(new Plane(glm::vec3(0, -2, 0), glm::vec3(0, 1, 0)));   

	// blocks (initial state with starting transformations)
	//
	scene.push_back(new Cube( glm::vec3(1.46321,  -0.0340148, -3.97571),   glm::vec3(0,   0,       58.0214),  glm::vec3(2, .5, 1),      ofColor::purple));
	scene.push_back(new Cube( glm::vec3(-1.54231, -1.225,      3.2706),    glm::vec3(0,  -10.1856, 0),        glm::vec3(.75, .75, .75), ofColor::blue));
	scene.push_back(new Cube( glm::vec3(3.55227,   0.0706874, -4.01301),   glm::vec3(0,   0,       0),        glm::vec3(.5, 2, .5),     ofColor::yellow));
	scene.push_back(new Cube( glm::vec3(2.94547,  -0.695337,  -0.0323806), glm::vec3(0,  -63.583,  0),        glm::vec3(1, 1, 1),       ofColor::orange));
	scene.push_back(new Cube( glm::vec3(0.559671,  0.147776,   4.0742),    glm::vec3(0,  -14.4059, 0),        glm::vec3(.5, 2, .5),     ofColor::indigo));
	scene.push_back(new Cube( glm::vec3(7.84789,  -1.48378,   -7.67569),   glm::vec3(0,  -64.3264, 0),        glm::vec3(2, .5, 1),      ofColor::red));
}

 
//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

	theCam->begin();
	ofNoFill();
	drawAxis();
	ofEnableLighting();

	//  draw the objects in scene
	//
	material.begin();
	ofFill();
	for (int i = 0; i < scene.size(); i++) {
		if (scene[i] == selectedObj)
			ofSetColor(ofColor::white);
		else ofSetColor(scene[i]->diffuseColor);
		scene[i]->draw();
	}

	material.end();
	ofDisableLighting();
	theCam->end();
}

// 
// Draw an XYZ axis in RGB at transform
//
void ofApp::drawAxis(glm::mat4 m, float len) {

	ofSetLineWidth(1.0);

	// X Axis
	ofSetColor(ofColor(255, 0, 0));
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(len, 0, 0, 1)));


	// Y Axis
	ofSetColor(ofColor(0, 255, 0));
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, len, 0, 1)));

	// Z Axis
	ofSetColor(ofColor(0, 0, 255));
	ofDrawLine(glm::vec3(m*glm::vec4(0, 0, 0, 1)), glm::vec3(m*glm::vec4(0, 0, len, 1)));
}

// print C++ code for obj tranformation channels. (for debugging);
//
void ofApp::printChannels(SceneObject *obj) {
	if (!obj) return;
	cout << "position = glm::vec3(" << obj->position.x << "," << obj->position.y << "," << obj->position.z << ");" << endl;
	cout << "rotation = glm::vec3(" << obj->rotation.x << "," << obj->rotation.y << "," << obj->rotation.z << ");" << endl;
	cout << "scale = glm::vec3(" << obj->scale.x << "," << obj->scale.y << "," << obj->scale.z << ");" << endl;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

	switch (key) {
	case OF_KEY_CONTROL:
		ctrl = false;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case 'C':
	case 'c':
		if (mainCam.getMouseInputEnabled()) mainCam.disableMouseInput();
		else mainCam.enableMouseInput();
		break;
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case 'p':
		if (selectedObj) printChannels(selectedObj);
		break;
	case OF_KEY_F1: 
		theCam = &mainCam;
		break;
	case OF_KEY_F2:
		theCam = &sideCam;
		break;
	case OF_KEY_F3:
		theCam = &topCam;
		break;
	case OF_KEY_CONTROL:
		ctrl = true;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

	if (selectedObj != NULL)
	{

		// For rotation.
		if (ctrl)
		{
			newPos = theCam->screenToWorld(glm::vec3(x, y, 0));
			glm::vec3 rotate = newPos - scrnPos;
			selectedObj->rotation = selectedObj->rotation + (rotate * 10);
		}
		else
		{
			//cout << "orignal screen position (" << scrnPos.x << ", " << scrnPos.y << ", " << scrnPos.z << ")" << endl;
			newPos = theCam->screenToWorld(ofVec3f(x, y, 0));
			glm::vec3 translate = newPos - scrnPos;
			//cout << "New screen position (" << newPos.x << ", " << newPos.y << ", " << newPos.z << ")" << endl << endl;
			// Subtract the difference of the distance of the mouse.
			selectedObj->position = selectedObj->position + translate;
			
			//selectedObj->position = ofVec3f(selectedObj->position) * g;
		}
		mainCam.enableMouseInput();
	}
}


//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	glm::vec3 point, normal;
	
	mouseX = x;
	mouseY = y;
	
	scrnPos = theCam->screenToWorld(ofVec3f(x, y, 0));

	cout << "scrnPos: (" << scrnPos.x << ", " << scrnPos.y << ", " << scrnPos.z << ")" << endl;
	ofVec3f d2 = theCam->getPosition() - scrnPos;
	Ray ray = Ray(theCam->getPosition(), d2.normalized());

	float nearestDist = std::numeric_limits<float>::infinity();

	for (int i = 0; i < scene.size(); i = i + 1)
	{
		
		if (scene.at(i)->intersect(ray, point, normal))
		{
			float dist = glm::length(point - theCam->getPosition());
			if (selectedObj != NULL)
			{
				if (dist< nearestDist)
				{
					selectedObj = scene.at(i);
					nearestDist = dist;
				}
			}
			else
			{
				selectedObj = scene.at(i);
				nearestDist = dist;
				//cout << "Selected: " << i << endl;
			}
		}
	}
	if (selectedObj != NULL)
	{
		mainCam.disableMouseInput();
		cout << "Object's initial (" << selectedObj->position.x << ", " << selectedObj->position.y << ", " << selectedObj->position.z << ") " << endl;
	}

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	printChannels(selectedObj);
	mainCam.enableMouseInput();
	selectedObj = NULL;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

