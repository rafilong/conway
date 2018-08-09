#include "ofApp.h"

void ofApp::setup() {
	conway_ = new conway::Conway<2>(ofGetWidth() / kCellSize);
	hover_ = conway_->Get({ 0, 0 });

	ofSetupScreen();
}

void ofApp::draw() {
	ofSetColor(100, 100, 255);
	drawCell(*hover_);

	ofSetColor(0, 0, 0);
	for (conway::Cell* c : conway_->GetAlive()) {
		drawCell(*c);
	}
}

void ofApp::drawCell(conway::Cell c) {
	vector<size_t> coords = c.coords;
	int x = coords[0] * kCellSize;
	int y = coords[1] * kCellSize;
	ofDrawRectangle(x, y, kCellSize, kCellSize);
}

void ofApp::keyReleased(int key) {
	if (key == 'q') {
		std::exit(0);
	} else {
		conway_->Next();
	}
}

void ofApp::mouseMoved(int x, int y ) {
	vector<size_t> coords(2);
	coords[0] = x / kCellSize;
	coords[1] = y / kCellSize;
	hover_ = conway_->Get(coords);
}

void ofApp::mouseReleased(int x, int y, int button) {
	vector<size_t> coords(2);
	coords[0] = x / kCellSize;
	coords[1] = y / kCellSize;
	conway_->Set(coords, true);
}
