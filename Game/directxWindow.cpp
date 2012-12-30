#include	"directxWindow.h"



DirectXWindow::DirectXWindow( HINSTANCE hInstance , GameManager* manager )	: WindowObject(hInstance) , _manager(manager)	{};


void	DirectXWindow::OnCreate()
{
	unsigned int	width;
	unsigned int	height;



	this->get_size(width,height);
	this->_manager->init_content(this->directx_device());
	this->_manager->resize(width,height,this->directx_device());
};

void	DirectXWindow::OnDestroy()
{
	this->_manager->destroy_content(this->directx_device());
};

void	DirectXWindow::OnRender()
{
	this->_manager->render(this->directx_device());
};

void	DirectXWindow::OnResize( const unsigned int width , const unsigned int height )
{
	D3DVIEWPORT9	viewport;
	unsigned int	safe_width = 1;
	unsigned int	safe_height = 1;



	viewport.X = 0;
	viewport.Y = 0;
	viewport.Width = safe_width;
	viewport.Height = safe_height;
	this->directx_device()->SetViewport(&viewport);
	this->set_size(width,height);
	this->_manager->resize(width,height,this->directx_device());
};

void	DirectXWindow::OnIdle()
{
	WindowObject::OnIdle();
};

void	DirectXWindow::Create( const wstring& name )
{
	WindowObject::Create(name,false);
};