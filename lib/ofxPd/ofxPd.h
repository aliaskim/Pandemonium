//
//  ofxPd.h
//  audioOutputExample
//
//  Created by Marek Bereza on 19/04/2011.
//
#pragma once

#include <string>
#include <vector>
#include "Slots.h"
#include "Mutex.h"
using namespace std;
/**
 * TODO:
 * make different patches receive the same message name from different inputs
 */

class ofxPd {
    
public:
    ofxPd();
	~ofxPd();
	
    // this must be called before anything else!
    static void setup(int samplerate);

    // need to give this an absolute path to the file
    bool open(string patchFile);
    
	void close();
	
	// processing is always in stereo for now, numFrames is how
	// many stereo samples we're using.
	void process(float *inputs, float *outputs, int numFrames);
	
	
	void sendFloat(string messageName, float value);
	void sendBang(string messageName);	
	void sendMidiNote(int noteNum, int velocity, int blockOffset = 0);
	void sendMidiControlChange(int ctlNum, int value);
	void sendMidiBend(int value);
	void sendMidiProgramChange(int program);
	void sendMidiPolyTouch(int noteNum, int value);
	void sendMidiAfterTouch(int value);
	
	

	
private:
    
	bool opened;
	
    // how many 64 sample chunks to process at one time.
    string patchFile;
    string folder;
	string file;
	
	// must be a multiple of 64!
	static void setBufferSize(int bufferSize);
    
    // static variables
    static int bufferSize;
    static bool pdInitialized;
	
	// libpd pointer to the patch
	void *patchPointer;
	
	// the patch's $0 value - a unique identifier for pd
	int dollarZero;
	
	// string representation with an appended '-'
	// cached for speed
	string dollarZeroString;
	
	// string reference to the 
	// patch's switch~ receive.
	string uid;
	
	// this is the plugin's unique midi channel
	int midiChannel;
	
	// this creates a new file in the same folder
	// as the original patch, but it adds the 
	// switch~ code and a unique filename.
	void createUniquePatch();

	
	string parseFileToString(string filePath);
	void processForConnects(string &line);
	void stringToFile(string filePath, string contents);
	vector<string> params;
	
	// to allow us to have multiple instances of effects
	// and instruments, we need to remap the midi channels
	// so each instance has its own.
	void renameMidiChannels(string &data);
	static Slots midiChannels;

	
};
