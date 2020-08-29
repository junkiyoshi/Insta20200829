#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_MULTIPLY);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 35, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<ofColor> color_list{ ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255) };
	vector<glm::vec2> location_list;
	for (int x = 120; x < 720; x += 240) {

		for (int y = 120; y < 720; y += 240) {

			location_list.push_back(glm::vec2(x, y));
		}
	}

	string word = "ROTATE";
	auto path_list = font.getStringAsPoints(word, true, false);
	for (auto& path : path_list) {

		auto& outline = path.getOutline();

		for (int i = 0; i < color_list.size(); i++) {

			ofSetColor(color_list[i]);
			for (int k = 0; k < location_list.size(); k++) {

				auto angle_z = ofMap(ofNoise(location_list[k].x, location_list[k].y, i * 0.02 + ofGetFrameNum() * 0.01), 0, 1, -PI * 2, PI * 2);

				ofPushMatrix();
				ofTranslate(location_list[k]);

				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getVertices();
					for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

						auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 0);

						auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));
						location = glm::vec4(location, 0) * rotation_z;

						ofVertex(location);
					}
				}
				ofEndShape(true);

				ofPopMatrix();
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}