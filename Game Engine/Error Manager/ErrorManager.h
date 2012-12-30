#pragma	once

#include	<string>
#include	<sstream>
#include	<fstream>
#include	<iostream>
#include	<iomanip>
#include	<time.h>
#include	"ErrorException.h"



#ifndef		_ERROR_MANAGER_H_
	#define	_ERROR_MANAGER_H_


	namespace	GameEngine
	{

		class	ErrorManager	:	public EngineObject
		{
			private:

				static ErrorManager					_error_manager;
				wstringstream						_logBuffer;
				wofstream							_logFile;
				wstring								_default_log_file;
				bool								_display_message;

				void								_flush();
				static const wstring				_date();
				static const wstring				_time();

				ErrorManager();
				virtual ~ErrorManager();


			public :

				DLL_OUTPUT	static ErrorManager*	GetErrorManager();
				void								Create( const wstring* filename  , const unsigned int clean = 0 );
				void								Close();
				DLL_OUTPUT	void					LogException( const ErrorException& e );
				DLL_OUTPUT	void					Output( const wchar_t* message );
				void								OnEvent( const unsigned int message , const Message& parameters );
				void								RegisterEvent( const unsigned int message );
				void								UnregisterEvent( const unsigned int message );
		};

	};


#endif		/* _ERROR_MANAGER_H_ */