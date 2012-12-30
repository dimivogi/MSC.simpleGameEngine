#include	"openglWindow.h"



OpenGLWindow::OpenGLWindow( HINSTANCE hInstance , GameManager* manager )	: WindowObject(hInstance) , _manager(manager)	{};


void	OpenGLWindow::OnCreate()
{	
	this->_manager->init_content(this->gl_content());
};

void	OpenGLWindow::OnDestroy()
{
	this->_manager->destroy_content(this->gl_content());
};

void	OpenGLWindow::OnRender()
{
	unsigned int	width;
	unsigned int	height;


	this->get_size(width,height);
	this->_manager->update_time(this->GetTime());
	this->_manager->render(width,height);
	WindowObject::SwapBuffers();
};

void	OpenGLWindow::OnResize( const unsigned int width , const unsigned int height )
{
	this->set_size(width,height);
	this->_manager->resize(width,height);
};

void	OpenGLWindow::OnIdle()
{
	WindowObject::OnIdle();
};

void	OpenGLWindow::Create( const wstring& name )
{
	WindowObject::Create(name,true);
};