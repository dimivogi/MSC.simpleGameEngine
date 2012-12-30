#pragma	once

#include	"GameEngine.h"
#include	"GameManager.h"

using		namespace GameEngine;



#ifndef		_DIRECTX_WINDOW_H_
	#define	_DIRECTX_WINDOW_H_

	// Window Class object with direct x rendering
	class	DirectXWindow	:	public WindowObject
	{
		private:

			GameManager*	_manager;


		public:

			DirectXWindow( HINSTANCE hInstance , GameManager* manager );

			void	OnCreate();
			void	OnDestroy();
			void	OnRender();
			void	OnResize( const unsigned int width , const unsigned int height );
			void	OnIdle();

			void	Create( const wstring& name );
	};


#endif		/* _DIRECTX_WINDOW_H_ */