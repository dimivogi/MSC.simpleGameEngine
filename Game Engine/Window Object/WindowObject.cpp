#include	"WindowObject.h"
#include	"..\Render Manager\RenderManager.h"

using		namespace GameEngine;



WindowObject::WindowObject( HINSTANCE hInstance )	:	
	_hInstance(hInstance) , _width(400) , _height(400) , _x(0) , _y(0) 		{};
WindowObject::~WindowObject()												{};


void	WindowObject::set_size( const unsigned int width , const unsigned int height )
{
	if ( width > 0 )
		this->_width = width;
	else
		this->_width = 1;

	if ( height > 0 )
		this->_height = height;
	else
		this->_height = 1;
};


unsigned int	WindowObject::handle() const								{ return this->_window_info._id; };
const HDC		WindowObject::gl_content() const							{ return this->_window_info._opengl_id; };
const LPDIRECT3DDEVICE9	WindowObject::directx_device() const				{ return this->_window_info._directx_device; };
void	WindowObject::get_size( unsigned int& width , unsigned int& height ) const
{
	width = this->_width;
	height = this->_height;
};

void	WindowObject::OnEvent( const unsigned int , const Message& )		{};
void	WindowObject::OnCreate()											{};
void	WindowObject::OnDestroy()											{};
void	WindowObject::OnRender()											{};
void	WindowObject::OnResize( const unsigned int , const unsigned int )	{};
void	WindowObject::OnIdle()												{ RenderManager::GetRenderManager()->RequestRepaint(this->_window_info._id); };


void	WindowObject::Create( const wstring& name , bool opengl )
{
	if ( !this->_window_info._id )
	{
		InitialisationInfo	info = RenderManager::GetRenderManager()->CreateNewWindow(this->_hInstance,name,this->_width,this->_height,this->_x,this->_y,this,opengl);



		if ( info._id > 0 )
		{
			this->_window_info = info;
			this->OnCreate();
		}
	}
};

void	WindowObject::Close()
{
	if ( this->_window_info._id )
		RenderManager::GetRenderManager()->CloseWindow(this->_window_info._id);
};

void	WindowObject::Show()
{
	if ( this->_window_info._id )
		RenderManager::GetRenderManager()->ShowWindow(this->_window_info._id);
};

void	WindowObject::Hide()
{
	if ( this->_window_info._id )
		RenderManager::GetRenderManager()->HideWindow(this->_window_info._id);
};

void	WindowObject::Exit()
{
	RenderManager::GetRenderManager()->Exit();
};

void	WindowObject::SetInitialPosition( const unsigned int x , const unsigned int y )
{
	this->_x = x;
	this->_y = y;
};


void	WindowObject::SwapBuffers()
{
	if ( this->_window_info._opengl_id )
		::SwapBuffers(this->_window_info._opengl_id);
};


double	WindowObject::GetTime()
{
	return RenderManager::GetRenderManager()->GetTime();
}