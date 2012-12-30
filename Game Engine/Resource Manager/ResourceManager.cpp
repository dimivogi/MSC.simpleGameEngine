#include	"ResourceManager.h"
#include	<iostream>

using		namespace std;
using		namespace GameEngine;



ResourceManager	ResourceManager::_resource_manager;


ResourceManager::ResourceManager()	{};
ResourceManager::~ResourceManager()	{};


ResourceManager*	ResourceManager::GetResourceManager()	{ return &_resource_manager; };
void	ResourceManager::OnEvent( const unsigned int , const Message& )
{
};

void	ResourceManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_resource_manager);
};

void	ResourceManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_resource_manager);
};