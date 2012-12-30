#include	"Message.h"

using		namespace GameEngine;


Message::Message( const unsigned int data_size , const unsigned int pointer_size )	:		
	_data(data_size,0.0) , _pointers(pointer_size,NULL)	{};