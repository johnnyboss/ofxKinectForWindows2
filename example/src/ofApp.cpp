#include "ofApp.h"

int previewWidth = 640;
int previewHeight = 480;

//--------------------------------------------------------------
void ofApp::setup(){
	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodySource();
	kinect.initBodyIndexSource();

	ofSetWindowShape(previewWidth * 2, previewHeight * 2);
}

//--------------------------------------------------------------
void ofApp::update(){
	kinect.update();
	ofFloatPixels refPixels = kinect.getBodyIndexSource()->getPixels();
	int bla = 0;
	unsigned short* rawdepth = kinect.getDepthSource()->getPixels();

	ofPixels pixels = kinect.getDepthSource()->getPixels(); ;// kinect.getDepthSource()->getDepthToWorldMap();
	
	float avgDist = 0;
	int nSamples = 0;
	if (pixels.size() > 0 && refPixels.size() > 0)
	{
		for (int i = 0; i < 512; i++)
		{
			for (int j = 0; j < 424; j++)
			{
				int index = j * 512 + i;
				//cout << refPixel << endl;
				if (refPixels.getColor(index) == ofFloatColor(0,0,0))
				{
					avgDist += pixels[index];
					nSamples++;
				}
			}
		}

		cout << "AVERAGE " << nSamples << endl;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	kinect.getDepthSource()->draw(0, 0, previewWidth, previewHeight);  // note that the depth texture is RAW so may appear dark
	
	// Color is at 1920x1080 instead of 512x424 so we should fix aspect ratio
	float colorHeight = previewWidth * (kinect.getColorSource()->getHeight() / kinect.getColorSource()->getWidth());
	float colorTop = (previewHeight - colorHeight) / 2.0;
	kinect.getColorSource()->draw(previewWidth, 0 + colorTop, previewWidth, colorHeight);
	kinect.getBodySource()->drawProjected(previewWidth, 0 + colorTop, previewWidth, colorHeight);
	
	kinect.getInfraredSource()->draw(0, previewHeight, previewWidth, previewHeight);
	
	kinect.getBodyIndexSource()->draw(previewWidth, previewHeight, previewWidth, previewHeight);
	kinect.getBodySource()->drawProjected(previewWidth, previewHeight, previewWidth, previewHeight, ofxKFW2::ProjectionCoordinates::DepthCamera);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
