#include	"ErrorException.h"

using		namespace GameEngine;



ErrorException::ErrorException( void )	:	_code(0) , _description(L"") , _file(L"") , _line(0) , _error_text(L"")	{};
ErrorException::ErrorException( const unsigned int code , const wstring& description , const wstring& file , const unsigned int line )	:	
	_code(code) , _description(description) , _file(file) , _line(line)
{
	this->_update_error_text();
};

ErrorException::ErrorException( const ErrorException& exception )	:	
	_code(exception.code()) , _description(exception.description()) , _file(exception.file()) , _line(exception.line())
{
	this->_update_error_text();
}

ErrorException::~ErrorException( void ) throw()	{};