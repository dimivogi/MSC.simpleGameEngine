#pragma	once

#include	<map>
#include	"..\Window Object\WindowObject.h"
#include	"..\GameEngineDefines.h"
#include	<gl\GL.h>
#include	<gl\GLU.h>
#include	<d3d9.h>
#include	<d3dx9.h>

using		namespace std;



#ifndef		_RENDER_MANAGER_H_
	#define	_RENDER_MANAGER_H_


	namespace	GameEngine
	{

		class	WindowInfo
		{
			public:

				wstring				_name;
				HINSTANCE			_instance;
				HWND				_window_handle;
				HDC					_opengl_context;
				HGLRC				_opengl_rendering_context;
				LPDIRECT3D9			_directx_context;
				LPDIRECT3DDEVICE9	_directx_device;
				WindowObject*		_window_pointer;


				WindowInfo()	:	_instance(NULL) , _window_handle(NULL) , _opengl_context(NULL) , _opengl_rendering_context(NULL) , _directx_context(NULL) , _directx_device(NULL) , _window_pointer(NULL)	{};
		};


		class	RenderManager	:	public EngineObject
		{
			private:

				static RenderManager			_render_manager;
				map<unsigned int,WindowInfo>	_windows;
				HWND							_app_handle;
				bool							_quit;


				static void						_initialise_directx( WindowInfo& info , unsigned int width , unsigned int height );
				static void						_initialise_opengl( WindowInfo& info ,  unsigned int width , unsigned int height );
				static LRESULT CALLBACK			_window_proc( HWND hwnd , UINT msg , WPARAM wparam, LPARAM lparam );
				static HWND						_find_console_handle();
				DLL_OUTPUT static void			_redirect_io( const unsigned int console_offset_x , const unsigned int console_offset_y , const unsigned int console_width , const unsigned int console_height , const unsigned short console_max_lines );

				RenderManager();
				virtual ~RenderManager();


			public :

				static RenderManager*			GetRenderManager();
				static double					GetTime();

				void							Create( const unsigned int x_offset = 0 , const unsigned int y_offset = 0 , const unsigned int width = 0 , const unsigned int height = 0 , const unsigned short console_max_lines = 999 );
				void							OnEvent( const unsigned int message , const Message& parameters );
				void							RegisterEvent( const unsigned int message );
				void							UnregisterEvent( const unsigned int message );

				InitialisationInfo				CreateNewWindow( const HINSTANCE hInstance , const wstring& name , const unsigned int width , const unsigned int height , unsigned int x, unsigned int y , WindowObject* caller , const bool opengl );
				void							CloseWindow( const unsigned int window );
				void							ShowWindow( const unsigned int window ) const;
				void							HideWindow( const unsigned int window ) const;
				void							Exit();
				void							MakeCurrent( const unsigned int window ) const;
				void							UnmakeCurrent( const unsigned int window ) const;
				void							RequestRepaint( const unsigned int window ) const;

				int								MainLoop();
				void							OnDestroy( const HWND handle );
				void							OnResize( const HWND handle , const unsigned int width , const unsigned int height );
				void							OnRender( const HWND handle );
		};

	};


#endif		/* _RENDER_MANAGER_H_ */