#include	"Vector3f.h"



const float				GameEngine::Vector3f::_V3EPSILON = 0.001f;


GameEngine::Vector3f::Vector3f( const float x , const float y , const float z )	{ this->set(x,y,z); };