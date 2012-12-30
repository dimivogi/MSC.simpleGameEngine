#pragma	once

#include	"..\GameEngineDefines.h"



#ifndef		_PHYSICS_MANAGER_H_
	#define	_PHYSICS_MANAGER_H_


	namespace	GameEngine
	{

		class	PhysicsManager	:	public EngineObject
		{
			private:

				static PhysicsManager	_physics_manager;

				PhysicsManager();
				virtual ~PhysicsManager();


			public :

				static PhysicsManager*	GetPhysicsManager();
				void					OnEvent( const unsigned int message , const Message& parameters );
				void					RegisterEvent( const unsigned int message );
				void					UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _PHYSICS_MANAGER_H_ */