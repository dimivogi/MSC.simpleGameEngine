#include	"RenderManager.h"
#include	"..\Error Manager\ErrorManager.h"
#include	<io.h>
#include	<iostream>
#include	<fstream>
#include	<cstdio>
#include	<fcntl.h>
#include	<limits>
#define		NOMINMAX
#include	<Windows.h>

using		namespace std;
using		namespace GameEngine;



RenderManager	RenderManager::_render_manager;


void	RenderManager::_initialise_directx( WindowInfo& info , unsigned int , unsigned int )
{
	info._directx_context = Direct3DCreate9(D3D_SDK_VERSION);
	if( !info._directx_context )
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_DIRECTX_CREATE_DIRECT3D,L"Direct3d Create problem",__WFILE__,__LINE__) );


	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;  
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.hDeviceWindow = info._window_handle;	
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.EnableAutoDepthStencil = TRUE;

	HRESULT hr = S_OK;
	hr = info._directx_context->CreateDevice(
		D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,info._window_handle,
		D3DCREATE_HARDWARE_VERTEXPROCESSING|D3DCREATE_FPU_PRESERVE,
		&d3dpp, &info._directx_device
		);

	if ( !info._directx_device )
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_DIRECTX_CREATE_DIRECT3DDEVICE,L"Direct3d Device Create problem",__WFILE__,__LINE__) );
	
	
	// turn on the z-buffer
	info._directx_device->SetRenderState(D3DRS_ZENABLE,TRUE);
};

void	RenderManager::_initialise_opengl( WindowInfo& info , unsigned int width , unsigned int height )
{
	GLuint							PixelFormat;			// Holds The Results After Searching For A Match



	info._opengl_context = GetDC(info._window_handle);
	if ( !info._opengl_context )	// Did We Get A Device Context?
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_HDC,L"Can't Create A GL Device Context.",__WFILE__,__LINE__) );


	static	PIXELFORMATDESCRIPTOR	pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};



	PixelFormat = ChoosePixelFormat(info._opengl_context,&pfd);
	if ( !PixelFormat )	// Did Windows Find A Matching Pixel Format?
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_FIND_PIXEL_FORMAT,L"Can't Find A Suitable PixelFormat.",__WFILE__,__LINE__) );
		
	if( !SetPixelFormat(info._opengl_context,PixelFormat,&pfd) )	// Are We Able To Set The Pixel Format?
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_SET_PIXEL_FORMAT,L"Can't Set The PixelFormat.",__WFILE__,__LINE__) );

	info._opengl_rendering_context = wglCreateContext(info._opengl_context);
	if ( !info._opengl_rendering_context )	// Are We Able To Get A Rendering Context?
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_CREATE_RENDERING_CONTEXT,L"Can't Create A GL Rendering Context.",__WFILE__,__LINE__) );
		
	if( !wglMakeCurrent(info._opengl_context,info._opengl_rendering_context) )	// Try To Activate The Rendering Context
		throw( ErrorException(GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_ACTIVATE_RENDERING_CONTEXT,L"Can't Activate The GL Rendering Context.",__WFILE__,__LINE__) );

	
	glViewport(0,0,width,height);						// Reset The Current Viewport
};

