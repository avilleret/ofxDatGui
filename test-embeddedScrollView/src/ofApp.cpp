#include "ofApp.h"

void ofApp::setup()
{
    ofSetWindowShape(1920, 1080);
    ofSetWindowPosition(ofGetScreenWidth()/2 - ofGetWidth()/2, 0);

    width = 540;
    theme = new ofxDatGuiThemeMidnight();

// create a button to attach items to the scroll view //
    addItem = new ofxDatGuiButton("click to add item");
    addItem->setStripeVisible(false);
    //addItem->setWidth(width);
    addItem->setPosition(ofGetWidth()/2 - addItem->getWidth()/2, 240);
    addItem->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    addItem->onButtonEvent(this, &ofApp::onAddNewItemButtonClick);

// create a scroll view that displays eight items at a time //
    // vector<string> btns = { "button 1", "button 2", "button 3", "button 4"};
    view = new ofxDatGuiScrollView("ScrollView #1", 8);
    view->setWidth(width);
    view->setPosition(ofGetWidth()/2, ofGetHeight()/2);
    view->onScrollViewEvent(this, &ofApp::onScrollViewEvent);

    // folder->attachItem(view);
    nestedview = new ofxDatGuiScrollView("Scrollview #2",4);
    //nestedview->onScrollViewEvent(this, &ofApp::onScrollViewEvent);
    //view->onButtonEvent(this, &ofApp::onButtonEvent);


// add a button to allow us to clear the scroll view out //
    clearAll = new ofxDatGuiButton("click to clear all items");
    clearAll->setStripeVisible(false);
    //clearAll->setWidth(width);
    clearAll->setPosition(ofGetWidth()/2 - clearAll->getWidth()/2, nestedview->getY() + nestedview->getHeight() + 1);
    clearAll->setLabelAlignment(ofxDatGuiAlignment::CENTER);
    clearAll->onButtonEvent(this, &ofApp::onClearAllButtonClick);

// add a few items for testing //
    for(int i=0; i<12; i++) {
        nestedview->add("item nested " + ofToString(nestedview->getNumItems() + 1));
        view->add("item " + ofToString(view->getNumItems() + 1));
    }
    addItem->setLabel("click to add item - " + ofToString(nestedview->getNumItems()) + " items");

    folder = new ofxDatGuiFolder("folder");
    folder->attachItem(addItem);
    folder->attachItem(nestedview);
    folder->attachItem(clearAll);

    vector<string> opts = {"coucou", "blabl", "ça va ?"};
    folder->addDropdown("select option", opts);

    gui = new ofxDatGui(ofxDatGuiAnchor::TOP_RIGHT);
    gui->addHeader("--- drag me to reposition ---");
    ofxDatGuiScrollView* guiview = gui->addScrollView("myScroll", 8);
    for (int i=0; i<12; i++){
        guiview->add("guiview item" + to_string(i));
    }
}

void ofApp::update()
{
    view->update();
    //addItem->update();
    //clearAll->update();
    folder->update();
}

void ofApp::draw()
{
    view->draw();
    //addItem->draw();
    //clearAll->draw();
    folder->draw();
}

void ofApp::onScrollViewEvent(ofxDatGuiScrollViewEvent e)
{
    cout << e.target->getLabel() << " [index " << e.target->getIndex() << "] selected in [" << e.parent->getName() << "]" << endl;
}

void ofApp::onAddNewItemButtonClick(ofxDatGuiButtonEvent e)
{
    nestedview->add("item " + ofToString(nestedview->getNumItems() + 1));
    addItem->setLabel("click to add item - " + ofToString(nestedview->getNumItems()) + " items");
}

void ofApp::onClearAllButtonClick(ofxDatGuiButtonEvent e)
{
    nestedview->clear();
    addItem->setLabel("click to add item");
}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e)
{
    cout << "button event: " << e.target->getName();
}

