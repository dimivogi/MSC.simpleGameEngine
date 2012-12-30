#pragma	once

#include	"Engine Object\EngineObject.h"
#define		NOMINMAX
#include	<Windows.h>
#include	<MSR_NuiApi.h>



#ifndef		_GAME_ENGINE_DEFINES_H_
	#define	_GAME_ENGINE_DEFINES_H_

	namespace	GameEngine
	{
		// each message expects different parameters, with the exception of kinect skeleton input with sends a 
		// skeleton structure pointer, all the other defined messages do not have pointers in their Message class.

		const unsigned int	GAME_ENGINE_OK =							0;
		const unsigned int	GAME_ENGINE_ERROR_FILE_OPENED =				1;
		const unsigned int	GAME_ENGINE_ERROR_FILE_NOT_OPENED =			2;
		const unsigned int	GAME_ENGINE_ERROR_LOGGED =					3;
		const unsigned int	GAME_ENGINE_ERROR_UNLOGGED =				4;
		const unsigned int	GAME_ENGINE_ERROR_MESSAGE_LOGGED =			5;
		const unsigned int	GAME_ENGINE_ERROR_MESSAGE_UNLOGGED =		6;
		const unsigned int	GAME_ENGINE_ERROR_DISPLAY_MESSAGE =			7;
		const unsigned int	GAME_ENGINE_ERROR_NO_DISPLAY_MESSAGE =		8;
		const unsigned int	GAME_ENGINE_RAW_KEY_UP =					9;
		const unsigned int	GAME_ENGINE_RAW_KEY_DOWN =					10;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_MOUSE_BUTTON =	11;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_MOUSE_BUTTON =	12;
		const unsigned int	GAME_ENGINE_KEY_DOWN_MIDDLE_MOUSE_BUTTON =	13;
		const unsigned int	GAME_ENGINE_KEY_DOWN_CANCEL =				14;
		const unsigned int	GAME_ENGINE_KEY_DOWN_BACKSPACE =			15;
		const unsigned int	GAME_ENGINE_KEY_DOWN_TAB =					16;
		const unsigned int	GAME_ENGINE_KEY_DOWN_CLEAR =				17;
		const unsigned int	GAME_ENGINE_KEY_DOWN_ENTER =				18;
		const unsigned int	GAME_ENGINE_KEY_DOWN_SHIFT =				19;
		const unsigned int	GAME_ENGINE_KEY_DOWN_CONTROL =				20;
		const unsigned int	GAME_ENGINE_KEY_DOWN_ALT =					21;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_SHIFT =			22;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_CONTROL =			23;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_ALT =				24;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_SHIFT =			25;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_CONTROL =		26;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_ALT =			27;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PAUSE =				28;
		const unsigned int	GAME_ENGINE_KEY_DOWN_CAPS_LOCK =			29;
		const unsigned int	GAME_ENGINE_KEY_DOWN_ESCAPE =				30;
		const unsigned int	GAME_ENGINE_KEY_DOWN_SPACE =				31;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PAGE_UP =				32;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PAGE_DOWN =			33;
		const unsigned int	GAME_ENGINE_KEY_DOWN_END =					34;
		const unsigned int	GAME_ENGINE_KEY_DOWN_HOME =					35;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_ARROW =			36;
		const unsigned int	GAME_ENGINE_KEY_DOWN_UP_ARROW =				37;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_ARROW =			38;
		const unsigned int	GAME_ENGINE_KEY_DOWN_DOWN_ARROW =			39;
		const unsigned int	GAME_ENGINE_KEY_DOWN_SELECT =				40;
		const unsigned int	GAME_ENGINE_KEY_DOWN_EXECUTE =				41;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PRINT_SCREEN =			42;
		const unsigned int	GAME_ENGINE_KEY_DOWN_INSERT =				43;
		const unsigned int	GAME_ENGINE_KEY_DOWN_DELETE =				44;
		const unsigned int	GAME_ENGINE_KEY_DOWN_HELP =					47;
		const unsigned int	GAME_ENGINE_KEY_DOWN_WINDOWS =				48;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_WINDOWS =			49;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_WINDOWS =		50;
		const unsigned int	GAME_ENGINE_KEY_DOWN_APPLICATION =			51;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_0 =				52;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_1 =				53;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_2 =				54;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_3 =				55;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_4 =				56;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_5 =				57;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_6 =				58;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_7 =				59;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_8 =				60;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_9 =				61;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_MULTIPLY =		62;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_ADD =			63;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_SEPARATOR =		64;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_SUBTRACT =		65;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_DECIMAL =		66;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUMPAD_DIVIDE =		67;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F1 =					68;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F2 =					69;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F3 =					70;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F4 =					71;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F5 =					72;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F6 =					73;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F7 =					74;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F8 =					75;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F9 =					76;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F10 =					77;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F11 =					78;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F12 =					79;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F13 =					80;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F14 =					81;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F15 =					82;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F16 =					83;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F17 =					84;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F18 =					85;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F19 =					86;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F20 =					87;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F21 =					88;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F22 =					89;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F23 =					90;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F24 =					91;
		const unsigned int	GAME_ENGINE_KEY_DOWN_NUM_LOCK =				92;
		const unsigned int	GAME_ENGINE_KEY_DOWN_SCROLL_LOCK =			93;
		const unsigned int	GAME_ENGINE_KEY_DOWN_ATTN =					94;
		const unsigned int	GAME_ENGINE_KEY_DOWN_CRSEL =				95;
		const unsigned int	GAME_ENGINE_KEY_DOWN_EXSEL =				96;
		const unsigned int	GAME_ENGINE_KEY_DOWN_EREOF =				97;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PLAY =					98;
		const unsigned int	GAME_ENGINE_KEY_DOWN_ZOOM =					99;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PA1 =					100;
		const unsigned int	GAME_ENGINE_KEY_DOWN_KEY_LOCK =				101;
		const unsigned int	GAME_ENGINE_KEY_DOWN_SEMICOLON =			102;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PLUS =					103;
		const unsigned int	GAME_ENGINE_KEY_DOWN_COMMA =				104;
		const unsigned int	GAME_ENGINE_KEY_DOWN_MINUS =				105;
		const unsigned int	GAME_ENGINE_KEY_DOWN_PERIOD =				106;
		const unsigned int	GAME_ENGINE_KEY_DOWN_DIVIDE =				107;
		const unsigned int	GAME_ENGINE_KEY_DOWN_TILDE =				108;
		const unsigned int	GAME_ENGINE_KEY_DOWN_LEFT_BRACKET =			109;
		const unsigned int	GAME_ENGINE_KEY_DOWN_SLASH =				110;
		const unsigned int	GAME_ENGINE_KEY_DOWN_RIGHT_BRACKET =		111;
		const unsigned int	GAME_ENGINE_KEY_DOWN_QUOTE =				112;
		const unsigned int	GAME_ENGINE_KEY_DOWN_0 =					113;
		const unsigned int	GAME_ENGINE_KEY_DOWN_1 =					114;
		const unsigned int	GAME_ENGINE_KEY_DOWN_2 =					115;
		const unsigned int	GAME_ENGINE_KEY_DOWN_3 =					116;
		const unsigned int	GAME_ENGINE_KEY_DOWN_4 =					117;
		const unsigned int	GAME_ENGINE_KEY_DOWN_5 =					118;
		const unsigned int	GAME_ENGINE_KEY_DOWN_6 =					119;
		const unsigned int	GAME_ENGINE_KEY_DOWN_7 =					120;
		const unsigned int	GAME_ENGINE_KEY_DOWN_8 =					121;
		const unsigned int	GAME_ENGINE_KEY_DOWN_9 =					122;
		const unsigned int	GAME_ENGINE_KEY_DOWN_A =					123;
		const unsigned int	GAME_ENGINE_KEY_DOWN_B =					124;
		const unsigned int	GAME_ENGINE_KEY_DOWN_C =					125;
		const unsigned int	GAME_ENGINE_KEY_DOWN_D =					126;
		const unsigned int	GAME_ENGINE_KEY_DOWN_E =					127;
		const unsigned int	GAME_ENGINE_KEY_DOWN_F =					128;
		const unsigned int	GAME_ENGINE_KEY_DOWN_G =					129;
		const unsigned int	GAME_ENGINE_KEY_DOWN_H =					130;
		const unsigned int	GAME_ENGINE_KEY_DOWN_I =					131;
		const unsigned int	GAME_ENGINE_KEY_DOWN_J =					132;
		const unsigned int	GAME_ENGINE_KEY_DOWN_K =					133;
		const unsigned int	GAME_ENGINE_KEY_DOWN_L =					134;
		const unsigned int	GAME_ENGINE_KEY_DOWN_M =					135;
		const unsigned int	GAME_ENGINE_KEY_DOWN_N =					136;
		const unsigned int	GAME_ENGINE_KEY_DOWN_O =					137;
		const unsigned int	GAME_ENGINE_KEY_DOWN_P =					138;
		const unsigned int	GAME_ENGINE_KEY_DOWN_Q =					139;
		const unsigned int	GAME_ENGINE_KEY_DOWN_R =					140;
		const unsigned int	GAME_ENGINE_KEY_DOWN_S =					141;
		const unsigned int	GAME_ENGINE_KEY_DOWN_T =					142;
		const unsigned int	GAME_ENGINE_KEY_DOWN_U =					143;
		const unsigned int	GAME_ENGINE_KEY_DOWN_V =					144;
		const unsigned int	GAME_ENGINE_KEY_DOWN_W =					145;
		const unsigned int	GAME_ENGINE_KEY_DOWN_X =					146;
		const unsigned int	GAME_ENGINE_KEY_DOWN_Y =					147;
		const unsigned int	GAME_ENGINE_KEY_DOWN_Z =					148;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_MOUSE_BUTTON =		149;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_MOUSE_BUTTON =		150;
		const unsigned int	GAME_ENGINE_KEY_UP_MIDDLE_MOUSE_BUTTON =	151;
		const unsigned int	GAME_ENGINE_KEY_UP_CANCEL =					152;
		const unsigned int	GAME_ENGINE_KEY_UP_BACKSPACE =				153;
		const unsigned int	GAME_ENGINE_KEY_UP_TAB =					154;
		const unsigned int	GAME_ENGINE_KEY_UP_CLEAR =					155;
		const unsigned int	GAME_ENGINE_KEY_UP_ENTER =					156;
		const unsigned int	GAME_ENGINE_KEY_UP_SHIFT =					157;
		const unsigned int	GAME_ENGINE_KEY_UP_CONTROL =				158;
		const unsigned int	GAME_ENGINE_KEY_UP_ALT =					159;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_SHIFT =				160;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_CONTROL =			161;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_ALT =				162;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_SHIFT =			163;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_CONTROL =			164;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_ALT =				165;
		const unsigned int	GAME_ENGINE_KEY_UP_PAUSE =					166;
		const unsigned int	GAME_ENGINE_KEY_UP_CAPS_LOCK =				167;
		const unsigned int	GAME_ENGINE_KEY_UP_ESCAPE =					168;
		const unsigned int	GAME_ENGINE_KEY_UP_SPACE =					169;
		const unsigned int	GAME_ENGINE_KEY_UP_PAGE_UP =				170;
		const unsigned int	GAME_ENGINE_KEY_UP_PAGE_DOWN =				171;
		const unsigned int	GAME_ENGINE_KEY_UP_END =					172;
		const unsigned int	GAME_ENGINE_KEY_UP_HOME =					173;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_ARROW =				174;
		const unsigned int	GAME_ENGINE_KEY_UP_UP_ARROW =				175;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_ARROW =			176;
		const unsigned int	GAME_ENGINE_KEY_UP_DOWN_ARROW =				177;
		const unsigned int	GAME_ENGINE_KEY_UP_SELECT =					178;
		const unsigned int	GAME_ENGINE_KEY_UP_EXECUTE =				179;
		const unsigned int	GAME_ENGINE_KEY_UP_PRINT_SCREEN =			180;
		const unsigned int	GAME_ENGINE_KEY_UP_INSERT =					181;
		const unsigned int	GAME_ENGINE_KEY_UP_DELETE =					182;
		const unsigned int	GAME_ENGINE_KEY_UP_HELP =					183;
		const unsigned int	GAME_ENGINE_KEY_UP_WINDOWS =				184;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_WINDOWS =			185;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_WINDOWS =			186;
		const unsigned int	GAME_ENGINE_KEY_UP_APPLICATION =			187;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_0 =				188;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_1 =				189;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_2 =				190;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_3 =				191;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_4 =				192;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_5 =				193;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_6 =				194;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_7 =				195;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_8 =				196;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_9 =				197;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_MULTIPLY =		198;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_ADD =				199;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_SEPARATOR =		200;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_SUBTRACT =		201;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_DECIMAL =			202;
		const unsigned int	GAME_ENGINE_KEY_UP_NUMPAD_DIVIDE =			203;
		const unsigned int	GAME_ENGINE_KEY_UP_F1 =						204;
		const unsigned int	GAME_ENGINE_KEY_UP_F2 =						205;
		const unsigned int	GAME_ENGINE_KEY_UP_F3 =						206;
		const unsigned int	GAME_ENGINE_KEY_UP_F4 =						207;
		const unsigned int	GAME_ENGINE_KEY_UP_F5 =						208;
		const unsigned int	GAME_ENGINE_KEY_UP_F6 =						209;
		const unsigned int	GAME_ENGINE_KEY_UP_F7 =						210;
		const unsigned int	GAME_ENGINE_KEY_UP_F8 =						211;
		const unsigned int	GAME_ENGINE_KEY_UP_F9 =						212;
		const unsigned int	GAME_ENGINE_KEY_UP_F10 =					213;
		const unsigned int	GAME_ENGINE_KEY_UP_F11 =					214;
		const unsigned int	GAME_ENGINE_KEY_UP_F12 =					215;
		const unsigned int	GAME_ENGINE_KEY_UP_F13 =					216;
		const unsigned int	GAME_ENGINE_KEY_UP_F14 =					217;
		const unsigned int	GAME_ENGINE_KEY_UP_F15 =					218;
		const unsigned int	GAME_ENGINE_KEY_UP_F16 =					219;
		const unsigned int	GAME_ENGINE_KEY_UP_F17 =					220;
		const unsigned int	GAME_ENGINE_KEY_UP_F18 =					221;
		const unsigned int	GAME_ENGINE_KEY_UP_F19 =					222;
		const unsigned int	GAME_ENGINE_KEY_UP_F20 =					223;
		const unsigned int	GAME_ENGINE_KEY_UP_F21 =					224;
		const unsigned int	GAME_ENGINE_KEY_UP_F22 =					225;
		const unsigned int	GAME_ENGINE_KEY_UP_F23 =					226;
		const unsigned int	GAME_ENGINE_KEY_UP_F24 =					227;
		const unsigned int	GAME_ENGINE_KEY_UP_NUM_LOCK =				228;
		const unsigned int	GAME_ENGINE_KEY_UP_SCROLL_LOCK =			229;
		const unsigned int	GAME_ENGINE_KEY_UP_ATTN =					230;
		const unsigned int	GAME_ENGINE_KEY_UP_CRSEL =					231;
		const unsigned int	GAME_ENGINE_KEY_UP_EXSEL =					232;
		const unsigned int	GAME_ENGINE_KEY_UP_EREOF =					233;
		const unsigned int	GAME_ENGINE_KEY_UP_PLAY =					234;
		const unsigned int	GAME_ENGINE_KEY_UP_ZOOM =					235;
		const unsigned int	GAME_ENGINE_KEY_UP_PA1 =					236;
		const unsigned int	GAME_ENGINE_KEY_UP_KEY_LOCK =				237;
		const unsigned int	GAME_ENGINE_KEY_UP_SEMICOLON =				238;
		const unsigned int	GAME_ENGINE_KEY_UP_PLUS =					239;
		const unsigned int	GAME_ENGINE_KEY_UP_COMMA =					240;
		const unsigned int	GAME_ENGINE_KEY_UP_MINUS =					241;
		const unsigned int	GAME_ENGINE_KEY_UP_PERIOD =					242;
		const unsigned int	GAME_ENGINE_KEY_UP_DIVIDE =					243;
		const unsigned int	GAME_ENGINE_KEY_UP_TILDE =					244;
		const unsigned int	GAME_ENGINE_KEY_UP_LEFT_BRACKET =			245;
		const unsigned int	GAME_ENGINE_KEY_UP_SLASH =					246;
		const unsigned int	GAME_ENGINE_KEY_UP_RIGHT_BRACKET =			247;
		const unsigned int	GAME_ENGINE_KEY_UP_QUOTE =					248;
		const unsigned int	GAME_ENGINE_KEY_UP_0 =						249;
		const unsigned int	GAME_ENGINE_KEY_UP_1 =						250;
		const unsigned int	GAME_ENGINE_KEY_UP_2 =						251;
		const unsigned int	GAME_ENGINE_KEY_UP_3 =						252;
		const unsigned int	GAME_ENGINE_KEY_UP_4 =						253;
		const unsigned int	GAME_ENGINE_KEY_UP_5 =						254;
		const unsigned int	GAME_ENGINE_KEY_UP_6 =						255;
		const unsigned int	GAME_ENGINE_KEY_UP_7 =						256;
		const unsigned int	GAME_ENGINE_KEY_UP_8 =						257;
		const unsigned int	GAME_ENGINE_KEY_UP_9 =						258;
		const unsigned int	GAME_ENGINE_KEY_UP_A =						259;
		const unsigned int	GAME_ENGINE_KEY_UP_B =						260;
		const unsigned int	GAME_ENGINE_KEY_UP_C =						261;
		const unsigned int	GAME_ENGINE_KEY_UP_D =						262;
		const unsigned int	GAME_ENGINE_KEY_UP_E =						263;
		const unsigned int	GAME_ENGINE_KEY_UP_F =						264;
		const unsigned int	GAME_ENGINE_KEY_UP_G =						265;
		const unsigned int	GAME_ENGINE_KEY_UP_H =						266;
		const unsigned int	GAME_ENGINE_KEY_UP_I =						267;
		const unsigned int	GAME_ENGINE_KEY_UP_J =						268;
		const unsigned int	GAME_ENGINE_KEY_UP_K =						269;
		const unsigned int	GAME_ENGINE_KEY_UP_L =						270;
		const unsigned int	GAME_ENGINE_KEY_UP_M =						271;
		const unsigned int	GAME_ENGINE_KEY_UP_N =						272;
		const unsigned int	GAME_ENGINE_KEY_UP_O =						273;
		const unsigned int	GAME_ENGINE_KEY_UP_P =						274;
		const unsigned int	GAME_ENGINE_KEY_UP_Q =						275;
		const unsigned int	GAME_ENGINE_KEY_UP_R =						276;
		const unsigned int	GAME_ENGINE_KEY_UP_S =						277;
		const unsigned int	GAME_ENGINE_KEY_UP_T =						278;
		const unsigned int	GAME_ENGINE_KEY_UP_U =						279;
		const unsigned int	GAME_ENGINE_KEY_UP_V =						280;
		const unsigned int	GAME_ENGINE_KEY_UP_W =						281;
		const unsigned int	GAME_ENGINE_KEY_UP_X =						282;
		const unsigned int	GAME_ENGINE_KEY_UP_Y =						283;
		const unsigned int	GAME_ENGINE_KEY_UP_Z =						284;
		const unsigned int	GAME_ENGINE_RAW_MOUSE_MOVE =				285;
		const unsigned int	GAME_ENGINE_MOUSE_MOVE =					286;
		const unsigned int	GAME_ENGINE_RAW_VERTICAL_MOUSE_WHEEL =		287;
		const unsigned int	GAME_ENGINE_RAW_HORIZONTAL_MOUSE_WHEEL =	288;
		const unsigned int	GAME_ENGINE_HORIZONTAL_MOUSE_WHEEL =		289;
		const unsigned int	GAME_ENGINE_VERTICAL_MOUSE_WHEEL =			290;
		const unsigned int	GAME_ENGINE_INIT =							291;
		const unsigned int	GAME_ENGINE_CLOSE =							292;
		const unsigned int	GAME_ENGINE_CLOSE_WINDOWS =					292;
		const unsigned int	GAME_ENGINE_INIT_KINECT =					293;
		const unsigned int	GAME_ENGINE_CLOSE_KINECT =					294;
		const unsigned int	GAME_ENGINE_KINECT_SKELETON =				295;
		



		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_HDC =							1;
		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_FIND_PIXEL_FORMAT =				2;
		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_SET_PIXEL_FORMAT =				3;
		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_CREATE_RENDERING_CONTEXT =		4;
		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_OPENGL_ACTIVATE_RENDERING_CONTEXT =	5;
		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_DIRECTX_CREATE_DIRECT3D =				6;
		const unsigned int	GAME_ENGINE_ERROR_CODE_RENDERMANAGER_DIRECTX_CREATE_DIRECT3DDEVICE =		7;
		const unsigned int	GAME_ENGINE_ERROR_CODE_INPUTMANAGER_KINECT_INITIALIZE =						8;
		const unsigned int	GAME_ENGINE_ERROR_CODE_INPUTMANAGER_KINECT_SKELETON_INITIALIZE =			9;
		const unsigned int	GAME_ENGINE_ERROR_CODE_INPUT_MANAGER_KINECT_DEPTH_STREAM_INITIALIZE =		10;
		const unsigned int	GAME_ENGINE_ERROR_CODE_INPUT_MANAGER_KINECT_THREAD_INITIALIZE =				11;



		class	SkeletonPoint
		{
			public:
				
				SkeletonPoint()	:	_x(0) , _y(0)	{};

				FLOAT	_x;
				FLOAT	_y;
		};

		class	Skeleton
		{
			public:	

				Skeleton()	:	_skeleton_no(0) , _used(false)	{};


				SkeletonPoint	_points[NUI_SKELETON_POSITION_COUNT];
				unsigned int	_skeleton_no;
				bool			_used;
		};

		
		DLL_OUTPUT	void	TriggerEvent( const unsigned int message , const Message& parameters = Message() );
		DLL_OUTPUT	void	RegisterEvent( const unsigned int message );
		DLL_OUTPUT	void	UnregisterEvent( const unsigned int message );
		void				AddEventWatch( const unsigned int message , EngineObject* object = NULL );
		void				RemoveEventWatch( const unsigned int message , EngineObject* object = NULL );

		// Main Rendering Loop
		DLL_OUTPUT int		MainLoop();
		// Initialization function
		DLL_OUTPUT void		InitialRegistration();

	};

#endif		/* _GAME_ENGINE_DEFINES_H_ */