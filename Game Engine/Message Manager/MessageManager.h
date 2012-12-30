#pragma	once

#include	<vector>
#include	<map>
#include	"..\GameEngineDefines.h"

using		namespace std;



#ifndef		_MESSAGE_MANAGER_H_
	#define	_MESSAGE_MANAGER_H_


	namespace	GameEngine
	{

		class	MessageManager	:	public EngineObject
		{
			private:

				static MessageManager						_message_manager;
				map<EngineObject*,vector<unsigned int> >	_event_entries;


				void										RegisterEvent( const unsigned int );
				void										UnregisterEvent( const unsigned int );

				MessageManager();
				virtual ~MessageManager();


			public :

				static MessageManager*						GetMessageManager();
				void										OnEvent( const unsigned int message , const Message& parameters );
				void										RegisterEvent( const unsigned int message , EngineObject* object );
				void										UnregisterEvent( const unsigned int message , EngineObject* object );
		};

	};


#endif		/* _MESSAGE_MANAGER_H_ */