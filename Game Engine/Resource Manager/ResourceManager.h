#pragma	once

#include	"..\GameEngineDefines.h"



#ifndef		_RESOURCE_MANAGER_H_
	#define	_RESOURCE_MANAGER_H_


	namespace	GameEngine
	{

		class	ResourceManager	:	public EngineObject
		{
			private:

				static ResourceManager	_resource_manager;

				ResourceManager();
				virtual ~ResourceManager();


			public :

				static ResourceManager*	GetResourceManager();
				void					OnEvent( const unsigned int message , const Message& parameters );
				void					RegisterEvent( const unsigned int message );
				void					UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _RESOURCE_MANAGER_H_ */