#pragma	once

#include	"..\GameEngineDefines.h"
#include	"..\Engine Object\EngineObject.h"



#ifndef		_GENERIC_OBJECT_H_
	#define	_GENERIC_OBJECT_H_


	namespace	GameEngine
	{

		// Generic Object, suitable for inheritance, and capable of working with the Message Manager
		class DLL_OUTPUT	GenericObject	:	public EngineObject
		{
			public:

				GenericObject();
				virtual ~GenericObject();


				virtual void	OnEvent( const unsigned int message , const Message& parameters );
				void			RegisterEvent( const unsigned int message );
				void			UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _GENERIC_OBJECT_H_ */