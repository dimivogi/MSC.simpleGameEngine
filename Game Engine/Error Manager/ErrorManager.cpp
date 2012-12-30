#include	"ErrorManager.h"

using		namespace GameEngine;



ErrorManager	ErrorManager::_error_manager;



//Gets current time as string in the form: hours:mins:secs
const wstring ErrorManager::_date()
{
	wstringstream	DateStr;
	wstring			day = L"";
	wstring			month = L"";
	unsigned int	year = 0;
	time_t			ctTime = 0;
	#ifdef	_WIN32
		struct tm		pTime;
	#else
		struct tm*		pTime;
	#endif	/* _WIN32 */



	time(&ctTime);

	#ifdef	_WIN32
		localtime_s(&pTime,&ctTime );
	#else
		ptime = localtime(&ctTime);
	#endif	/* _WIN32 */


	#ifdef	_WIN32
		switch( pTime.tm_wday )
	#else
		switch( pTime->tm_wday )
	#endif	/* _WIN32 */
		{
			case	0:	day = L"Sunday";	break;
			case	1:	day = L"Monday";	break;
			case	2:	day = L"Tuesday";	break;
			case	3:	day = L"Wednesday";	break;
			case	4:	day = L"Thursday";	break;
			case	5:	day = L"Friday";	break;
			case	6:	day = L"Saturday";	break;
		}

	#ifdef	_WIN32
		switch( pTime.tm_mon )
	#else
		switch( pTime->tm_mon )
	#endif	/* _WIN32 */
		{
			case	0:	month = L"January";	break;
			case	1:	month = L"February";	break;
			case	2:	month = L"March";	break;
			case	3:	month = L"April";	break;
			case	4:	month = L"May";	break;
			case	5:	month = L"June";	break;
			case	6:	month = L"July";	break;
			case	7:	month = L"August";	break;
			case	8:	month = L"September";	break;
			case	9:	month = L"October";	break;
			case	10:	month = L"November";	break;
			case	11:	month = L"December";	break;
		}

	#ifdef	_WIN32
		year = pTime.tm_year + 1900;
	#else
		year = pTime->tm_year + 1900;
	#endif	/* _WIN32 */
	
	DateStr	<< day << L" ";
	#ifdef	_WIN32
		DateStr	<< pTime.tm_mday << L" ";
	#else
		DateStr	<< pTime->tm_mday << L" ";
	#endif	/* _WIN32 */
	DateStr	<< month << L" " << year;


	return DateStr.str();
};

//Gets current time as string in the form: hours:mins:secs
const wstring ErrorManager::_time()
{
	wstringstream	TimeStr;
	time_t			ctTime = 0;
	#ifdef	_WIN32
		struct tm		pTime;
	#else
		struct tm*		pTime;
	#endif



	time(&ctTime);

	#ifdef	_WIN32
		localtime_s(&pTime,&ctTime );

		TimeStr << std::setw(2) << std::setfill(L'0') <<pTime.tm_hour << L":";
		TimeStr << std::setw(2) << std::setfill(L'0') <<pTime.tm_min << L":";
		TimeStr << std::setw(2) << std::setfill(L'0') <<pTime.tm_sec;
	#else
		ptime = localtime(&ctTime);

		TimeStr << std::setw(2) << std::setfill(L'0') <<pTime->tm_hour << L":";
		TimeStr << std::setw(2) << std::setfill(L'0') <<pTime->tm_min << L":";
		TimeStr << std::setw(2) << std::setfill(L'0') <<pTime->tm_sec;
	#endif


	return TimeStr.str();
};


ErrorManager::ErrorManager()	:	_default_log_file(L"ErrorLog.txt") , _display_message(false)	{};
ErrorManager::~ErrorManager()	{};


ErrorManager* ErrorManager::GetErrorManager()	{ return &_error_manager; };

//Opens log file
void	ErrorManager::Create( const wstring* filename  , const unsigned int clean )
{
	ios_base::open_mode	flags = wofstream::out;



	try
	{	
		if ( !_logFile.is_open() )
		{
			if ( clean > 0 )
				flags |= wofstream::trunc;
			else
				flags |= wofstream::app;

			_logFile.setf(wofstream::badbit|wofstream::failbit);

			if ( filename != NULL )
				_logFile.open(filename->c_str(),flags);
			else
				_logFile.open(this->_default_log_file.c_str(),flags);

			this->RegisterEvent(GAME_ENGINE_ERROR_DISPLAY_MESSAGE);
			this->RegisterEvent(GAME_ENGINE_ERROR_NO_DISPLAY_MESSAGE);
			this->RegisterEvent(GAME_ENGINE_CLOSE);
			TriggerEvent(GAME_ENGINE_ERROR_FILE_OPENED);
		}
	}
	catch( exception& )
	{
		TriggerEvent(GAME_ENGINE_ERROR_FILE_NOT_OPENED);
	}
};

//Commits information to file and clears text cache
void ErrorManager::_flush()
{
	if ( this->_logFile.is_open() )
	{
		this->_logFile << _logBuffer.str();
		this->_logFile.flush();
		wcerr << this->_logBuffer.str() << endl;
		this->_logBuffer.str(L"");
		TriggerEvent(GAME_ENGINE_ERROR_MESSAGE_LOGGED,Message());
	}
	else
		TriggerEvent(GAME_ENGINE_ERROR_MESSAGE_UNLOGGED,Message());
};

//Close log file
void ErrorManager::Close()
{ 
	if ( this->_logFile.is_open() )
		this->_logFile.close();
};

void ErrorManager::LogException( const ErrorException &e)
{
	if ( this->_logFile.is_open() )
	{
		wstring			time = this->_time();
		wstring			date = this->_date();
		wstringstream	output;

		
		output			<< L"Date:\t\t\t" << date << L"\n" << L"Time:\t\t\t" << time << L"\n" << e;
		this->_logFile	<< output.str() << endl;
		wcerr			<< output.str() << endl;
		
		if ( this->_display_message )
			MessageBoxW(0,output.str().c_str(),L"An Error has occurred!",MB_TOPMOST|MB_OK|MB_ICONEXCLAMATION);

		TriggerEvent(GAME_ENGINE_ERROR_LOGGED,Message());
	}
	else
		TriggerEvent(GAME_ENGINE_ERROR_UNLOGGED,Message());
};

void ErrorManager::Output( const wchar_t* message )
{
	_logBuffer << message << '\n';
	this->_flush();
};

void	ErrorManager::OnEvent( const unsigned int message , const Message& parameters )
{
	if ( message == GAME_ENGINE_ERROR_DISPLAY_MESSAGE )
		this->_display_message = true;
	else if ( message == GAME_ENGINE_ERROR_NO_DISPLAY_MESSAGE )
		this->_display_message = false;
	else if ( message == GAME_ENGINE_INIT )
		this->Create(reinterpret_cast<const wstring*>(parameters.pointer(0)),static_cast<unsigned int>(parameters.data(0)));
	else if ( message == GAME_ENGINE_CLOSE )
		this->Close();
};

void	ErrorManager::RegisterEvent( const unsigned int message )
{
	AddEventWatch(message,&_error_manager);
};

void	ErrorManager::UnregisterEvent( const unsigned int message )
{
	RemoveEventWatch(message,&_error_manager);
};