#include	"GenericObject.h"

using		namespace GameEngine;



GenericObject::GenericObject()	{};
GenericObject::~GenericObject()	{};


void	GenericObject::OnEvent( const unsigned int , const Message& )					{};
void	GenericObject::RegisterEvent( const unsigned int message )		{ AddEventWatch(message,this); };
void	GenericObject::UnregisterEvent( const unsigned int message )	{ RemoveEventWatch(message,this); };