#pragma	once

#include	"..\GameEngineDefines.h"



#ifndef		_INPUT_MANAGER_H_
	#define	_INPUT_MANAGER_H_

	
	namespace	GameEngine
	{

		class	InputManager	:	public EngineObject
		{
			private:

				static InputManager		_input_manager;
				HANDLE					_next_skeleton_event;
				HANDLE					_stop_kinect_event;
				HANDLE					_kinect_thread_handle;
				HANDLE					_depth_stream;
				bool					_kinect_init;

				InputManager();
				virtual ~InputManager();

				void					_initialise_kinect();
				void					_close_kinect();
				void					_skeleton_event_handler() const;

				static DWORD WINAPI		_kinect_thread_process( LPVOID pParam );


			public:

				static InputManager*	GetInputManager();
				void					Create();
				void					OnEvent( const unsigned int message , const Message& parameters );
				void					RegisterEvent( const unsigned int message );
				void					UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _INPUT_MANAGER_H_ */