LRESULT CALLBACK	RenderManager::_window_proc( HWND hwnd , UINT msg , WPARAM wparam, LPARAM lparam )
{
	LRESULT	return_value = 0;
	Message	parameters(2);



	// what is the message 
	switch ( msg )
	{	
		case WM_CLOSE:			
								TriggerEvent(GAME_ENGINE_CLOSE_WINDOWS);
								break;
								
		case WM_DESTROY:		
								RenderManager::GetRenderManager()->OnDestroy(hwnd);
								break;

		case WM_SIZE:			
								RenderManager::GetRenderManager()->OnResize(hwnd,LOWORD(lparam),HIWORD(lparam));
								break;

		case WM_PAINT:			
								{
									// this is the main message handler of the system
									PAINTSTRUCT		ps;	// used in WM_PAINT
									HDC				hdc;	// handle to a device context



									//SetForegroundWindow(window_info._window_handle);	// Slightly Higher Priority
									//SetFocus(window_info._window_handle);				// Sets Keyboard Focus To The Window
									// validate the window
									hdc = BeginPaint(hwnd,&ps);
									RenderManager::GetRenderManager()->OnRender(hwnd);
									EndPaint(hwnd,&ps);
									break;
								}

		case WM_SYSKEYDOWN:		
								if ( wparam == VK_MENU  ||  wparam == VK_LMENU  ||  wparam == VK_RMENU )
								{
									parameters.data(0,static_cast<double>(wparam));
									parameters.data(1,static_cast<double>(lparam));
									TriggerEvent(GAME_ENGINE_RAW_KEY_DOWN,parameters);
								}
								else
									return_value = DefWindowProc(hwnd,msg,wparam,lparam);

								break;

		case WM_SYSKEYUP:		
								if ( wparam == VK_MENU  ||  wparam == VK_LMENU  ||  wparam == VK_RMENU )
								{
									parameters.data(0,static_cast<double>(wparam));
									parameters.data(1,static_cast<double>(lparam));
									TriggerEvent(GAME_ENGINE_RAW_KEY_UP,parameters);
								}
								else
									return_value = DefWindowProc(hwnd,msg,wparam,lparam);

								break;

		case WM_KEYDOWN:		
								parameters.data(0,static_cast<double>(wparam));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_DOWN,parameters);
								break;
		
		case WM_KEYUP:					
								parameters.data(0,static_cast<double>(wparam));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_UP,parameters);
								break;

		case WM_LBUTTONDOWN:	
								SetCapture(hwnd);
								parameters.data(0,static_cast<double>(VK_LBUTTON));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_DOWN,parameters);
								break;

		case WM_LBUTTONUP:		
								if ( wparam != (MK_RBUTTON|MK_MBUTTON) )
									ReleaseCapture();

								parameters.data(0,static_cast<double>(VK_LBUTTON));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_UP,parameters);
								break;


		case WM_RBUTTONDOWN:	
								SetCapture(hwnd);
								parameters.data(0,static_cast<double>(VK_RBUTTON));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_DOWN,parameters);
								break;

		case WM_RBUTTONUP:		
								if ( wparam != (MK_LBUTTON|MK_MBUTTON) )
									ReleaseCapture();

								parameters.data(0,static_cast<double>(VK_RBUTTON));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_UP,parameters);
								break;

		case WM_MBUTTONDOWN:	
								SetCapture(hwnd);
								parameters.data(0,static_cast<double>(VK_MBUTTON));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_DOWN,parameters);
								break;

		case WM_MBUTTONUP:		
								if ( wparam != (MK_RBUTTON|MK_LBUTTON) )
									ReleaseCapture();

								parameters.data(0,static_cast<double>(VK_MBUTTON));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_KEY_UP,parameters);
								break;

		case WM_MOUSEWHEEL:		
								parameters.data(0,static_cast<double>(static_cast<short>(HIWORD(wparam))));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_VERTICAL_MOUSE_WHEEL,parameters);
								break;
		case WM_MOUSEHWHEEL:	
								parameters.data(0,static_cast<double>(static_cast<short>(HIWORD(wparam))));
								parameters.data(1,static_cast<double>(lparam));
								TriggerEvent(GAME_ENGINE_RAW_HORIZONTAL_MOUSE_WHEEL,parameters);
								break;

		case WM_MOUSEMOVE:		
								parameters.data(0,static_cast<double>(static_cast<short>(LOWORD(lparam))));
								parameters.data(1,static_cast<double>(static_cast<short>(HIWORD(lparam))));
								TriggerEvent(GAME_ENGINE_RAW_MOUSE_MOVE,parameters);
								break;

		default:				
								return_value = DefWindowProc(hwnd,msg,wparam,lparam);
								break;
	}


	return return_value;
};

