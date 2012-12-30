#include	"InputManager.h"
#include	"..\Error Manager\ErrorException.h"
#include	<iostream>
#include	<MSR_NuiApi.h>

using		namespace std;
using		namespace GameEngine;



InputManager	InputManager::_input_manager;


InputManager::InputManager()	:	
	_next_skeleton_event(NULL) , _stop_kinect_event(NULL) , 	
	_kinect_thread_handle(NULL) , _depth_stream(NULL), _kinect_init(false)	{};
InputManager::~InputManager()	{};

void	InputManager::_initialise_kinect()
{
	HRESULT	hr;



	// Initialise event handlers
	// Params: security descriptor (NULL), manually reset event? (TRUE),
	// initial state? (FALSE), name (NULL)
	this->_next_skeleton_event = CreateEvent(NULL, TRUE, FALSE, NULL);
	this->_stop_kinect_event = CreateEvent(NULL, FALSE, FALSE, NULL);


	hr = NuiInitialize(	// Initialise skeleton information
						NUI_INITIALIZE_FLAG_USES_SKELETON);
	if ( FAILED(hr) )
		throw ErrorException(GAME_ENGINE_ERROR_CODE_INPUTMANAGER_KINECT_INITIALIZE,L"Kinect could not be initialized.",__WFILE__,__LINE__);


	hr = NuiSkeletonTrackingEnable(this->_next_skeleton_event,0);
	if ( FAILED(hr) )
	{
		NuiShutdown();
		throw ErrorException(GAME_ENGINE_ERROR_CODE_INPUTMANAGER_KINECT_SKELETON_INITIALIZE,L"Kinect skeleton tracking could not be enabled.",__WFILE__,__LINE__);
	}


	this->_kinect_thread_handle = CreateThread(NULL,0,this->_kinect_thread_process,this,0,NULL);
	if ( this->_kinect_thread_handle == NULL )
	{
		CloseHandle(this->_next_skeleton_event);
		NuiShutdown();
		throw ErrorException(GAME_ENGINE_ERROR_CODE_INPUT_MANAGER_KINECT_THREAD_INITIALIZE,L"Kinect thread could not be initialised.",__WFILE__,__LINE__);
	}


	this->_kinect_init = true;
};

void	InputManager::_close_kinect()
{
	if ( this->_kinect_init )
	{
		SetEvent(this->_stop_kinect_event);
		WaitForSingleObject(this->_kinect_thread_handle,INFINITE);
		CloseHandle(this->_kinect_thread_handle);

		CloseHandle(this->_next_skeleton_event);

		NuiShutdown();
		this->_kinect_init = false;
	}
};

void	InputManager::_skeleton_event_handler() const
{
	static Message		parameters(1,1);
	NUI_SKELETON_FRAME	skeleton_frames;
	Skeleton			skeleton[NUI_SKELETON_COUNT];
	HRESULT				hr = NuiSkeletonGetNextFrame(0,&skeleton_frames);
	bool				found = false;


	if ( !FAILED(hr) )
	{
		for ( unsigned int i = 0;  i < NUI_SKELETON_COUNT;  ++i )
		{
			if ( skeleton_frames.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED )
				found = true;
		}

		if ( found ) 
		{
			NuiTransformSmooth(&skeleton_frames,NULL);

			for ( unsigned int i = 0;  i < NUI_SKELETON_COUNT;  ++i )
			{
				for ( unsigned int j = 0;  j < NUI_SKELETON_POSITION_COUNT;  ++j )
				{
					skeleton[i]._points[j]._x = skeleton_frames.SkeletonData[i].SkeletonPositions[j].x;
					skeleton[i]._points[j]._y = skeleton_frames.SkeletonData[i].SkeletonPositions[j].y;
				}

				skeleton[i]._skeleton_no = i+1;

				if ( skeleton_frames.SkeletonData[i].eTrackingState == NUI_SKELETON_TRACKED )
					skeleton[i]._used = true;
				else
					skeleton[i]._used = false;
			}

			parameters.data(0,NUI_SKELETON_COUNT);
			parameters.pointer(0,reinterpret_cast<void*>(&skeleton));
			TriggerEvent(GAME_ENGINE_KINECT_SKELETON,parameters);
		}
	}
};


