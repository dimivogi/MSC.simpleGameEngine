#include	"ScriptManager.h"
#include	<iostream>

using		namespace std;
using		namespace GameEngine;



ScriptManager	ScriptManager::_script_manager;


ScriptManager::ScriptManager()	{};
ScriptManager::~ScriptManager()	{};


ScriptManager*	ScriptManager::GetScriptManager()	{ return &_script_manager; };
void	ScriptManager::OnEvent( const unsigned int , const Message& )
{
};

void	ScriptManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_script_manager);
};

void	ScriptManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_script_manager);
};