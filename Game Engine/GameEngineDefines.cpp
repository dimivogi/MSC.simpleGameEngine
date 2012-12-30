#include	"GameEngineDefines.h"
#include	"Message Manager\MessageManager.h"
#include	"Audio Manager\AudioManager.h"
#include	"Error Manager\ErrorManager.h"
#include	"Input Manager\InputManager.h"
#include	"Physics Manager\PhysicsManager.h"
#include	"Render Manager\RenderManager.h"
#include	"Resource Manager\ResourceManager.h"
#include	"Scene Manager\SceneManager.h"
#include	"Script Manager\ScriptManager.h"



#ifdef	_WINDLL


	void	GameEngine::TriggerEvent( const unsigned int message , const Message& parameters )	{ MessageManager::GetMessageManager()->OnEvent(message,parameters); };
	void	GameEngine::RegisterEvent( const unsigned int message )								{ AddEventWatch(message,NULL); };
	void	GameEngine::UnregisterEvent( const unsigned int message )							{ RemoveEventWatch(message,NULL); };
	
	void	GameEngine::AddEventWatch( const unsigned int message , EngineObject* object )		{ MessageManager::GetMessageManager()->RegisterEvent(message,object); };
	void	GameEngine::RemoveEventWatch( const unsigned int message , EngineObject* object )	{ MessageManager::GetMessageManager()->UnregisterEvent(message,object); }; 

	int		GameEngine::MainLoop()																{ return RenderManager::GetRenderManager()->MainLoop(); };
	void	GameEngine::InitialRegistration()
	{
		AudioManager::GetAudioManager()->RegisterEvent(GAME_ENGINE_INIT);
		ErrorManager::GetErrorManager()->RegisterEvent(GAME_ENGINE_INIT);
		InputManager::GetInputManager()->RegisterEvent(GAME_ENGINE_INIT);
		PhysicsManager::GetPhysicsManager()->RegisterEvent(GAME_ENGINE_INIT);
		RenderManager::GetRenderManager()->RegisterEvent(GAME_ENGINE_INIT);
		ResourceManager::GetResourceManager()->RegisterEvent(GAME_ENGINE_INIT);
		SceneManager::GetSceneManager()->RegisterEvent(GAME_ENGINE_INIT);
		ScriptManager::GetScriptManager()->RegisterEvent(GAME_ENGINE_INIT);
	};


#endif	/*_WINDLL */