#pragma	once

#include	<string>
#include	<sstream>
#include	<iostream>
#include	<exception>
#include	"..\GameEngineDefines.h"

using		namespace std;



#ifndef		_ERROR_EXCEPTION_H_
	#define	_ERROR_EXCEPTION_H_


	namespace	GameEngine
	{

		class	ErrorException	:	public exception
		{
			private:

				unsigned int		_code;
				wstring				_description;
				wstring				_file;
				unsigned int		_line;
				wstring				_error_text;


				void				_update_error_text();
				const char*			what();

			public:

				DLL_OUTPUT	ErrorException();
				DLL_OUTPUT	ErrorException( const unsigned int code , const wstring& description , const wstring& filename , const unsigned int line );
				DLL_OUTPUT	ErrorException( const ErrorException& exception );
				DLL_OUTPUT	~ErrorException() throw();


				DLL_OUTPUT	ErrorException&	operator=( const ErrorException& exception );


				void						code( const unsigned int error );
				void						description( const wstring& description );
				void						file( const wstring& file );
				void						line( const unsigned int line );

				unsigned int				code() const;
				wstring						description() const;
				wstring						file() const;
				unsigned int				line() const;
				DLL_OUTPUT	wstring			error_text() const;
				// Override std::exception::what
				DLL_OUTPUT	const wchar_t*	what( const int ) const;	// dummy variable to enable compiling since the return value differs
		};


		DLL_OUTPUT	wostream&	operator<<( wostream& stream , const ErrorException& exception );



		inline void				ErrorException::_update_error_text()
		{
			wstringstream	ErrStr;



			ErrStr	<< L"Source File:\t\t" << this->_file << L"\nLine Number:\t\t" << this->_line
					<< L"\nError Code:\t\t" << this->_code << L"\nError Description:\t" << this->_description << "\n";
			this->_error_text = ErrStr.str();
		};


		inline ErrorException&	ErrorException::operator=( const ErrorException& exception )
		{
			if ( this != &exception )
			{
				this->code(exception.code());
				this->description(exception.description());
				this->file(exception.file());
				this->line(exception.line());
				this->_update_error_text();
			}


			return *this;
		};


		inline void				ErrorException::code( const unsigned int error )			{ this->_code = error;	this->_update_error_text(); };
		inline void				ErrorException::description( const wstring& description )	{ this->_description = description;	this->_update_error_text(); };
		inline void				ErrorException::file( const wstring& file )					{ this->_file = file;	this->_update_error_text(); };
		inline void				ErrorException::line( const unsigned int line )				{ this->_line = line;	this->_update_error_text(); };

		inline unsigned int		ErrorException::code() const								{ return this->_code; };
		inline wstring			ErrorException::description() const							{ return this->_description; };
		inline wstring			ErrorException::file() const								{ return this->_file; };
		inline unsigned int		ErrorException::line() const								{ return this->_line; };
		inline wstring			ErrorException::error_text() const							{ return this->_error_text; };
		inline const char*		ErrorException::what()										{ return NULL; };
		inline const wchar_t*	ErrorException::what( const int ) const						{ return this->_error_text.c_str(); };	// i is there to avoid level 4 warning;
	

		#ifdef	_WINDLL
			DLL_OUTPUT	inline wostream&	operator<<( wostream& stream , const ErrorException& exception )
			{
				stream << exception.error_text();


				return stream;
			};
		#endif	/* _WINDLL */
	};


#endif		/* _ERROR_EXCEPTION_H_ */