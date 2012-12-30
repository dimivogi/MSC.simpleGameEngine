#include	"MessageManager.h"

using		namespace GameEngine;



MessageManager	MessageManager::_message_manager;


MessageManager::MessageManager()	{};
MessageManager::~MessageManager()	{};


MessageManager*	MessageManager::GetMessageManager()	{ return &_message_manager; };
void	MessageManager::OnEvent( const unsigned int message , const Message& parameters )
{
	bool												null_found = false;
	map<EngineObject*,vector<unsigned int> >::iterator	null_it = this->_event_entries.find(NULL);



	if ( null_it != this->_event_entries.end() )
	{
		for ( vector<unsigned int>::iterator message_it = null_it->second.begin();  message_it != null_it->second.end();  ++message_it )
		{
			if ( (*message_it) == message )
			{
				null_found = true;

				for ( map<EngineObject*,vector<unsigned int> >::iterator send_it = this->_event_entries.begin();  send_it != this->_event_entries.end();  ++send_it )
				{
					if ( send_it != null_it )
						send_it->first->OnEvent(message,parameters);
				}

				break;
			}
		}
	}

	for ( map<EngineObject*,vector<unsigned int> >::iterator it = this->_event_entries.begin();  it != this->_event_entries.end();  ++it )
	{
		if ( it != null_it )
		{
			for ( vector<unsigned int>::iterator message_it = it->second.begin();  message_it != it->second.end();  ++message_it )
			{
				if ( (*message_it) == message )
				{
					if ( !null_found )
						it->first->OnEvent(message,parameters);
					
					break;
				}
			}
		}
	}
};

void	MessageManager::RegisterEvent( const unsigned int )	{};
// If engine object is NULL, recipients are all registered objects, equivalent to broadcast event
void	MessageManager::RegisterEvent( const unsigned int message , EngineObject* object )
{
	map<EngineObject*,vector<unsigned int> >::iterator	event_iterator = this->_event_entries.find(object);



	if ( event_iterator != this->_event_entries.end() )
	{
		bool							found = false;
		vector<unsigned int>::iterator	object_event_iterator = event_iterator->second.begin();



		while( object_event_iterator != event_iterator->second.end()  &&  !found )
		{
			if ( (*object_event_iterator) == message )
				found = true;
			else
				++object_event_iterator;
		};


		if ( !found )
			event_iterator->second.push_back(message);
	}
	else
		this->_event_entries.insert(pair<EngineObject*,vector<unsigned int> >(object,vector<unsigned int>(1,message)));
};

void	MessageManager::UnregisterEvent( const unsigned int )	{};
void	MessageManager::UnregisterEvent( const unsigned int message , EngineObject* object )
{
	map<EngineObject*,vector<unsigned int> >::iterator	event_iterator = this->_event_entries.find(object);



	if ( event_iterator != this->_event_entries.end() )
	{
		for ( vector<unsigned int>::iterator	object_event_iterator = event_iterator->second.begin();  object_event_iterator != event_iterator->second.end();  ++object_event_iterator )
		{
			 if ( (*object_event_iterator) == message )
			 {
				event_iterator->second.erase(object_event_iterator);
				break;
			 }
		};

		if ( event_iterator->second.size() == 0  &&  event_iterator->first != NULL )
			this->_event_entries.erase(event_iterator);
	}
};