HWND	RenderManager::_find_console_handle()
{
	static const int	BUFF_SIZE	= 1024;
	wchar_t				windowTitle[BUFF_SIZE];
	wchar_t				temp_windowTitle[BUFF_SIZE+5];
	HWND				returnValue;



	GetConsoleTitle(windowTitle,BUFF_SIZE);
	wsprintf(temp_windowTitle,L"%s-temp",windowTitle);
	SetConsoleTitle(temp_windowTitle);
	Sleep(40);
	returnValue = FindWindow(NULL,temp_windowTitle);
	SetConsoleTitle(windowTitle);


	return returnValue;
};

// function repsonsible for redirecting input and output streams to a newly allocated console
void	RenderManager::_redirect_io( const unsigned int console_offset_x , const unsigned int console_offset_y , const unsigned int console_width , const unsigned int console_height , const unsigned short console_max_lines )
{
	if ( !AllocConsole() )	return;



	CONSOLE_SCREEN_BUFFER_INFO	console_info;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&console_info);
	console_info.dwSize.Y = console_max_lines;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),console_info.dwSize);


	HWND	console_handle = RenderManager::_find_console_handle();

	if ( console_height == 0 )
	{
		RECT	console_size;
		RECT	desktop_size;
	
		GetWindowRect(console_handle,&console_size);
		GetClientRect(GetDesktopWindow(),&desktop_size);
		console_size.bottom = desktop_size.bottom - 60;

		if ( console_width != 0 )
			MoveWindow(console_handle,console_offset_x,console_offset_y,console_width,console_size.bottom,TRUE);
		else
			MoveWindow(console_handle,console_offset_x,console_offset_y,console_size.right,console_size.bottom,TRUE);
	}
	else
		MoveWindow(console_handle,console_offset_x,console_offset_y,console_width,console_height,TRUE);



	int		stdout_handle = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE),_O_TEXT); 
	int		stdin_handle = _open_osfhandle((long)GetStdHandle(STD_INPUT_HANDLE),_O_TEXT);
	int		stderr_handle = _open_osfhandle((long)GetStdHandle(STD_ERROR_HANDLE),_O_TEXT);

	
	FILE*	stdout_file = _fdopen(stdout_handle,"w");
	FILE*	stdin_file = _fdopen(stdin_handle,"r");
	FILE*	stderr_file = _fdopen(stderr_handle,"w");

	*stdout = *stdout_file;
	*stdin = *stdin_file;
	*stderr = *stderr_file;

	//setvbuf(stdout,NULL,_IONBF,0);	// might be needed, parasoft throws an error since they redirect the I/O operations
	//setvbuf(stdin,NULL,_IONBF,0);		// to std streams
	//setvbuf(stderr,NULL,_IONBF,0);

	ios::sync_with_stdio();
};


RenderManager::RenderManager()	:	_app_handle(NULL) , _quit(false)
{
	WindowInfo	temp;



	this->_windows.insert(pair<unsigned int,WindowInfo>(0,temp));
	temp._window_handle = NULL;
};

RenderManager::~RenderManager()	{};


RenderManager*	RenderManager::GetRenderManager()	{ return &_render_manager; };
double			RenderManager::GetTime()			
{
	return static_cast<double>(timeGetTime());
};

void	RenderManager::Create( const unsigned int x_offset, const unsigned int y_offset, const unsigned int width , const unsigned int height , const unsigned short console_max_lines )
{
	#ifdef	_DEBUG
		this->_redirect_io(x_offset,y_offset,width,height,console_max_lines);
	#else
		x_offset;	y_offset;	width;	height;	console_max_lines;
	#endif	/* _DEBUG */

	this->RegisterEvent(GAME_ENGINE_CLOSE_WINDOWS);
	this->RegisterEvent(GAME_ENGINE_CLOSE);
}

void	RenderManager::OnEvent( const unsigned int message , const Message& parameters )
{
	if ( message == GAME_ENGINE_INIT )
	{
		unsigned short	console_lines = static_cast<unsigned short>(parameters.data(5));



		if ( console_lines == 0 )
			console_lines = 999;

		this->Create(	static_cast<unsigned int>(parameters.data(1)) , 
						static_cast<unsigned int>(parameters.data(2)) , 
						static_cast<unsigned int>(parameters.data(3)) , 
						static_cast<unsigned int>(parameters.data(4)) , 
						console_lines );
	}
	else if ( message == GAME_ENGINE_CLOSE_WINDOWS  ||  message == GAME_ENGINE_CLOSE )
	{
		this->Exit();
		this->_quit = true;
	}
};

