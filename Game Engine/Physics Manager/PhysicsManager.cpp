#include	"PhysicsManager.h"
#include	<iostream>

using		namespace std;
using		namespace GameEngine;



PhysicsManager	PhysicsManager::_physics_manager;


PhysicsManager::PhysicsManager()	{};
PhysicsManager::~PhysicsManager()	{};


PhysicsManager*	PhysicsManager::GetPhysicsManager()	{ return &_physics_manager; };
void	PhysicsManager::OnEvent( const unsigned int , const Message& )
{
}

void	PhysicsManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_physics_manager);
};

void	PhysicsManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_physics_manager);
};