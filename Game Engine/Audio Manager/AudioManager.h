#pragma	once

#include	"..\GameEngineDefines.h"



#ifndef		_AUDIO_MANAGER_H_
	#define	_AUDIO_MANAGER_H_


	namespace	GameEngine
	{

		class	AudioManager	:	public EngineObject
		{
			private:

				static AudioManager		_audio_manager;

				AudioManager();
				virtual ~AudioManager();


			public:

				static AudioManager*	GetAudioManager();
				void					OnEvent( const unsigned int message , const Message& parameters );
				void					RegisterEvent( const unsigned int message );
				void					UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _AUDIO_MANAGER_H_ */