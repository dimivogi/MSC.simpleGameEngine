#pragma	once

#include	"..\GameEngineDefines.h"



#ifndef		_SCRIPT_MANAGER_H_
	#define	_SCRIPT_MANAGER_H_


	namespace	GameEngine
	{

		class	ScriptManager	:	public EngineObject
		{
			private:

				static ScriptManager	_script_manager;

				ScriptManager();
				virtual ~ScriptManager();


			public :

				static ScriptManager*	GetScriptManager();
				void					OnEvent( const unsigned int message , const Message& parameters );
				void					RegisterEvent( const unsigned int message );
				void					UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _SCRIPT_MANAGER_H_ */