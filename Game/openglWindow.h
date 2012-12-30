#pragma	once

#include	"GameEngine.h"
#include	"GameManager.h"
#include	<MSR_NuiApi.h>

using		namespace GameEngine;



#ifndef		_OPENGL_WINDOW_H_
	#define	_OPENGL_WINDOW_H_


	// Window object with opengl Rendering
	class	OpenGLWindow	:	public WindowObject
	{
		private:

			GameManager*	_manager;


		public:

			OpenGLWindow( HINSTANCE hInstance , GameManager* manager );

			void	OnCreate();
			void	OnDestroy();
			void	OnRender();
			void	OnResize( const unsigned int width , const unsigned int height );
			void	OnIdle();

			void	Create( const wstring& name );
	};


#endif		/* _OPENGL_WINDOW_H_ */