DWORD WINAPI		InputManager::_kinect_thread_process( LPVOID pParam )
{
	InputManager*	manager = static_cast<InputManager*>(pParam);
	HANDLE			events[2];
	int				event_id;
	bool			iterate = true;



	events[0] = manager->_stop_kinect_event;
	events[1] = manager->_next_skeleton_event;
	while( iterate )
	{
		event_id = WaitForMultipleObjects(sizeof(events)/sizeof(events[0]),events,FALSE,100);

		
		if ( event_id == 0 )
			iterate = false;
		else
		{
			switch ( event_id )
			{
				case 1:
						manager->_skeleton_event_handler();
						break;
			}
		}
	}


	return 0;
};


InputManager*	InputManager::GetInputManager()	{ return &_input_manager; };
void	InputManager::Create()
{
	this->RegisterEvent(GAME_ENGINE_RAW_KEY_UP);
	this->RegisterEvent(GAME_ENGINE_RAW_KEY_DOWN);
	this->RegisterEvent(GAME_ENGINE_RAW_MOUSE_MOVE);
	this->RegisterEvent(GAME_ENGINE_RAW_VERTICAL_MOUSE_WHEEL);
	this->RegisterEvent(GAME_ENGINE_RAW_HORIZONTAL_MOUSE_WHEEL);
	this->RegisterEvent(GAME_ENGINE_CLOSE);
	this->RegisterEvent(GAME_ENGINE_INIT_KINECT);
	this->RegisterEvent(GAME_ENGINE_CLOSE_KINECT);
};

