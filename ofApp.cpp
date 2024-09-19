#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	if (ofGetFrameNum() % 100 < 50) {

		this->noise_span = ofMap(ofGetFrameNum() % 100, 0, 50, 0.02, 0.00005);
	}
	else {

		this->noise_span = ofMap(ofGetFrameNum() % 100, 51, 100, 0.00005, 0.02);
	}

	float span = 1;
	ofColor color;
	for (float x = ofGetWindowWidth() * -0.5 + 30 ; x <= ofGetWindowWidth() * 0.5 - span - 30; x += span) {

		for (float y = ofGetWindowHeight() * -0.5 + 30; y <= ofGetWindowHeight() * 0.5 - span - 30 ; y += span) {

			this->mesh.addVertex(glm::vec3(x, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y, 0));
			this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
			this->mesh.addVertex(glm::vec3(x, y + span, 0));

			for (int i = this->mesh.getNumVertices() - 4; i < this->mesh.getNumVertices(); i++) {

				auto noise_location = this->mesh.getVertex(i) * this->noise_span;
				auto noise_value = ofMap(ofNoise(noise_location.x, noise_location.y, ofGetFrameNum() * 0.06), 0, 1, 0, 4);
				int int_noise_value = noise_value;
				float param = noise_value - int_noise_value;
				param = abs(param - 0.5);
				auto alpha = param < 0.3 ? ofMap(param, 0, 0.3, 255, 0) : 0;

				color.setHsb(ofMap(int_noise_value, 0, 4, 0, 255), 200, 255);
				this->mesh.addColor(ofColor(color, alpha));
			}

			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
			this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 3); this->mesh.addIndex(this->mesh.getNumVertices() - 4);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	this->mesh.draw();

	/*
	int start = 50 + 18;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}