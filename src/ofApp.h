#pragma once

#include "ofMain.h"
#include "conway/conway.h"

class ofApp : public ofBaseApp{
public:
	void setup();
	void draw();
	void drawCell(conway::Cell c);

	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseReleased(int x, int y, int button);
		
private:
	const size_t kCellSize = 10;

	conway::Conway<2>* conway_;
	conway::Cell* hover_;
};
