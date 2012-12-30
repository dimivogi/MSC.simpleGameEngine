#pragma	once

#include	<string>
#include	"..\Generic Object\GenericObject.h"
#include	<gl\GL.h>
#include	<gl\GLU.h>
#include	<d3d9.h>
#include	<d3dx9.h>

using		namespace std;



#ifndef		_WINDOW_OBJECT_H_
	#define	_WINDOW_OBJECT_H_

	
	namespace	GameEngine
	{

		class DLL_OUTPUT	InitialisationInfo
		{
			public:

				LPDIRECT3D9			_directx_id;
				LPDIRECT3DDEVICE9	_directx_device;
				HDC					_opengl_id;
				HGLRC				_opengl_rendering_id;
				unsigned int		_id;


				InitialisationInfo()	:	 _directx_id(NULL) , _directx_device(NULL) , _opengl_id(NULL) , _opengl_rendering_id(NULL) ,_id(0)	{};
		};


		// Basic Window class capable for directx and oopengl rendering
		class DLL_OUTPUT	WindowObject	:	public GenericObject
		{
			private:

				HINSTANCE				_hInstance;
				InitialisationInfo		_window_info;
				unsigned int			_width;
				unsigned int			_height;
				unsigned int			_x;
				unsigned int			_y;


			public:

				explicit WindowObject( HINSTANCE hInstance );
				virtual ~WindowObject();


				void					set_size( const unsigned int width , const unsigned int height );

				
				unsigned int			handle() const;
				const HDC				gl_content() const;
				const LPDIRECT3DDEVICE9	directx_device() const;
				void					get_size( unsigned int& width , unsigned int& height ) const;				

				
				virtual void			OnEvent( const unsigned int message , const Message& parameters );
				virtual void			OnCreate();
				virtual void			OnDestroy();
				virtual void			OnRender();
				virtual void			OnResize( const unsigned int width , const unsigned int height );
				virtual void			OnIdle();


				void					Create( const wstring& name , bool opengl = false );
				void					Close();
				void					Show();
				void					Hide();
				void					Exit();
				void					SetInitialPosition( const unsigned int x , const unsigned int y );
				void					SwapBuffers();


				static double			GetTime();
		};

	};


#endif		/* _WINDOW_OBJECT_H_ */