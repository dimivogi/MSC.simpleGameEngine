// main.cpp : Defines the entry point for the console application.
//
#pragma		comment(lib,"Game Engine.lib")

#include	<cstdlib>
#include	<stdio.h>
#include	<tchar.h>
#include	"GameEngine.h"
#include	"directxWindow.h"
#include	"openglWindow.h"
#include	"GameManager.h"

using		namespace GameEngine;



int WINAPI	WinMain( HINSTANCE hInstance , HINSTANCE hpRevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	Message				init_message(3,1);
	wstring				filename(L"testlog.txt");
	ErrorManager*		Log = ErrorManager::GetErrorManager();



	// create the message that holds out initialization parameters
	init_message.data(0,0);
	init_message.data(1,10);
	init_message.data(2,10);
	init_message.pointer(0,&filename);
	// call the init function
	InitialRegistration();
	// trigger the init event
	TriggerEvent(GAME_ENGINE_INIT,init_message);
	// toggle message boxs
	TriggerEvent(GAME_ENGINE_ERROR_DISPLAY_MESSAGE);
	
	try
	{
		hpRevInstance; lpCmdLine; nCmdShow;
		GameManager		_manager;
		DirectXWindow	_window(hInstance,&_manager);
		OpenGLWindow	_window2(hInstance,&_manager);



		// open 2 windows, a directx one with minimal functionality
		_window.set_size(500,500);
		_window.SetInitialPosition(695,10);
		_window.Create(L"DirectX");
		// and a opengl one with full game implementation
		_window2.set_size(500,500);
		_window2.SetInitialPosition(1205,10);
		_window2.Create(L"OpenGL");
		
		// initialize the game manager
		_manager.init_once();
		// initialize kinect
		_manager.init_kinect();
		// enter the main loop
		MainLoop();
	}
	catch( ErrorException& e )
	{
		// log any exceptions
		Log->Output(L"****** ERROR ******");
		Log->LogException(e);
		Log->Output(L"*******************");
		// exit
		TriggerEvent(GAME_ENGINE_CLOSE);
	}
}