void	RenderManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_render_manager);
};

void	RenderManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_render_manager);
};


InitialisationInfo	RenderManager::CreateNewWindow( const HINSTANCE hInstance , const wstring& name , const unsigned int width , const unsigned int height , unsigned int x, unsigned int y , WindowObject* caller , const bool opengl )
{
	WindowInfo			window_info;
	InitialisationInfo	return_value;
	WNDCLASSW			window_class;



	try
	{
		// first fill in the window class stucture
		window_class.style			= CS_HREDRAW | CS_VREDRAW;                  
		window_class.lpfnWndProc	= &RenderManager::_window_proc;
		window_class.cbClsExtra		= 0;
		window_class.cbWndExtra		= 0;
		window_class.hInstance		= hInstance;
		window_class.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		window_class.hCursor		= LoadCursor(NULL, IDC_ARROW);
		window_class.hbrBackground  = (HBRUSH)GetStockObject(BLACK_BRUSH);
		window_class.lpszMenuName	= NULL;
		window_class.lpszClassName	= name.c_str();

		// register the window class
		if ( RegisterClass(&window_class) )
		{
			window_info._window_handle = CreateWindowExW(
					0L,
					name.c_str(),	// class
					name.c_str(),	// title
					WS_OVERLAPPEDWINDOW | WS_VISIBLE,
					x,
					y,
					//Set the size of the window to the size of the screen 
					width,
					height,
					NULL,	   // handle to parent 
					NULL,	   // handle to menu
					hInstance,	// instance
					NULL
			);


			// create the window
			if ( window_info._window_handle )	// creation params
			{
				unsigned int	id = 1;
				bool			found = false;


			
				if ( opengl )
					RenderManager::_initialise_opengl(window_info,width,height);
				else
					RenderManager::_initialise_directx(window_info,width,height);

				window_info._name = name;
				window_info._instance = hInstance;
				window_info._window_pointer = caller;
			

				while( id <= numeric_limits<unsigned int>::max()  &&  !found )
				{
					map<unsigned int,WindowInfo>::iterator it = this->_windows.begin();



					while( it != this->_windows.end() )
					{
						if ( it->first == id )
							break;
						else
							++it;
					}

					if ( it == this->_windows.end() )
						found = true;
					else
						++id;
				}
				this->_windows.insert(pair<unsigned int,WindowInfo>(id,window_info));

				return_value._id = id;
				return_value._opengl_id = window_info._opengl_context;
				return_value._opengl_rendering_id = window_info._opengl_rendering_context;
				return_value._directx_id = window_info._directx_context;
				return_value._directx_device = window_info._directx_device;


				this->ShowWindow(id);
				SetFocus(window_info._window_handle);
			}
			else
				UnregisterClass(name.c_str(),hInstance);

		}
	}
	catch ( ErrorException& e )
	{
		if ( window_info._window_handle )
		{
			DestroyWindow(window_info._window_handle);
			UnregisterClass(name.c_str(),hInstance);
		}

		ErrorManager::GetErrorManager()->Output(L"****** ERROR ******");
		ErrorManager::GetErrorManager()->LogException(e);
		ErrorManager::GetErrorManager()->Output(L"*******************");
	}
		


	return return_value;
};

void	RenderManager::CloseWindow( const unsigned int window )
{
	if ( window > 0 )
	{
		map<unsigned int,WindowInfo>::iterator	it = this->_windows.find(window);



		if ( it != this->_windows.end() )
		{
			DestroyWindow(it->second._window_handle);
			UnregisterClass(it->second._name.c_str(),it->second._instance);

			if ( it->second._opengl_context )
			{
				this->MakeCurrent(0);
				wglDeleteContext(it->second._opengl_rendering_context);
				ReleaseDC(it->second._window_handle,it->second._opengl_context);
			}
			else
			{
				it->second._directx_device->Release();
				it->second._directx_context->Release();
			}


			this->_windows.erase(it);
		}
	}
};

