#ifndef _APPLICATION_h
#define _APPLICATION_h
#include <Pch/Pch.h>
#include "Input.h"
#include "StateManager.h"

class Application {

public:
	Application();
	~Application();
	
	bool init();
	void run();


private:
	void initGraphics();
	
	GLFWwindow* m_window;
	Input* m_input;
	StateManager* m_stateManager;
	bool m_vsync;
	bool initialFrame;
};




#endif
