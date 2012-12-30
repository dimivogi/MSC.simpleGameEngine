#pragma	once

#include	"..\GameEngineDefines.h"



#ifndef		_SCENE_MANAGER_H_
	#define	_SCENE_MANAGER_H_


	namespace	GameEngine
	{

		class	SceneManager	:	public EngineObject
		{
			private:

				static SceneManager		_scene_manager;

				SceneManager();
				virtual ~SceneManager();


			public :

				static SceneManager*	GetSceneManager();
				void					OnEvent( const unsigned int message , const Message& parameters );
				void					RegisterEvent( const unsigned int message );
				void					UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _SCENE_MANAGER_H_ */