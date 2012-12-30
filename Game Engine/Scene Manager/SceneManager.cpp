#include	"SceneManager.h"
#include	<iostream>

using		namespace std;
using		namespace GameEngine;



SceneManager	SceneManager::_scene_manager;


SceneManager::SceneManager()	{};
SceneManager::~SceneManager()	{};


SceneManager*	SceneManager::GetSceneManager()	{ return &_scene_manager; };
void	SceneManager::OnEvent( const unsigned int , const Message& )
{
};

void	SceneManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_scene_manager);
};

void	SceneManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_scene_manager);
};