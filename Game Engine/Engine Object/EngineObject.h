#pragma	once

#include	"..\GameEngineMacros.h"
#include	"..\Message Manager\Message.h"



#ifndef		_ENGINE_OBJECT_H_
	#define	_ENGINE_OBJECT_H_


	namespace	GameEngine
	{

		class DLL_OUTPUT	EngineObject
		{
			public:

				EngineObject()			{};
				virtual ~EngineObject()	{};

				virtual	void	OnEvent( const unsigned int message , const Message& parameters ) = 0;
				virtual void	RegisterEvent( const unsigned int message ) = 0;
				virtual void	UnregisterEvent( const unsigned int message ) = 0;
		};

	};


#endif		/* _ENGINE_OBJECT_H_ */