void	RenderManager::ShowWindow( const unsigned int window ) const
{
	if ( window > 0 )
	{
		map<unsigned int,WindowInfo>::const_iterator	it = this->_windows.find(window);



		if ( it != this->_windows.end() )
			::ShowWindow(it->second._window_handle,SW_SHOW);
	}
};

void	RenderManager::HideWindow( const unsigned int window ) const
{
	if ( window > 0 )
	{
		map<unsigned int,WindowInfo>::const_iterator	it = this->_windows.find(window);



		if ( it != this->_windows.end() )
			::ShowWindow(it->second._window_handle,SW_HIDE);
	}
};

void	RenderManager::Exit()
{
	for ( unsigned int i = 1;  i <= this->_windows.size();  ++i ) 
		this->CloseWindow(i);

	PostQuitMessage(0);
};

void	RenderManager::MakeCurrent( const unsigned int window ) const
{
	if ( window > 0 )
	{
		map<unsigned int,WindowInfo>::const_iterator	it = this->_windows.find(window);



		if ( it != this->_windows.end() )
		{
			if ( it->second._opengl_context )
				wglMakeCurrent(it->second._opengl_context,it->second._opengl_rendering_context);
		}
	}
	else
		wglMakeCurrent(NULL,NULL);
};

void	RenderManager::UnmakeCurrent( const unsigned int window ) const
{
	if ( window > 0 )
	{
		map<unsigned int,WindowInfo>::const_iterator	it = this->_windows.find(window);



		if ( it != this->_windows.end() )
		{
			if ( it->second._opengl_context )
				wglMakeCurrent(it->second._opengl_context,NULL);
		}
	}
	else
		wglMakeCurrent(NULL,NULL);
};

void	RenderManager::RequestRepaint( const unsigned int window ) const
{
	if ( window > 0 )
	{
		map<unsigned int,WindowInfo>::const_iterator	it = this->_windows.find(window);



		if ( it != this->_windows.end() )
			PostMessageW(it->second._window_handle,WM_PAINT,0,0);
	}
};


int	RenderManager::MainLoop()
{
	int		return_value = 0;
	MSG		msg;



	msg.wParam = 0;
	// enter main event loop
	while(!this->_quit)
	{
		if ( PeekMessage(&msg,NULL,0,0,PM_REMOVE) )
		{ 
			// test if this is a quit
			if ( msg.message == WM_QUIT )
				this->_quit = true;
			
			// translate any accelerator keys
			TranslateMessage(&msg);
			// send the message to the window proc
			DispatchMessage(&msg);
		} // end if
		else
		{
			for ( map<unsigned int,WindowInfo>::iterator it = ++(this->_windows.begin());  it != this->_windows.end();  ++it )
				it->second._window_pointer->OnIdle();
		}

	} // end while

	// return to Windows like this
	return_value = msg.wParam;


	return return_value;
};


void	RenderManager::OnDestroy( const HWND handle )
{
	for ( map<unsigned int,WindowInfo>::iterator it = ++(this->_windows.begin());  it != this->_windows.end();  ++it )
	{
		if ( it->second._window_handle == handle )
		{
			it->second._window_pointer->OnDestroy();
			break;
		}
	}
};

void	RenderManager::OnResize( const HWND handle , const unsigned int width , const unsigned int height )
{
	for ( map<unsigned int,WindowInfo>::iterator it = ++(this->_windows.begin());  it != this->_windows.end();  ++it )
	{
		if ( it->second._window_handle == handle )
		{
			it->second._window_pointer->OnResize(width,height);
			break;
		}
	}
};

void	RenderManager::OnRender( const HWND handle )
{
	for ( map<unsigned int,WindowInfo>::iterator it = ++(this->_windows.begin());  it != this->_windows.end();  ++it )
	{
		if ( it->second._window_handle == handle )
		{
			this->MakeCurrent(it->first);
			it->second._window_pointer->OnRender();
			this->UnmakeCurrent(it->first);
			break;
		}
	}
};