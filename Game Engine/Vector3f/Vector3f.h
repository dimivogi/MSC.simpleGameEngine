#pragma	once

#include	"..\GameEngineDefines.h"
#include	<iostream>
using		namespace std;



namespace	GameEngine
{

	class Vector3f
	{
		private:

			float							_data[3];


		public:

			DLL_OUTPUT static const float	_V3EPSILON;

			DLL_OUTPUT explicit	Vector3f( const float x = 0.0f , const float y = 0.0f , const float z = 0.0f );


			DLL_OUTPUT void					set( const float x , const float y , const float z );
			DLL_OUTPUT void					x( const float value );
			DLL_OUTPUT void					y( const float value );
			DLL_OUTPUT void					z( const float value );
			DLL_OUTPUT void					r( const float value );
			DLL_OUTPUT void					g( const float value );
			DLL_OUTPUT void					b( const float value );
			DLL_OUTPUT void					s( const float value );
			DLL_OUTPUT void					t( const float value );
			DLL_OUTPUT void					p( const float value );

			DLL_OUTPUT const float*			get() const;
			DLL_OUTPUT float				x() const;
			DLL_OUTPUT float				y() const;
			DLL_OUTPUT float				z() const;
			DLL_OUTPUT float				r() const;
			DLL_OUTPUT float				g() const;
			DLL_OUTPUT float				b() const;
			DLL_OUTPUT float				s() const;
			DLL_OUTPUT float				t() const;
			DLL_OUTPUT float				p() const;

		
			DLL_OUTPUT Vector3f&			operator+= ( const Vector3f& input );
			DLL_OUTPUT Vector3f&			operator-= ( const Vector3f& input );
			DLL_OUTPUT Vector3f&			operator*= ( const float& input );	// scale
			DLL_OUTPUT Vector3f&			operator^= ( const Vector3f& input );	// cross product
			DLL_OUTPUT Vector3f				operator+ () const;	// unary
			DLL_OUTPUT Vector3f				operator- () const;


			DLL_OUTPUT void					add( const Vector3f& input );
			DLL_OUTPUT void					sub( const Vector3f& input );
			DLL_OUTPUT void					scale( const float value );
			DLL_OUTPUT float				dot_product( const Vector3f&	input ) const;
			DLL_OUTPUT void					cross_product( const Vector3f&  input );
			DLL_OUTPUT float				length() const;
			DLL_OUTPUT void					normalize();


			DLL_OUTPUT void					write( ostream& out ) const;
			DLL_OUTPUT void					read( istream& in );
	};


	DLL_OUTPUT Vector3f	operator+ ( const Vector3f& input , const Vector3f& input2 );
	DLL_OUTPUT Vector3f	operator- ( const Vector3f& input , const Vector3f& input2 );
	DLL_OUTPUT Vector3f	operator^ ( const Vector3f& input , const Vector3f& input2 );	// cross product
	DLL_OUTPUT float	operator* ( const Vector3f& input , const Vector3f& input2 );	// dot product
	DLL_OUTPUT Vector3f	operator* ( const Vector3f& input , const float& input2 );
	DLL_OUTPUT Vector3f	operator* ( const float& input , const Vector3f& input2 );
	DLL_OUTPUT bool		operator== ( const Vector3f& input , const Vector3f& input2 );	// boolean
	DLL_OUTPUT bool		operator!= ( const Vector3f& input , const Vector3f& input2);

	DLL_OUTPUT ostream&	operator<< ( ostream& stream , const Vector3f& output );
	DLL_OUTPUT istream&	operator>> ( istream& stream , Vector3f& input );




	/****************************************************************************************
	*****************************************************************************************
	--------------------------------- Function Definitions ----------------------------------
	*****************************************************************************************
	****************************************************************************************/



	inline void				Vector3f::set( const float x , const float y , const float z )	{ this->x(x); this->y(y); this->z(z); };
	inline void				Vector3f::x( const float value )								{ this->_data[0] = value; };
	inline void				Vector3f::y( const float value )								{ this->_data[1] = value; };
	inline void				Vector3f::z( const float value )								{ this->_data[2] = value; };
	inline void				Vector3f::r( const float value )								{ this->x(value); };
	inline void				Vector3f::g( const float value )								{ this->y(value); };
	inline void				Vector3f::b( const float value )								{ this->z(value); };
	inline void				Vector3f::s( const float value )								{ this->x(value); };
	inline void				Vector3f::t( const float value )								{ this->y(value); };
	inline void				Vector3f::p( const float value )								{ this->z(value); };