void	InputManager::OnEvent( const unsigned int message , const Message& parameters )
{
	Message	parsed_parameters(parameters);



	if ( message == GAME_ENGINE_RAW_KEY_UP )
	{
		parsed_parameters.data(0,0.0);

		switch ( static_cast<unsigned int>(parameters.data(0)) )
		{
			case VK_LBUTTON:	
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_MOUSE_BUTTON,parsed_parameters);
								break;

			case VK_RBUTTON:	
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_MOUSE_BUTTON,parsed_parameters);
								break;

			case VK_CANCEL:		
								TriggerEvent(GAME_ENGINE_KEY_UP_CANCEL,parsed_parameters);
								break;

			case VK_MBUTTON:	
								TriggerEvent(GAME_ENGINE_KEY_UP_MIDDLE_MOUSE_BUTTON,parsed_parameters);
								break;

			case VK_BACK:		
								TriggerEvent(GAME_ENGINE_KEY_UP_BACKSPACE,parsed_parameters);
								break;

			case VK_TAB:		
								TriggerEvent(GAME_ENGINE_KEY_UP_TAB,parsed_parameters);
								break;

			case VK_CLEAR:		
								TriggerEvent(GAME_ENGINE_KEY_UP_CLEAR,parsed_parameters);
								break;

			case VK_OEM_CLEAR:	
								TriggerEvent(GAME_ENGINE_KEY_UP_CLEAR,parsed_parameters);
								break;

			case VK_RETURN:		
								TriggerEvent(GAME_ENGINE_KEY_UP_ENTER,parsed_parameters);
								break;

			case VK_SHIFT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_SHIFT,parsed_parameters);
								break;

			case VK_LSHIFT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_SHIFT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_SHIFT,parsed_parameters);
								break;

			case VK_RSHIFT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_SHIFT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_SHIFT,parsed_parameters);
								break;

			case VK_CONTROL:	
								TriggerEvent(GAME_ENGINE_KEY_UP_CONTROL,parsed_parameters);
								break;

			case VK_LCONTROL:	
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_CONTROL,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_CONTROL,parsed_parameters);
								break;

			case VK_RCONTROL:	
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_CONTROL,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_CONTROL,parsed_parameters);
								break;

			case VK_MENU:		
								TriggerEvent(GAME_ENGINE_KEY_UP_ALT,parsed_parameters);
								break;

			case VK_LMENU:		
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_ALT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_ALT,parsed_parameters);
								break;

			case VK_RMENU:		
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_ALT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_ALT,parsed_parameters);
								break;

			case VK_PAUSE:		
								TriggerEvent(GAME_ENGINE_KEY_UP_PAUSE,parsed_parameters);
								break;

			case VK_CAPITAL:	
								TriggerEvent(GAME_ENGINE_KEY_UP_CAPS_LOCK,parsed_parameters);
								break;

			case VK_ESCAPE:		
								TriggerEvent(GAME_ENGINE_KEY_UP_ESCAPE,parsed_parameters);
								break;

			case VK_SPACE:		
								TriggerEvent(GAME_ENGINE_KEY_UP_SPACE,parsed_parameters);
								break;

			case VK_PRIOR:		
								TriggerEvent(GAME_ENGINE_KEY_UP_PAGE_UP,parsed_parameters);
								break;

			case VK_NEXT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_PAGE_DOWN,parsed_parameters);
								break;

			case VK_END:		
								TriggerEvent(GAME_ENGINE_KEY_UP_END,parsed_parameters);
								break;

			case VK_HOME:		
								TriggerEvent(GAME_ENGINE_KEY_UP_HOME,parsed_parameters);
								break;

			case VK_LEFT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_ARROW,parsed_parameters);
								break;

			case VK_UP:			
								TriggerEvent(GAME_ENGINE_KEY_UP_UP_ARROW,parsed_parameters);
								break;

			case VK_RIGHT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_ARROW,parsed_parameters);
								break;

			case VK_DOWN:		
								TriggerEvent(GAME_ENGINE_KEY_UP_DOWN_ARROW,parsed_parameters);
								break;

			case VK_SELECT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_SELECT,parsed_parameters);
								break;

			case VK_EXECUTE:	
								TriggerEvent(GAME_ENGINE_KEY_UP_EXECUTE,parsed_parameters);
								break;

			case VK_SNAPSHOT:	
								TriggerEvent(GAME_ENGINE_KEY_UP_PRINT_SCREEN,parsed_parameters);
								break;

			case VK_INSERT:		
								TriggerEvent(GAME_ENGINE_KEY_UP_INSERT,parsed_parameters);
								break;

			case VK_DELETE:		
								TriggerEvent(GAME_ENGINE_KEY_UP_DELETE,parsed_parameters);
								break;

			case VK_HELP:		
								TriggerEvent(GAME_ENGINE_KEY_UP_HELP,parsed_parameters);
								break;

			case VK_LWIN:		
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_WINDOWS,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_WINDOWS,parsed_parameters);
								break;

			case VK_RWIN:		
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_WINDOWS,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_WINDOWS,parsed_parameters);
								break;

			case VK_APPS:		
								TriggerEvent(GAME_ENGINE_KEY_UP_APPLICATION,parsed_parameters);
								break;

			case VK_NUMPAD0:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_0,parsed_parameters);
								break;

			case VK_NUMPAD1:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_1,parsed_parameters);
								break;

			case VK_NUMPAD2:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_2,parsed_parameters);
								break;

			case VK_NUMPAD3:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_3,parsed_parameters);
								break;

			case VK_NUMPAD4:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_4,parsed_parameters);
								break;

			case VK_NUMPAD5:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_5,parsed_parameters);
								break;

			case VK_NUMPAD6:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_6,parsed_parameters);
								break;

			case VK_NUMPAD7:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_7,parsed_parameters);
								break;

			case VK_NUMPAD8:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_8,parsed_parameters);
								break;

			case VK_NUMPAD9:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_9,parsed_parameters);
								break;

			case VK_MULTIPLY:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_MULTIPLY,parsed_parameters);
								break;

			case VK_ADD:		
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_ADD,parsed_parameters);
								break;

			case VK_SEPARATOR:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_SEPARATOR,parsed_parameters);
								break;

			case VK_SUBTRACT:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_SUBTRACT,parsed_parameters);
								break;

			case VK_DECIMAL:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_DECIMAL,parsed_parameters);
								break;

			case VK_DIVIDE:		
								TriggerEvent(GAME_ENGINE_KEY_UP_NUMPAD_DIVIDE,parsed_parameters);
								break;

			case VK_F1:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F1,parsed_parameters);
								break;

			case VK_F2:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F2,parsed_parameters);
								break;

			case VK_F3:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F3,parsed_parameters);
								break;

			case VK_F4:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F4,parsed_parameters);
								break;

			case VK_F5:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F5,parsed_parameters);
								break;

			case VK_F6:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F6,parsed_parameters);
								break;

			case VK_F7:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F7,parsed_parameters);
								break;

			case VK_F8:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F8,parsed_parameters);
								break;

			case VK_F9:			
								TriggerEvent(GAME_ENGINE_KEY_UP_F9,parsed_parameters);
								break;

			case VK_F10:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F10,parsed_parameters);
								break;

			case VK_F11:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F11,parsed_parameters);
								break;

			case VK_F12:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F12,parsed_parameters);
								break;

			case VK_F13:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F13,parsed_parameters);
								break;

			case VK_F14:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F14,parsed_parameters);
								break;

			case VK_F15:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F15,parsed_parameters);
								break;

			case VK_F16:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F16,parsed_parameters);
								break;

			case VK_F17:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F17,parsed_parameters);
								break;

			case VK_F18:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F18,parsed_parameters);
								break;

			case VK_F19:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F19,parsed_parameters);
								break;

			case VK_F20:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F20,parsed_parameters);
								break;

			case VK_F21:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F21,parsed_parameters);
								break;

			case VK_F22:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F22,parsed_parameters);
								break;

			case VK_F23:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F23,parsed_parameters);
								break;

			case VK_F24:		
								TriggerEvent(GAME_ENGINE_KEY_UP_F24,parsed_parameters);
								break;

			case VK_NUMLOCK:	
								TriggerEvent(GAME_ENGINE_KEY_UP_NUM_LOCK,parsed_parameters);
								break;

			case VK_SCROLL:		
								TriggerEvent(GAME_ENGINE_KEY_UP_SCROLL_LOCK,parsed_parameters);
								break;

			case VK_ATTN:		
								TriggerEvent(GAME_ENGINE_KEY_UP_ATTN,parsed_parameters);
								break;

			case VK_CRSEL:		
								TriggerEvent(GAME_ENGINE_KEY_UP_CRSEL,parsed_parameters);
								break;

			case VK_EXSEL:		
								TriggerEvent(GAME_ENGINE_KEY_UP_EXSEL,parsed_parameters);
								break;

			case VK_EREOF:		
								TriggerEvent(GAME_ENGINE_KEY_UP_EREOF,parsed_parameters);
								break;

			case VK_PLAY:		
								TriggerEvent(GAME_ENGINE_KEY_UP_PLAY,parsed_parameters);
								break;

			case VK_ZOOM:		
								TriggerEvent(GAME_ENGINE_KEY_UP_ZOOM,parsed_parameters);
								break;

			case VK_PA1:		
								TriggerEvent(GAME_ENGINE_KEY_UP_PA1,parsed_parameters);
								break;

			case VK_OEM_1:		
								TriggerEvent(GAME_ENGINE_KEY_UP_SEMICOLON,parsed_parameters);
								break;

			case VK_OEM_PLUS:	
								TriggerEvent(GAME_ENGINE_KEY_UP_PLUS,parsed_parameters);
								break;

			case VK_OEM_COMMA:	
								TriggerEvent(GAME_ENGINE_KEY_UP_COMMA,parsed_parameters);
								break;

			case VK_OEM_MINUS:	
								TriggerEvent(GAME_ENGINE_KEY_UP_MINUS,parsed_parameters);
								break;

			case VK_OEM_PERIOD:	
								TriggerEvent(GAME_ENGINE_KEY_UP_PERIOD,parsed_parameters);
								break;

			case VK_OEM_2:		
								TriggerEvent(GAME_ENGINE_KEY_UP_DIVIDE,parsed_parameters);
								break;

			case VK_OEM_3:		
								TriggerEvent(GAME_ENGINE_KEY_UP_TILDE,parsed_parameters);
								break;

			case VK_OEM_4:		
								TriggerEvent(GAME_ENGINE_KEY_UP_LEFT_BRACKET,parsed_parameters);
								break;

			case VK_OEM_5:		
								TriggerEvent(GAME_ENGINE_KEY_UP_SLASH,parsed_parameters);
								break;

			case VK_OEM_6:		
								TriggerEvent(GAME_ENGINE_KEY_UP_RIGHT_BRACKET,parsed_parameters);
								break;

			case VK_OEM_7:		
								TriggerEvent(GAME_ENGINE_KEY_UP_QUOTE,parsed_parameters);
								break;

			case '0':			
								TriggerEvent(GAME_ENGINE_KEY_UP_0,parsed_parameters);
								break;

			case '1':			
								TriggerEvent(GAME_ENGINE_KEY_UP_1,parsed_parameters);
								break;

			case '2':			
								TriggerEvent(GAME_ENGINE_KEY_UP_2,parsed_parameters);
								break;

			case '3':			
								TriggerEvent(GAME_ENGINE_KEY_UP_3,parsed_parameters);
								break;

			case '4':			
								TriggerEvent(GAME_ENGINE_KEY_UP_4,parsed_parameters);
								break;

			case '5':			
								TriggerEvent(GAME_ENGINE_KEY_UP_5,parsed_parameters);
								break;

			case '6':			
								TriggerEvent(GAME_ENGINE_KEY_UP_6,parsed_parameters);
								break;

			case '7':			
								TriggerEvent(GAME_ENGINE_KEY_UP_7,parsed_parameters);
								break;

			case '8':			
								TriggerEvent(GAME_ENGINE_KEY_UP_8,parsed_parameters);
								break;

			case '9':			
								TriggerEvent(GAME_ENGINE_KEY_UP_9,parsed_parameters);
								break;

			case 'A':			
								TriggerEvent(GAME_ENGINE_KEY_UP_A,parsed_parameters);
								break;

			case 'B':			
								TriggerEvent(GAME_ENGINE_KEY_UP_B,parsed_parameters);
								break;

			case 'C':			
								TriggerEvent(GAME_ENGINE_KEY_UP_C,parsed_parameters);
								break;

			case 'D':			
								TriggerEvent(GAME_ENGINE_KEY_UP_D,parsed_parameters);
								break;

			case 'E':			
								TriggerEvent(GAME_ENGINE_KEY_UP_E,parsed_parameters);
								break;

			case 'F':			
								TriggerEvent(GAME_ENGINE_KEY_UP_F,parsed_parameters);
								break;

			case 'G':			
								TriggerEvent(GAME_ENGINE_KEY_UP_G,parsed_parameters);
								break;

			case 'H':			
								TriggerEvent(GAME_ENGINE_KEY_UP_H,parsed_parameters);
								break;

			case 'I':			
								TriggerEvent(GAME_ENGINE_KEY_UP_I,parsed_parameters);
								break;

			case 'J':			
								TriggerEvent(GAME_ENGINE_KEY_UP_J,parsed_parameters);
								break;

			case 'K':			
								TriggerEvent(GAME_ENGINE_KEY_UP_K,parsed_parameters);
								break;

			case 'L':			
								TriggerEvent(GAME_ENGINE_KEY_UP_L,parsed_parameters);
								break;

			case 'M':			
								TriggerEvent(GAME_ENGINE_KEY_UP_M,parsed_parameters);
								break;

			case 'N':			
								TriggerEvent(GAME_ENGINE_KEY_UP_N,parsed_parameters);
								break;

			case 'O':			
								TriggerEvent(GAME_ENGINE_KEY_UP_O,parsed_parameters);
								break;

			case 'P':			
								TriggerEvent(GAME_ENGINE_KEY_UP_P,parsed_parameters);
								break;

			case 'Q':			
								TriggerEvent(GAME_ENGINE_KEY_UP_Q,parsed_parameters);
								break;

			case 'R':			
								TriggerEvent(GAME_ENGINE_KEY_UP_R,parsed_parameters);
								break;

			case 'S':			
								TriggerEvent(GAME_ENGINE_KEY_UP_S,parsed_parameters);
								break;

			case 'T':			
								TriggerEvent(GAME_ENGINE_KEY_UP_T,parsed_parameters);
								break;

			case 'U':			
								TriggerEvent(GAME_ENGINE_KEY_UP_U,parsed_parameters);
								break;

			case 'V':			
								TriggerEvent(GAME_ENGINE_KEY_UP_V,parsed_parameters);
								break;
			
			case 'W':			
								TriggerEvent(GAME_ENGINE_KEY_UP_W,parsed_parameters);
								break;

			case 'X':			
								TriggerEvent(GAME_ENGINE_KEY_UP_X,parsed_parameters);
								break;

			case 'Y':			
								TriggerEvent(GAME_ENGINE_KEY_UP_Y,parsed_parameters);
								break;

			case 'Z':			
								TriggerEvent(GAME_ENGINE_KEY_UP_Z,parsed_parameters);
								break;

			default:
								wcout << parameters.data(0) << " " << parameters.data(1) << endl;
		};
	}
	else if ( message == GAME_ENGINE_RAW_KEY_DOWN )
	{
		parsed_parameters.data(0,0.0);

		switch ( static_cast<unsigned int>(parameters.data(0)) )
		{
			case VK_LBUTTON:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_MOUSE_BUTTON,parsed_parameters);
								break;

			case VK_RBUTTON:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_MOUSE_BUTTON,parsed_parameters);
								break;

			case VK_CANCEL:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CANCEL,parsed_parameters);
								break;

			case VK_MBUTTON:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_MIDDLE_MOUSE_BUTTON,parsed_parameters);
								break;

			case VK_BACK:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_BACKSPACE,parsed_parameters);
								break;

			case VK_TAB:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_TAB,parsed_parameters);
								break;

			case VK_CLEAR:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CLEAR,parsed_parameters);
								break;

			case VK_OEM_CLEAR:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CLEAR,parsed_parameters);
								break;

			case VK_RETURN:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ENTER,parsed_parameters);
								break;

			case VK_SHIFT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SHIFT,parsed_parameters);
								break;

			case VK_LSHIFT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_SHIFT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SHIFT,parsed_parameters);
								break;

			case VK_RSHIFT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_SHIFT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SHIFT,parsed_parameters);
								break;

			case VK_CONTROL:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CONTROL,parsed_parameters);
								break;

			case VK_LCONTROL:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_CONTROL,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CONTROL,parsed_parameters);
								break;

			case VK_RCONTROL:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_CONTROL,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CONTROL,parsed_parameters);
								break;

			case VK_MENU:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ALT,parsed_parameters);
								break;

			case VK_LMENU:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_ALT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ALT,parsed_parameters);
								break;

			case VK_RMENU:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_ALT,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ALT,parsed_parameters);
								break;

			case VK_PAUSE:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PAUSE,parsed_parameters);
								break;

			case VK_CAPITAL:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CAPS_LOCK,parsed_parameters);
								break;

			case VK_ESCAPE:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ESCAPE,parsed_parameters);
								break;

			case VK_SPACE:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SPACE,parsed_parameters);
								break;

			case VK_PRIOR:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PAGE_UP,parsed_parameters);
								break;

			case VK_NEXT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PAGE_DOWN,parsed_parameters);
								break;

			case VK_END:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_END,parsed_parameters);
								break;

			case VK_HOME:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_HOME,parsed_parameters);
								break;

			case VK_LEFT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_ARROW,parsed_parameters);
								break;

			case VK_UP:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_UP_ARROW,parsed_parameters);
								break;

			case VK_RIGHT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_ARROW,parsed_parameters);
								break;

			case VK_DOWN:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_DOWN_ARROW,parsed_parameters);
								break;

			case VK_SELECT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SELECT,parsed_parameters);
								break;

			case VK_EXECUTE:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_EXECUTE,parsed_parameters);
								break;

			case VK_SNAPSHOT:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PRINT_SCREEN,parsed_parameters);
								break;

			case VK_INSERT:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_INSERT,parsed_parameters);
								break;

			case VK_DELETE:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_DELETE,parsed_parameters);
								break;

			case VK_HELP:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_HELP,parsed_parameters);
								break;

			case VK_LWIN:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_WINDOWS,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_WINDOWS,parsed_parameters);
								break;

			case VK_RWIN:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_WINDOWS,parsed_parameters);
								TriggerEvent(GAME_ENGINE_KEY_DOWN_WINDOWS,parsed_parameters);
								break;

			case VK_APPS:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_APPLICATION,parsed_parameters);
								break;

			case VK_NUMPAD0:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_0,parsed_parameters);
								break;

			case VK_NUMPAD1:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_1,parsed_parameters);
								break;

			case VK_NUMPAD2:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_2,parsed_parameters);
								break;

			case VK_NUMPAD3:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_3,parsed_parameters);
								break;

			case VK_NUMPAD4:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_4,parsed_parameters);
								break;

			case VK_NUMPAD5:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_5,parsed_parameters);
								break;

			case VK_NUMPAD6:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_6,parsed_parameters);
								break;

			case VK_NUMPAD7:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_7,parsed_parameters);
								break;

			case VK_NUMPAD8:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_8,parsed_parameters);
								break;

			case VK_NUMPAD9:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_9,parsed_parameters);
								break;

			case VK_MULTIPLY:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_MULTIPLY,parsed_parameters);
								break;

			case VK_ADD:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_ADD,parsed_parameters);
								break;

			case VK_SEPARATOR:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_SEPARATOR,parsed_parameters);
								break;

			case VK_SUBTRACT:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_SUBTRACT,parsed_parameters);
								break;

			case VK_DECIMAL:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_DECIMAL,parsed_parameters);
								break;

			case VK_DIVIDE:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUMPAD_DIVIDE,parsed_parameters);
								break;

			case VK_F1:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F1,parsed_parameters);
								break;

			case VK_F2:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F2,parsed_parameters);
								break;

			case VK_F3:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F3,parsed_parameters);
								break;

			case VK_F4:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F4,parsed_parameters);
								break;

			case VK_F5:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F5,parsed_parameters);
								break;

			case VK_F6:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F6,parsed_parameters);
								break;

			case VK_F7:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F7,parsed_parameters);
								break;

			case VK_F8:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F8,parsed_parameters);
								break;

			case VK_F9:			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F9,parsed_parameters);
								break;

			case VK_F10:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F10,parsed_parameters);
								break;

			case VK_F11:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F11,parsed_parameters);
								break;

			case VK_F12:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F12,parsed_parameters);
								break;

			case VK_F13:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F13,parsed_parameters);
								break;

			case VK_F14:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F14,parsed_parameters);
								break;

			case VK_F15:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F15,parsed_parameters);
								break;

			case VK_F16:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F16,parsed_parameters);
								break;

			case VK_F17:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F17,parsed_parameters);
								break;

			case VK_F18:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F18,parsed_parameters);
								break;

			case VK_F19:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F19,parsed_parameters);
								break;

			case VK_F20:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F20,parsed_parameters);
								break;

			case VK_F21:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F21,parsed_parameters);
								break;

			case VK_F22:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F22,parsed_parameters);
								break;

			case VK_F23:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F23,parsed_parameters);
								break;

			case VK_F24:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F24,parsed_parameters);
								break;

			case VK_NUMLOCK:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_NUM_LOCK,parsed_parameters);
								break;

			case VK_SCROLL:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SCROLL_LOCK,parsed_parameters);
								break;

			case VK_ATTN:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ATTN,parsed_parameters);
								break;

			case VK_CRSEL:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_CRSEL,parsed_parameters);
								break;

			case VK_EXSEL:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_EXSEL,parsed_parameters);
								break;

			case VK_EREOF:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_EREOF,parsed_parameters);
								break;

			case VK_PLAY:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PLAY,parsed_parameters);
								break;

			case VK_ZOOM:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_ZOOM,parsed_parameters);
								break;

			case VK_PA1:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PA1,parsed_parameters);
								break;

			case VK_OEM_1:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SEMICOLON,parsed_parameters);
								break;

			case VK_OEM_PLUS:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PLUS,parsed_parameters);
								break;

			case VK_OEM_COMMA:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_COMMA,parsed_parameters);
								break;

			case VK_OEM_MINUS:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_MINUS,parsed_parameters);
								break;

			case VK_OEM_PERIOD:	
								TriggerEvent(GAME_ENGINE_KEY_DOWN_PERIOD,parsed_parameters);
								break;

			case VK_OEM_2:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_DIVIDE,parsed_parameters);
								break;

			case VK_OEM_3:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_TILDE,parsed_parameters);
								break;

			case VK_OEM_4:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_LEFT_BRACKET,parsed_parameters);
								break;

			case VK_OEM_5:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_SLASH,parsed_parameters);
								break;

			case VK_OEM_6:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_RIGHT_BRACKET,parsed_parameters);
								break;

			case VK_OEM_7:		
								TriggerEvent(GAME_ENGINE_KEY_DOWN_QUOTE,parsed_parameters);
								break;

			case '0':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_0,parsed_parameters);
								break;

			case '1':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_1,parsed_parameters);
								break;

			case '2':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_2,parsed_parameters);
								break;

			case '3':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_3,parsed_parameters);
								break;

			case '4':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_4,parsed_parameters);
								break;

			case '5':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_5,parsed_parameters);
								break;

			case '6':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_6,parsed_parameters);
								break;

			case '7':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_7,parsed_parameters);
								break;

			case '8':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_8,parsed_parameters);
								break;

			case '9':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_9,parsed_parameters);
								break;

			case 'A':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_A,parsed_parameters);
								break;

			case 'B':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_B,parsed_parameters);
								break;

			case 'C':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_C,parsed_parameters);
								break;

			case 'D':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_D,parsed_parameters);
								break;

			case 'E':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_E,parsed_parameters);
								break;

			case 'F':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F,parsed_parameters);
								break;

			case 'G':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_G,parsed_parameters);
								break;

			case 'H':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_H,parsed_parameters);
								break;

			case 'I':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_I,parsed_parameters);
								break;

			case 'J':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_J,parsed_parameters);
								break;

			case 'K':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_K,parsed_parameters);
								break;

			case 'L':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_L,parsed_parameters);
								break;

			case 'M':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_M,parsed_parameters);
								break;

			case 'N':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_N,parsed_parameters);
								break;

			case 'O':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_O,parsed_parameters);
								break;

			case 'P':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_P,parsed_parameters);
								break;

			case 'Q':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_Q,parsed_parameters);
								break;

			case 'R':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_R,parsed_parameters);
								break;

			case 'S':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_S,parsed_parameters);
								break;

			case 'T':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_T,parsed_parameters);
								break;

			case 'U':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_U,parsed_parameters);
								break;

			case 'V':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_V,parsed_parameters);
								break;

			case 'W':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_W,parsed_parameters);
								break;

			case 'X':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_X,parsed_parameters);
								break;

			case 'Y':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_Y,parsed_parameters);
								break;

			case 'Z':			
								TriggerEvent(GAME_ENGINE_KEY_DOWN_Z,parsed_parameters);
								break;

			default:
					wcout << parameters.data(0) << " " << parameters.data(1) << endl;
		};
	}
	else if ( message == GAME_ENGINE_RAW_MOUSE_MOVE )
	{
		TriggerEvent(GAME_ENGINE_MOUSE_MOVE,parsed_parameters);
	}
	else if ( message == GAME_ENGINE_RAW_VERTICAL_MOUSE_WHEEL )
	{
		parsed_parameters.data(0,static_cast<long double>(static_cast<int>(parsed_parameters.data(0))/WHEEL_DELTA));
		TriggerEvent(GAME_ENGINE_VERTICAL_MOUSE_WHEEL,parsed_parameters);
	}
	else if ( message == GAME_ENGINE_RAW_HORIZONTAL_MOUSE_WHEEL )
	{
		parsed_parameters.data(0,static_cast<long double>(static_cast<short>(parsed_parameters.data(0))/WHEEL_DELTA));
		TriggerEvent(GAME_ENGINE_HORIZONTAL_MOUSE_WHEEL,parsed_parameters);
	}
	else if ( message == GAME_ENGINE_INIT )
		this->Create();
	else if ( message == GAME_ENGINE_INIT_KINECT )
	{
		this->_initialise_kinect();
	}
	else if ( message == GAME_ENGINE_CLOSE  ||  message == GAME_ENGINE_CLOSE_KINECT )
	{
		this->_close_kinect();
	}
};

void	InputManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_input_manager);
};

void	InputManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_input_manager);
};