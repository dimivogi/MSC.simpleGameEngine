#pragma	once

#include	<vector>
#include	"..\GameEngineMacros.h"

using		namespace std;



#ifndef	_MESSAGE_H_
	#define	_MESSAGE_H_


	namespace	GameEngine
	{
		// Class used to communicate vauable information on events
		class Message
		{
			private:

				vector<long double>				_data;
				vector<void*>					_pointers;


			public:

				DLL_OUTPUT explicit				Message( const unsigned int data_size = 0 , const unsigned int pointer_size = 0 );


				DLL_OUTPUT void					data( const unsigned int position , const long double data );
				DLL_OUTPUT void					data( const vector<long double>& data );
				DLL_OUTPUT void					pointer( const unsigned int position , void* pointer );
				DLL_OUTPUT void					pointers( const vector<void*>& pointers );

				DLL_OUTPUT long double			data( const unsigned int position ) const;
				DLL_OUTPUT vector<long double>	data() const;
				DLL_OUTPUT unsigned int			data_size() const;
				DLL_OUTPUT void*				pointer( const unsigned int position ) const;
				DLL_OUTPUT vector<void*>		pointers() const;
				DLL_OUTPUT unsigned int			pointers_size() const;
		};



		/*
			Function Definitions
		*/


		inline void					Message::data( const unsigned int position , const long double data )
		{
			if ( position < this->_data.size() )
				this->_data[position] = data;
		};

		inline void					Message::data( const vector<long double>& data )
		{
			this->_data = data;
		};

		inline void					Message::pointer( const unsigned int position , void* pointer )
		{
			if ( position < this->_pointers.size() )
				this->_pointers[position] = pointer;
		};

		inline void					Message::pointers( const vector<void*>& pointers )
		{
			this->_pointers = pointers;
		}


		inline long double			Message::data( const unsigned int position ) const
		{
			if ( position < this->_data.size() )
				return this->_data[position];
			else
				return 0.0;
		};

		inline vector<long double>	Message::data() const
		{
			return this->_data;
		};

		inline unsigned int			Message::data_size() const
		{
			return this->_data.size();
		};

		inline void*				Message::pointer( const unsigned int position ) const
		{
			if ( position < this->_pointers.size() )
				return this->_pointers[position];
			else
				return NULL;
		};

		inline vector<void*>		Message::pointers() const
		{
			return this->_pointers;
		}

		inline unsigned int			Message::pointers_size() const
		{
			return this->_pointers.size();
		};
	};


#endif	/* _MESSAGE_H_ */