	inline const float*	Vector3f::get() const												{ return this->_data; };
	inline float			Vector3f::x()  const											{ return this->_data[0]; };
	inline float			Vector3f::y() const												{ return this->_data[1]; };
	inline float			Vector3f::z() const												{ return this->_data[2]; };
	inline float			Vector3f::r() const												{ return this->x(); };
	inline float			Vector3f::g() const												{ return this->y(); };
	inline float			Vector3f::b() const												{ return this->z(); };
	inline float			Vector3f::s() const												{ return this->x(); };
	inline float			Vector3f::t() const												{ return this->y(); };
	inline float			Vector3f::p() const												{ return this->z(); };


	inline Vector3f&		Vector3f::operator+= ( const Vector3f& input )					{ this->add(input);	return *this; };
	inline Vector3f&		Vector3f::operator-= ( const Vector3f& input )					{ this->sub(input);	return *this; };
	inline Vector3f&		Vector3f::operator*= ( const float& input )						{ this->scale(input);	return *this; };
	inline Vector3f&		Vector3f::operator^= ( const Vector3f& input )					{ this->cross_product(input);	return *this; };
	inline Vector3f			Vector3f::operator+ () const									{ return *this; };
	inline Vector3f			Vector3f::operator- () const									{ return Vector3f(-this->x(),-this->y(),-this->z()); };
	inline Vector3f			operator+ ( const Vector3f& input , const Vector3f& input2 )	{ return Vector3f(input) += input2; };
	inline Vector3f			operator- ( const Vector3f& input , const Vector3f& input2 )	{ return Vector3f(input) -= input2; };
	inline Vector3f			operator^ ( const Vector3f& input , const Vector3f& input2 )	{ return Vector3f(input) ^= input2; };
	inline float			operator* ( const Vector3f& input , const Vector3f& input2 )	{ return input.dot_product(input2); };
	inline Vector3f			operator* ( const Vector3f& input , const float& input2 )		{ return Vector3f(input) *= input2; };
	inline Vector3f			operator* ( const float& input , const Vector3f& input2 )		{ return Vector3f(input2) *= input; };
	inline bool				operator== ( const Vector3f& input , const Vector3f& input2 )	{ return ( abs(input.x()-input2.x()) < Vector3f::_V3EPSILON  &&  abs(input.y()-input2.y()) < Vector3f::_V3EPSILON  &&  abs(input.z()-input2.z()) < Vector3f::_V3EPSILON ); };
	inline bool				operator!= ( const Vector3f& input , const Vector3f& input2)	{ return ( abs(input.x()-input2.x()) > Vector3f::_V3EPSILON  ||  abs(input.y()-input2.y()) > Vector3f::_V3EPSILON  ||  abs(input.z()-input2.z()) > Vector3f::_V3EPSILON ); };


	inline void				Vector3f::add( const Vector3f& input )
	{
		this->x(this->x() + input.x());
		this->y(this->y() + input.y());
		this->z(this->z() + input.z());
	};

	inline void				Vector3f::sub( const Vector3f& input )
	{
		this->x(this->x() - input.x());
		this->y(this->y() - input.y());
		this->z(this->z() - input.z());
	};

	inline void				Vector3f::scale( const float value )
	{
		this->x(this->x() * value);
		this->y(this->y() * value);
		this->z(this->z() * value);
	};

	inline float			Vector3f::dot_product( const Vector3f&	input ) const			{ return ( this->x()*input.x() + this->y()*input.y() + this->z()*input.z() ); };
	inline void				Vector3f::cross_product( const Vector3f& input )
	{
		float	x;
		float	y;
		float	z;



		x = this->y()*input.z() - this->z()*input.y();
		y = this->z()*input.x() - this->x()*input.z();
		z = this->x()*input.y() - this->y()*input.x();

		this->x(x);
		this->y(y);
		this->z(z);
	};

	inline float			Vector3f::length() const										{ return sqrt(this->dot_product(*this)); };
	inline void				Vector3f::normalize()
	{
		float			length = this->length();



		if ( length > 0 )
			this->scale(1.0f/length);
	}


	inline void					Vector3f::write( ostream& out ) const						{ out	<< "(" << this->x() << "," << this->y() << "," << this->z() << ")"; };
	inline void					Vector3f::read( istream& in )
	{
		char	temp;
		float	temp1 , temp2 , temp3;



		in	>> temp >> temp1 >> temp >> temp2 >> temp >> temp3 >> temp;
		this->x(temp1);
		this->y(temp2);
		this->z(temp3);
	}

	inline ostream&		operator<< ( ostream& stream , const Vector3f& output )				{ output.write(stream);	return stream; };
	inline istream&		operator>> ( istream& stream , Vector3f& input )					{ input.read(stream);	return stream; };

};