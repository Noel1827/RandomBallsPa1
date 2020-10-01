#include "ofApp.h"
#include "Particle.h"

//--------------------------------------------------------------
void ofApp::setup()
{

	updating = true;
	recordbaby = false;

	ofSetVerticalSync(true);

	int num = 1500;
	p.assign(num, Particle());
	currentMode = PARTICLE_MODE_ATTRACT;

	currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";

	resetParticles();
}

//--------------------------------------------------------------
void ofApp::resetParticles()
{

	//these are the attraction points used in the fourth demo
	attractPoints.clear();
	for (int i = 0; i < 4; i++)
	{
		attractPoints.push_back(glm::vec3(ofMap(i, 0, 4, 100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100), 0));
	}

	attractPointsWithMovement = attractPoints;

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].setMode(currentMode);
		p[i].setAttractPoints(&attractPointsWithMovement);
		;
		p[i].reset();
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// the updating boolean decides if the particles move or not.
	if (updating)
	{
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].setMode(currentMode);
			p[i].update();
		}

		//lets add a bit of movement to the attract points
		for (unsigned int i = 0; i < attractPointsWithMovement.size(); i++)
		{
			attractPointsWithMovement[i].x = attractPoints[i].x + ofSignedNoise(i * 10, ofGetElapsedTimef() * 0.7) * 12.0;
			attractPointsWithMovement[i].y = attractPoints[i].y + ofSignedNoise(i * -10, ofGetElapsedTimef() * 0.7) * 12.0;
		}
	}

	if (replaybaby)
	{
		count++;

		if (count == 100 && RecordKey < record.size())
		{
			count = 0;
			keyPressed(record[RecordKey]);
			RecordKey++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofBackgroundGradient(ofColor(0, 0, 255), ofColor(10, 10, 10));

	for (unsigned int i = 0; i < p.size(); i++)
	{
		p[i].draw();
	}

	ofSetColor(190);
	if (currentMode == PARTICLE_MODE_NEAREST_POINTS)
	{
		for (unsigned int i = 0; i < attractPoints.size(); i++)
		{
			ofNoFill();
			ofDrawCircle(attractPointsWithMovement[i], 10);
			ofFill();
			ofDrawCircle(attractPointsWithMovement[i], 4);
		}
	}
	if (!recordbaby || cancel == true)
	{

		ofSetColor(230);
		ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
	}
	else if (recordbaby)
	{
		ofSetColor(255, 0, 0);
		ofDrawCircle(ofGetWidth() - 35, 35, 30);
		ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
	}

	if (replaybaby)
	{

		ofSetColor(0, 255, 0);
		ofDrawTriangle(ofGetWidth() - (40 + 70), 50, ofGetWidth() - (40 + 70), 10, ofGetWidth() - 70, 30);
		ofDrawBitmapString(currentModeStr + "\n\nSpacebar to reset. \nKeys 1-4 to change mode.", 10, 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == '1')
	{
		currentMode = PARTICLE_MODE_ATTRACT;
		currentModeStr = "1 - PARTICLE_MODE_ATTRACT: attracts to mouse";
	}
	if (key == '2')
	{
		currentMode = PARTICLE_MODE_REPEL;
		currentModeStr = "2 - PARTICLE_MODE_REPEL: repels from mouse";
	}
	if (key == '3')
	{
		currentMode = PARTICLE_MODE_NEAREST_POINTS;
		currentModeStr = "3 - PARTICLE_MODE_NEAREST_POINTS: hold 'f' to disable force";
	}
	if (key == '4')
	{
		currentMode = PARTICLE_MODE_NOISE;
		currentModeStr = "4 - PARTICLE_MODE_NOISE: snow particle simulation";
		resetParticles();
	}

	if (key == ' ')
	{
		resetParticles();
	}

	if (key == 'a' || key == 'A')
	{
		updating = !updating;
	}

	if (key == 'd' || key == 'D')
	{
		currentModeStr = "Double size Particles";
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].doublesize();
		}
	}
	if (key == 'm' || key == 'M')
	{
		currentModeStr = "Halve size of Particles";
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].halvesize();
		}
	}

	if (key == 't' || key == 'T')
	{
		currentModeStr = "double the velocity";
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].doubleVelocity();
		}
	}

	if (key == 's' || key == 'S')
	{
		currentModeStr = "Halve  the velocity";
		for (unsigned int i = 0; i < p.size(); i++)
		{
			p[i].halveVelocity();
		}
	}
	if (key == 'r' || key == 'R')
	{
		cancel = false;
		count = 0;
		RecordKey = 1;
		currentModeStr = "We are Recording babyyyyyyyyyyyyyyyyy";
		recordbaby = true;
	}

	if (key == 'p' || key == 'P')
	{
		resetParticles();
		updating = true;
		cancel = false;
		recordbaby = false;
		currentModeStr = "Replaying babyyyyyyyyyyyyyyyyyyy";
		replaybaby = true;
	}

	if (recordbaby)
	{
		record.push_back(key);
	}

	if (key == 'c' || key == 'C')
	{
		record.clear();
		updating = true;
		replaybaby = false;
		cancel = true;
		currentModeStr = "Canceled";
		resetParticles();
	}
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}