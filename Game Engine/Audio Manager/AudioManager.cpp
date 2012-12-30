#include	"AudioManager.h"
#include	<iostream>

using		namespace std;
using		namespace GameEngine;



AudioManager	AudioManager::_audio_manager;


AudioManager::AudioManager()	{};
AudioManager::~AudioManager()	{};


AudioManager*	AudioManager::GetAudioManager()	{ return &_audio_manager; };
void	AudioManager::OnEvent( const unsigned int , const Message& )
{
};

void	AudioManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_audio_manager);
};

void	AudioManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_audio_manager);
};