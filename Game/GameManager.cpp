#include	"GameManager.h"
#include	<fstream>
#include	<sstream>



void	GameManager::_load_high_scores()
{
	ifstream	high_scores("highscores.scores",ifstream::in);



	if ( high_scores.is_open() )
	{
		high_scores.seekg(0,ifstream::end);
		streamoff		size = high_scores.tellg();
		high_scores.seekg(0,ifstream::beg);

		char*			temp = new (nothrow)	char[static_cast<unsigned int>(size)];
		high_scores.read(temp,size);
		stringstream	buffer(temp);
		delete[] temp;


		unsigned int i = 0;
		while( !buffer.eof()  &&  i < _max_high_scores )
		{
			buffer >> this->_highscore_names[i] >> this->_highscore_scores[i];

			if ( this->_highscore_names[i].length() > this->_max_high_score_name_length )
				this->_highscore_names[i] = this->_highscore_names[i].substr(0,this->_max_high_score_name_length);

			++i;
		}

		
		high_scores.close();
	};
};

void	GameManager::_write_high_scores()
{
	ofstream	high_scores("highscores.scores",ofstream::out|ofstream::trunc);



	if ( high_scores.is_open() )
	{

		for ( unsigned int i = 0;  i < _max_high_scores;  ++i )
		{
			if ( this->_highscore_names[i] != "" )
				high_scores	<< this->_highscore_names[i] << " " << this->_highscore_scores[i] << endl;
			else
				high_scores	<< "EMPTY" << " " << this->_highscore_scores[i] << endl;
		}


		high_scores.close();
	}
};


void	GameManager::_build_fonts( HDC hdc )								// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID



	this->_font_ids[0] = glGenLists(256);				// Storage For 256 Characters
	this->_font_ids[1] = glGenLists(256);				// Storage For 256 Characters
	this->_font_ids[2] = glGenLists(256);				// Storage For 256 Characters
	this->_font_ids[3] = glGenLists(256);				// Storage For 256 Characters


	font = CreateFont(	-12,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						L"Arial");						// Font Name

	SelectObject(hdc, font);							// Selects The Font We Created

	wglUseFontOutlines(	hdc,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						this->_font_ids[0],							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						this->_font_content[0]);		// Address Of Buffer To Recieve Data


	font = CreateFont(	-14,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						L"Arial");						// Font Name

	SelectObject(hdc, font);							// Selects The Font We Created

	wglUseFontOutlines(	hdc,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						this->_font_ids[1],							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						this->_font_content[1]);		// Address Of Buffer To Recieve Data

	font = CreateFont(	-16,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						L"Arial");						// Font Name

	SelectObject(hdc, font);							// Selects The Font We Created

	wglUseFontOutlines(	hdc,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						this->_font_ids[2],							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						this->_font_content[2]);		// Address Of Buffer To Recieve Data

	font = CreateFont(	-18,							// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_BOLD,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						ANSI_CHARSET,					// Character Set Identifier
						OUT_TT_PRECIS,					// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						L"Arial");						// Font Name

	SelectObject(hdc, font);							// Selects The Font We Created

	wglUseFontOutlines(	hdc,							// Select The Current DC
						0,								// Starting Character
						255,							// Number Of Display Lists To Build
						this->_font_ids[3],							// Starting Display Lists
						0.0f,							// Deviation From The True Outlines
						0.2f,							// Font Thickness In The Z Direction
						WGL_FONT_POLYGONS,				// Use Polygons, Not Lines
						this->_font_content[3]);		// Address Of Buffer To Recieve Data
}

void GameManager::_print_font( const unsigned int i , const char *fmt, ... )	// Custom GL "Print" Routine
{
	if ( i < 4   &&  fmt != NULL )
	{
		float		length=0;								// Used To Find The Length Of The Text
		char		text[256];								// Holds Our String
		va_list		ap;										// Pointer To List Of Arguments



		va_start(ap, fmt);									// Parses The String For Variables
			vsprintf_s(text, fmt, ap);						// And Converts Symbols To Actual Numbers
		va_end(ap);											// Results Are Stored In Text

		for (unsigned int loop = 0;  loop < (strlen(text));  ++loop )	// Loop To Find Text Length
			length += this->_font_content[i][text[loop]].gmfCellIncX;			// Increase Length By Each Characters Width


		glPushMatrix();
			glTranslatef(-length/2,0.0f,0.0f);					// Center Our Text On The Screen
			glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
			glListBase(this->_font_ids[i]);						// Sets The Base Character to 0
			glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
			glPopAttrib();										// Pops The Display List Bits
		glPushMatrix();
	}
};

void	GameManager::_create_texture_from_bmp( const unsigned int i , const GLuint id , const string& filename )
{
	if ( i < 26 )
	{
		this->_texture_images[i].Load(filename.c_str());
	
		if ( !this->_texture_images[i].IsEmpty() )
		{
			glBindTexture(GL_TEXTURE_2D,id);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_R,GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
			this->_texture_images[i].gluBuild2DMipmaps();
			glBindTexture(GL_TEXTURE_2D,0);
		}
	}
};

void	GameManager::_create_gl_textures()
{
	glGenTextures(27,this->_texture_ids);

	if ( this->_texture_ids[0] > 0 )
	{
		this->_create_texture_from_bmp(0,this->_texture_ids[0],"A.bmp");
		this->_create_texture_from_bmp(1,this->_texture_ids[1],"B.bmp");
		this->_create_texture_from_bmp(2,this->_texture_ids[2],"C.bmp");
		this->_create_texture_from_bmp(3,this->_texture_ids[3],"D.bmp");
		this->_create_texture_from_bmp(4,this->_texture_ids[4],"E.bmp");
		this->_create_texture_from_bmp(5,this->_texture_ids[5],"F.bmp");
		this->_create_texture_from_bmp(6,this->_texture_ids[6],"G.bmp");
		this->_create_texture_from_bmp(7,this->_texture_ids[7],"H.bmp");
		this->_create_texture_from_bmp(8,this->_texture_ids[8],"I.bmp");
		this->_create_texture_from_bmp(9,this->_texture_ids[9],"J.bmp");
		this->_create_texture_from_bmp(10,this->_texture_ids[10],"K.bmp");
		this->_create_texture_from_bmp(11,this->_texture_ids[11],"L.bmp");
		this->_create_texture_from_bmp(12,this->_texture_ids[12],"M.bmp");
		this->_create_texture_from_bmp(13,this->_texture_ids[13],"N.bmp");
		this->_create_texture_from_bmp(14,this->_texture_ids[14],"O.bmp");
		this->_create_texture_from_bmp(15,this->_texture_ids[15],"P.bmp");
		this->_create_texture_from_bmp(16,this->_texture_ids[16],"Q.bmp");
		this->_create_texture_from_bmp(17,this->_texture_ids[17],"R.bmp");
		this->_create_texture_from_bmp(18,this->_texture_ids[18],"S.bmp");
		this->_create_texture_from_bmp(19,this->_texture_ids[19],"T.bmp");
		this->_create_texture_from_bmp(20,this->_texture_ids[20],"U.bmp");
		this->_create_texture_from_bmp(21,this->_texture_ids[21],"V.bmp");
		this->_create_texture_from_bmp(22,this->_texture_ids[22],"W.bmp");
		this->_create_texture_from_bmp(23,this->_texture_ids[23],"X.bmp");
		this->_create_texture_from_bmp(24,this->_texture_ids[24],"Y.bmp");
		this->_create_texture_from_bmp(25,this->_texture_ids[25],"Z.bmp");
		this->_create_texture_from_bmp(26,this->_texture_ids[26],"SPACE.bmp");
	}
	else
		throw( ErrorException(12,L"Cannot load the letter textures, the application will terminate!",__WFILE__,__LINE__));
};

void	GameManager::_set_gl_perspective( const unsigned int width , const unsigned int height ) const
{
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,static_cast<GLfloat>(width)/static_cast<GLfloat>(height),0.1f,100.0f);
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
};

void	GameManager::_set_gl_ortho() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0,10.0,-10.0,10.0,0.1,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};


void	GameManager::_set_gl_viewport( const unsigned int start_x , const unsigned int start_y , const unsigned int width , const unsigned int height ) const
{
	unsigned int	safe_width = 1;
	unsigned int	safe_height = 1;



	if ( width > 0 )
		safe_width = width;

	if ( height > 0 )
		safe_height = height;

	glViewport(start_x,start_y,safe_width,safe_height);
	this->_set_gl_perspective(safe_width,safe_height);
};

void	GameManager::_set_directx_viewport( const unsigned int width , const unsigned int height ,  LPDIRECT3DDEVICE9 device )
{
	D3DXVECTOR3			eye(0.0f,0.0f,1.0f);
	D3DXVECTOR3			direction(0.0f,0.0f,-1.0f);
	D3DXVECTOR3			up(0.0f,1.0f,0.0f);
	unsigned int		safe_width = 1;
	unsigned int		safe_height = 1;



	if ( width > 0 )
		safe_width = width;

	if ( height > 0 )
		safe_height = height;


	// For the projection matrix, we set up a perspective transform 
	// (which transforms geometry from 3D view space to 2D viewport 
	// space, with a perspective divide making objects smaller in the 
	// distance). To build a perspective transform, we need the width of the world window,
	// the width of the world window divided by the aspect ratio of the world window, 
	// and the near and far clipping planes (which define at what 
	// distances geometry should be no longer be rendered).
	//D3DXMatrixPerspectiveLH(&g_matProj, 2.0f, 2.0f/1.5f, 1.0f, 10000.0f);
	D3DXMatrixPerspectiveFovLH(&this->_dx_matProj,45.0f,static_cast<float>(safe_width)/static_cast<float>(safe_height),0.1f,100.0f);
	device->SetTransform( D3DTS_PROJECTION, &this->_dx_matProj );

	// Set up our view matrix. A view matrix can be defined given an 
	// eye point, a point to look at, and a direction for which way
	// is up. Here, we set the eye five units back along the z-axis
	// , look at the origin, and define "up" to be
	// in the y-direction.
	D3DXMatrixLookAtLH( &this->_dx_matView,&eye,&direction,&up);
	device->SetTransform( D3DTS_VIEW, &this->_dx_matView );
};

void	GameManager::_init_gl( HDC hdc )
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glEnable(GL_TEXTURE_2D);

	this->_build_fonts(hdc);
	this->_create_gl_textures();
};

void	GameManager::_init_directx( LPDIRECT3DDEVICE9 device )
{
	this->_dx_vertices[0].x = -1.0f;	this->_dx_vertices[0].y = -1.0f;		this->_dx_vertices[0].z = -2.0f;	this->_dx_vertices[0].color = 0xffff0000;
	this->_dx_vertices[1].x = 1.0f;		this->_dx_vertices[1].y = -1.0f;		this->_dx_vertices[1].z = -2.0f;	this->_dx_vertices[1].color = 0xffff0000;
	this->_dx_vertices[2].x = 1.0f;		this->_dx_vertices[2].y = 1.0f;		this->_dx_vertices[2].z = -2.0f;	this->_dx_vertices[2].color = 0xffff0000;
	
	this->_dx_vertices[3] = this->_dx_vertices[0];
	this->_dx_vertices[4] = this->_dx_vertices[2];
	this->_dx_vertices[5].x = -1.0f;		this->_dx_vertices[5].y = 1.0f;	this->_dx_vertices[5].z = -2.0f;	this->_dx_vertices[5].color = 0xffff0000;

	//*************************** Create Vertex Buffer ****************************
	if( FAILED( device->CreateVertexBuffer( 6*sizeof(CUSTOMVERTEX),
											0 /* Usage */ , D3DFVF_CUSTOMVERTEX,
											D3DPOOL_MANAGED, &this->_dx_vbo, NULL ) ) )
		throw(ErrorException(0,L"Vertex Buffer problem",__WFILE__,__LINE__));

	VOID* pVertices;
	if( FAILED( this->_dx_vbo->Lock( 0, sizeof(this->_dx_vertices), (void**)&pVertices, 0 ) ) )
		throw(ErrorException(0,L"Vertex Lock Problem",__WFILE__,__LINE__));

	memcpy( pVertices, this->_dx_vertices, sizeof(this->_dx_vertices) );

	this->_dx_vbo->Unlock();

	// Turn off D3D lighting, since we are
	// providing our own vertex colours
	device->SetRenderState( D3DRS_LIGHTING, FALSE );
	// Turn off culling, so we see the front and back of the triangle
	device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
};

void	GameManager::_destroy_directx( LPDIRECT3DDEVICE9 )
{
	this->_dx_vbo->Release();
};

void	GameManager::_destroy_gl()
{
	if ( this->_texture_ids[0] > 0 )
		glDeleteTextures(27,this->_texture_ids);

	for ( unsigned int i = 0;  i < 26;  ++i )
		this->_texture_images[i].Free();

	for ( unsigned int i = 0;  i < 4; ++i )
		glDeleteLists(this->_font_ids[i], 256);
};

void	GameManager::_render_gl( const unsigned width , const unsigned height )
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	this->_set_gl_viewport(0,0,width,height);


	if ( this->_in_menu )
		this->_draw_menu();
	else if ( this->_in_highscores )
		this->_draw_high_scores();
	else if ( this->_active_game )
	{
		this->_draw_play_screen(1,width,height);

		if ( this->_kinect_multi_player )
			this->_draw_play_screen(2,width,height);
	}
	else if ( this->_in_scorescreen )
		this->_draw_scorescreen(width,height);
	else if ( this->_update_highscores )
		this->_draw_update_high_scores();
};

void	GameManager::_render_directx( LPDIRECT3DDEVICE9 device )
{
	device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( device->BeginScene() ) )
	{
		// Rendering of scene objects can happen here
		device->SetStreamSource( 0, this->_dx_vbo, 0, sizeof(CUSTOMVERTEX) );
		device->SetFVF( D3DFVF_CUSTOMVERTEX );
		device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

		// End the scene
		device->EndScene();
	}

	device->Present( NULL, NULL, NULL, NULL );
};

void	GameManager::_kinect_func( const Skeleton* input )
{
	if ( input != NULL )
	{
		unsigned int	slot = 0;



		this->_skeletons[0]._used = false;
		this->_skeletons[1]._used = false;

		// get the first two tarcked skeletons, and use them as players
		for ( unsigned int i = 0;  i < NUI_SKELETON_COUNT;  ++i )
		{
			if ( input[i]._used == true )
			{ 
				for ( unsigned int j = 0;  j < NUI_SKELETON_POSITION_COUNT;  ++j )
				{
					if (	abs(this->_skeletons[slot]._points[j]._x-input[i]._points[j]._x) > Vector3f::_V3EPSILON  ||  
							abs(this->_skeletons[slot]._points[j]._y-input[i]._points[j]._y) > Vector3f::_V3EPSILON )
					{
						this->_skeletons[slot]._points[j]._x = input[i]._points[j]._x;
						this->_skeletons[slot]._points[j]._y = input[i]._points[j]._y;
					}
				}

				this->_skeletons[slot]._skeleton_no = input[i]._skeleton_no;
				this->_skeletons[slot]._used = input[i]._used;

				++slot;
			}


			if ( slot > 2 )
				break;
		}


		this->_trigger_events();
	}
};


// parse kinect input and translate it to letter messages corresponding to semaphores
void	GameManager::_trigger_events()
{
	Message	parameters(2,0);



	for ( unsigned int i = 0;  i < 2;  ++i )
	{
		parameters.data(0,static_cast<double>(i+1));
		parameters.data(1,0.0f);

		if ( this->_skeletons[i]._used )
		{
			Vector3f	left_arm(this->_skeletons[i]._points[NUI_SKELETON_POSITION_ELBOW_LEFT]._x - this->_skeletons[i]._points[NUI_SKELETON_POSITION_SHOULDER_LEFT]._x,this->_skeletons[i]._points[NUI_SKELETON_POSITION_ELBOW_LEFT]._y - this->_skeletons[i]._points[NUI_SKELETON_POSITION_SHOULDER_LEFT]._y,0.0f);
			Vector3f	right_arm(this->_skeletons[i]._points[NUI_SKELETON_POSITION_ELBOW_RIGHT]._x - this->_skeletons[i]._points[NUI_SKELETON_POSITION_SHOULDER_RIGHT]._x,this->_skeletons[i]._points[NUI_SKELETON_POSITION_ELBOW_RIGHT]._y - this->_skeletons[i]._points[NUI_SKELETON_POSITION_SHOULDER_RIGHT]._y,0.0f);
			Vector3f	down(this->_skeletons[i]._points[NUI_SKELETON_POSITION_SPINE]._x - this->_skeletons[i]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._x,this->_skeletons[i]._points[NUI_SKELETON_POSITION_SPINE]._y - this->_skeletons[i]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._y,0.0f);



			left_arm.normalize();
			right_arm.normalize();
			down.normalize();
		
			float		left_position = 1.0f - left_arm*down;
			float		right_position = 1.0f - right_arm*down;



			if ( left_position < 0.1f )
			{
				if ( left_arm.x() >= 0.0f )
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else
					{
					}
				}
				else
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							//TriggerEvent(GAME_ENGINE_KEY_DOWN_SPACE,parameters);
						}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_G )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_G,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_G;
							}
						}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_F )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_F,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_F;
							}
						}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_E )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_E,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_E;
							}
						}
						else	{}
					}
					else
					{
					}
				}
			}
			else if ( left_position < 0.5f )
			{
				if ( left_arm.x() >= 0.0f )
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_Z )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_Z,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_Z;
							}
						}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else
					{
					}
				}
				else
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_A )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_A,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_A;
							}
						}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_N )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_N,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_N;
							}
						}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_M )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_M,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_M;
							}
						}
						else
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_H )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_H,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_H;
							}
						}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_L )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_L,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_L;
							}
						}
						else
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_I )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_I,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_I;
							}
						}
					}
					else
					{
						if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_K )
						{
							TriggerEvent(GAME_ENGINE_KEY_DOWN_K,parameters);
							TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
							this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_K;
						}
					}
				}
			}
			else if ( left_position < 1.1f )
			{
				if ( left_arm.x() >= 0.0f )
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else
					{
					}
				}
				else
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_B )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_B,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_B;
							}
						}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_S )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_S,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_S;
							}
						}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_R )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_R,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_R;
							}
						}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_Q )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_Q,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_Q;
							}
						}
						else
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_O )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_O,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_O;
							}
						}
					}
					else
					{
						if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_P )
						{
							TriggerEvent(GAME_ENGINE_KEY_DOWN_P,parameters);
							TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
							this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_P;
						}
					}
				}
			}
			else if ( left_position < 1.55 )
			{
				if ( left_arm.x() >= 0.0f )
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_X )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_X,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_X;
							}
						}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_W )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_W,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_W;
							}
						}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else
					{
					}
				}
				else
				{
					if ( right_position < 0.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_C )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_C,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_C;
							}
						}
						else	{}
					}
					else if ( right_position < 0.55f )
					{
						if ( right_arm.x() >= 0.0f )	{}
						else	{}
					}
					else if ( right_position < 1.1f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_Y )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_Y,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_Y;
							}
						}
						else	{}
					}
					else if ( right_position < 1.55f )
					{
						if ( right_arm.x() >= 0.0f )
						{
							if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_U )
							{
								TriggerEvent(GAME_ENGINE_KEY_DOWN_U,parameters);
								TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
								this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_U;
							}
						}
						else	{}
					}
					else
					{
						if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_T )
						{
							TriggerEvent(GAME_ENGINE_KEY_DOWN_T,parameters);
							TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
							this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_T;
						}
					}
				}
			}
			else
			{
				if ( right_position < 0.1f )
				{
					if ( right_arm.x() >= 0.0f )
					{
						if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_D )
						{
							TriggerEvent(GAME_ENGINE_KEY_DOWN_D,parameters);
							TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
							this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_D;
						}
					}
					else	{}
				}
				else if ( right_position < 0.55f )
				{
					if ( right_arm.x() >= 0.0f )
					{
						if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_V )
						{
							TriggerEvent(GAME_ENGINE_KEY_DOWN_V,parameters);
							TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
							this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_V;
						}
					}
					else	{}
				}
				else if ( right_position < 1.1f )
				{
					if ( right_arm.x() >= 0.0f )
					{
						if ( this->_skeleton_last_message[i] != GAME_ENGINE_KEY_DOWN_J )
						{
							TriggerEvent(GAME_ENGINE_KEY_DOWN_J,parameters);
							TriggerEvent(GAME_ENGINE_KEY_UP_A-GAME_ENGINE_KEY_DOWN_A+this->_skeleton_last_message[i],parameters);
							this->_skeleton_last_message[i] = GAME_ENGINE_KEY_DOWN_J;
						}
					}
					else	{}
				}
				else if ( right_position < 1.55f )
				{
					if ( right_arm.x() >= 0.0f )	{}
					else	{}
				}
				else
				{
				}
			}
		}
	}
};

void	GameManager::_update_player_time( double time )
{
	this->_player1_time += time;

	if ( this->_kinect_single_player  ||  this->_kinect_multi_player )
	{
		if ( this->_player1_time > this->_maximum_kinect_response_time )
		{
			this->_choose_letter(1);
			this->_player1_time = 0.0;
		}
	}
	else
	{
		if ( this->_player1_time > this->_maximum_response_time )
		{
			this->_choose_letter(0);
			this->_player1_time = 0.0;
		}
	}


	if ( this->_kinect_multi_player )
	{
		this->_player2_time += time;

		if ( this->_player2_time > this->_maximum_kinect_response_time )
		{
			this->_choose_letter(2);
			this->_player2_time = 0.0;
		}
	}
};

void	GameManager::_update_score( const unsigned int player )
{
	float	_award = 0;



	if ( player <= 1 )
	{
		if ( player == 0 )
			_award = static_cast<float>(max(this->_maximum_response_time - this->_player1_time,0.0))/static_cast<float>(this->_maximum_response_time);
		else
			_award = static_cast<float>(max(this->_maximum_kinect_response_time - this->_player1_time,0.0))/static_cast<float>(this->_maximum_kinect_response_time);

		this->_player1_score += static_cast<unsigned int>(_award*this->_max_points_per_answer);
	}
	else if ( player == 2 )
	{
		_award = static_cast<float>(max(this->_maximum_kinect_response_time - this->_player2_time,0.0))/static_cast<float>(this->_maximum_kinect_response_time);
		this->_player2_score += static_cast<unsigned int>(_award*this->_max_points_per_answer);
	}
};

void	GameManager::_choose_letter( const unsigned int player )
{
	srand(static_cast<unsigned int>(time(NULL)+player));
	
	if ( player <= 1 )
		this->_player1_letter = rand()%26;
	else if ( player == 2 )
		this->_player2_letter = rand()%26;
};

bool	GameManager::_check_key( const unsigned int player , const unsigned int key )
{
	if ( player <= 1 )
	{
		if ( this->_player1_letter == key )
			return true;
		else
			return false;
	}
	else if ( player == 2 )
	{
		if ( this->_player2_letter == key )
			return true;
		else
			return false;
	}
	else
		return false;
};

void	GameManager::_check_highscore()
{
	bool	found = false;
	
	
	
	if ( !this->_kinect_multi_player )
	{
		for ( unsigned int i = 0;  i < this->_max_high_scores;  ++i )
		{
			if ( this->_highscore_scores[i] < this->_player1_score )
			{
				found = true;
				this->_new_highscore_place = i;
				this->_new_highscore_player = 0;
				this->_new_highscore_name = "";
				break;
			}
		}

		if ( !found )
		{
			this->_new_highscore_place = this->_max_high_scores;
			this->_new_highscore_player = 0;
		}

		this->_new_highscore_score = this->_player1_score;
	}
	else
	{
		unsigned int	winner = 1;
		unsigned int	score = this->_player1_score;



		if ( this->_player1_score < this->_player2_score )
		{
			winner = 2;
			score = this->_player2_score;
		}

		for ( unsigned int i = 0;  i < this->_max_high_scores;  ++i )
		{
			if ( this->_highscore_scores[i] < score )
			{
				found = true;
				this->_new_highscore_place = i;
				this->_new_highscore_player = winner;
				this->_new_highscore_name = "";
				break;
			}
		}

		if ( !found )
		{
			this->_new_highscore_place = this->_max_high_scores;
			this->_new_highscore_player = winner;
		}

		this->_new_highscore_score = score;
	}
};


void	GameManager::_draw_skeleton( const unsigned int skeleton )
{
	if ( skeleton < 2  &&  this->_skeletons[skeleton]._used )
	{
		glPushMatrix();
			// Draw joints as blobs
			glPointSize(3);
			glBegin(GL_LINES);
				glColor3f(1.0f,0.0f,0.0f);

				//	Head to shoulder center
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HEAD]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HEAD]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._y),
								-2.5f);

				// Shoulder center to spine
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SPINE]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SPINE]._y),
								-2.5f);

				// Spine to hip center
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SPINE]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SPINE]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HIP_CENTER]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HIP_CENTER]._y),
								-2.5f);

				// Shoulder center to right shoulder
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_RIGHT]._y),
								-2.5f);

				//	Right Shoulder to right elbow
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_RIGHT]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_RIGHT]._y),
								-2.5f);

				//	Right elbow to right wrist
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_RIGHT]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_RIGHT]._y),
								-2.5f);

				// Right wrist to right hand
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_RIGHT]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HAND_RIGHT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HAND_RIGHT]._y),
								-2.5f);

				// Shoulder center to left shoulder
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_CENTER]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_LEFT]._y),
								-2.5f);

				//	Left Shoulder to Left elbow
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_SHOULDER_LEFT]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_LEFT]._y),
								-2.5f);

				//	Left elbow to Left wrist
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_ELBOW_LEFT]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_LEFT]._y),
								-2.5f);

				// Left wrist to Left hand
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_WRIST_LEFT]._y),
								-2.5f);
				glVertex3f(static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HAND_LEFT]._x),
								static_cast<GLfloat>(this->_skeletons[skeleton]._points[NUI_SKELETON_POSITION_HAND_LEFT]._y),
								-2.5f);

			glEnd();
		glPopMatrix();
	}
};

void	GameManager::_draw_menu()
{
	this->_set_gl_ortho();


	glPushMatrix();
		glColor3f(0.68f,0.12f,0.02f);
		glTranslatef(0.0f,6.0f,0.1f);
		this->_print_font(3,"Semaphore....Whatever");
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,0.0f,0.1f);
		this->_print_font(2,"1. Keyboard Singleplayer");
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,-2.0f,0.1f);
		this->_print_font(2,"2. Kinect Singleplayer");
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,-4.0f,0.1f);
		this->_print_font(2,"3. Kinect Multiplayer");
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,-6.0f,0.1f);
		this->_print_font(2,"4. Highscores");
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,-8.0f,0.1f);
		this->_print_font(2,"5. Exit");
	glPopMatrix();
};

void	GameManager::_draw_high_scores()
{
	unsigned int	max_length = 0;



	this->_set_gl_ortho();


	glPushMatrix();
		glColor3f(0.68f,0.12f,0.02f);
		glTranslatef(0.0f,6.0f,0.0f);
		this->_print_font(3,"Highscores");
	glPopMatrix();

	
	for ( unsigned int i = 0;  i < _max_high_scores; ++i )
	{
		if ( this->_highscore_names[i].length() > max_length )
			max_length = this->_highscore_names[i].length();
	}

	for ( unsigned int i = 0;  i < _max_high_scores;  ++i )
	{
		string padding("");
		


		for ( unsigned int j = 0;  j < (max_length - this->_highscore_names[i].length()+1);  ++j )
			padding += " ";

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,i*-2.0f,0.1f);
			this->_print_font(2,"%u  %s%s%d",(i+1),this->_highscore_names[i].c_str(),padding.c_str(),this->_highscore_scores[i]);
		glPopMatrix();
	}
};


void	GameManager::_draw_update_high_scores()
{
	unsigned int	max_length = 0;
	string			padding("");
	string			name("PLAYER1");



	if ( this->_new_highscore_place < this->_max_high_scores )
		name = this->_new_highscore_name;
	else if ( this->_new_highscore_player == 2 )
		name = "PLAYER2";


	this->_set_gl_ortho();


	glPushMatrix();
		glColor3f(0.68f,0.12f,0.02f);
		glTranslatef(0.0f,6.0f,0.0f);
		this->_print_font(3,"Highscores");
	glPopMatrix();

	
	for ( unsigned int i = 0;  i < _max_high_scores; ++i )
	{
		if ( this->_highscore_names[i].length() > max_length )
			max_length = this->_highscore_names[i].length();
	}

	if ( max_length < name.length() )
		max_length = name.length();


	for ( unsigned int i = 0;  i < this->_new_highscore_place;  ++i )
	{
		padding = "";
		for ( unsigned int j = 0;  j < (max_length - this->_highscore_names[i].length()+1);  ++j )
			padding += " ";

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,2.0f - i*2.0f,0.1f);
			this->_print_font(2,"%u  %s%s%d",(i+1),this->_highscore_names[i].c_str(),padding.c_str(),this->_highscore_scores[i]);
		glPopMatrix();
	}


	padding = "";
	for ( unsigned int j = 0;  j < (max_length - name.length()+1);  ++j )
			padding += " ";

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,2.0f - this->_new_highscore_place*2.0f,0.1f);
		this->_print_font(2,"%u  %s%s%d",(this->_new_highscore_place+1),name.c_str(),padding.c_str(),this->_new_highscore_score);
	glPopMatrix();

	for ( unsigned int i = this->_new_highscore_place;  i < this->_max_high_scores;  ++i )
	{
		padding = "";
		for ( unsigned int j = 0;  j < (max_length - this->_highscore_names[i].length()+1);  ++j )
			padding += " ";

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,2.0f - (i+1)*2.0f,0.1f);
			this->_print_font(2,"%u  %s%s%d",(i+2),this->_highscore_names[i].c_str(),padding.c_str(),this->_highscore_scores[i]);
		glPopMatrix();
	}
};

void	GameManager::_draw_play_screen( const unsigned int player , const unsigned int width , const unsigned int height )
{
	unsigned int	letter = 1;
	unsigned int	skeleton = 0;
	unsigned int	score = 0;
	double			time = 0.0;
	unsigned int	start_x = 0;
	unsigned int	start_y = 0;
	unsigned int	end_x = width;
	unsigned int	end_y = height;
	


	if ( player == 1 )
	{
		letter = this->_texture_ids[this->_player1_letter];
		skeleton = 0;
		score = this->_player1_score;
		time = this->_player1_time;

		if ( this->_kinect_multi_player )
			end_x = static_cast<unsigned int>(max(static_cast<float>(width*0.495f),0.495f));
	}
	else if ( player == 2 )
	{
		letter = this->_texture_ids[this->_player2_letter];
		skeleton = 1;
		score = this->_player2_score;
		time = this->_player2_time;
		start_x = static_cast<unsigned int>(max(static_cast<float>(width*0.5f),0.5f));
		end_x = static_cast<unsigned int>(max(static_cast<float>(width*0.495f),0.495f));
	}


	this->_set_gl_viewport(start_x,start_y,end_x,end_y);

	glPushMatrix();
		glBindTexture(GL_TEXTURE_2D,letter);
		glBegin(GL_QUADS);
			glColor3f(0.6f,0.6f,0.15f);

			glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -0.5f,  -7.5f);  // Bottom Left Of The Texture and Quad
			glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -0.5f,  -7.5f);  // Bottom Right Of The Texture and Quad
			glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.5f,  -7.5f);  // Top Right Of The Texture and Quad
			glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.5f,  -7.5f);  // Top Left Of The Texture and Quad
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
	glPopMatrix();

	this->_draw_skeleton(skeleton);

	this->_set_gl_ortho();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,7.5f,0.1f);
		this->_print_font(1,"Time Left:  %3.2f",this->_time_left);
	glPopMatrix();

	glPushMatrix();
		glColor3f(0.02f,0.35f,0.65f);
		glTranslatef(0.0f,-9.5f,0.1f);
		this->_print_font(0,"Score: %4u               Timer:  %3.2f",score,time);
	glPopMatrix();
};

void	GameManager::_draw_scorescreen( const unsigned int width , const unsigned int height )
{
	this->_set_gl_ortho();

	if ( !this->_kinect_multi_player )
	{
		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,7.5f,0.1f);
			this->_print_font(0,"You Win! ... sort of...");
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,-2.5f,0.1f);
			this->_print_font(2,"Your score was: %d",this->_player1_score);
		glPopMatrix();

		if ( this->_new_highscore_place < this->_max_high_scores )
		{
			glPushMatrix();
				glColor3f(0.02f,0.85f,0.25f);
				glTranslatef(0.0f,-7.5f,0.1f);
				this->_print_font(0,"It's a new highscore! Your ranking is: %u",this->_new_highscore_place+1 );
			glPopMatrix();
		}
	}
	else
	{
		string	win  = "You Win! ...sort of...";
		string	loss = "You Lose! ...play with both hands next time...";



		this->_set_gl_viewport(0,0,static_cast<unsigned int>(max(static_cast<float>(width*0.495f),0.495f)),height);
		this->_set_gl_ortho();

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,7.5f,0.1f);

			if ( this->_new_highscore_player == 1 )
				this->_print_font(0,win.c_str());
			else
				this->_print_font(0,loss.c_str());

		glPopMatrix();

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,-2.5f,0.1f);
			this->_print_font(2,"Your score was: %d",this->_player1_score);
		glPopMatrix();

		if ( this->_new_highscore_player == 1   &&  this->_new_highscore_place < this->_max_high_scores )
		{
			glPushMatrix();
				glColor3f(0.02f,0.85f,0.25f);
				glTranslatef(0.0f,-7.5f,0.1f);
				this->_print_font(0,"It's a new highscore! Your ranking is: %u",this->_new_highscore_place+1 );
			glPopMatrix();
		}



		this->_set_gl_viewport(static_cast<unsigned int>(max(static_cast<float>(width*0.5f),0.5f)),0,static_cast<unsigned int>(max(static_cast<float>(width*0.495f),0.495f)),height);
		this->_set_gl_ortho();

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,7.5f,0.1f);

			if ( this->_new_highscore_player == 2 )
				this->_print_font(0,win.c_str());
			else
				this->_print_font(0,loss.c_str());

		glPopMatrix();

		glPushMatrix();
			glColor3f(0.02f,0.35f,0.65f);
			glTranslatef(0.0f,-2.5f,0.1f);
			this->_print_font(2,"Your score was: %d",this->_player2_score);
		glPopMatrix();

		if ( this->_new_highscore_player == 2   &&  this->_new_highscore_place < this->_max_high_scores )
		{
			glPushMatrix();
				glColor3f(0.02f,0.85f,0.25f);
				glTranslatef(0.0f,-7.5f,0.1f);
				this->_print_font(0,"It's a new highscore! Your ranking is: %u",this->_new_highscore_place );
			glPopMatrix();
		}
	}
};


GameManager::GameManager()	:	
	_dx_vbo(NULL) , 
	_new_highscore_player(0) ,
	_new_highscore_name("") , 
	_new_highscore_score(0) , 
	_new_highscore_place(6) , 
	_current_time(WindowObject::GetTime()) , 
	_round_time(10.0f) , 
	_time_left(0.0f) ,
	_maximum_response_time(1.00f) , 
	_maximum_kinect_response_time(2.25f) , 
	_player1_time(0.0f) , 
	_player2_time(0.0f) , 
	_player1_score(0) , 
	_player2_score(0) , 
	_player1_letter(0) ,
	_player2_letter(0) , 
	_in_menu(true) ,
	_active_game(false) , 
	_game_paused(false) , 
	_in_highscores(false) , 
	_update_highscores(false) , 
	_single_player(true) , 
	_kinect_single_player(false) ,
	_kinect_multi_player(false)
{
	this->_skeleton_last_message[0] = 65000;
	this->_skeleton_last_message[1] = 65000;

	for ( unsigned int i = 0;  i < this->_max_high_scores;  ++i )
	{
		this->_highscore_names[i] = "EMPTY";
		this->_highscore_scores[i] = 0;
	}

	this->_font_ids[0] = 0;
	this->_font_ids[1] = 0;
	this->_font_ids[2] = 0;
	this->_font_ids[3] = 0;
};

GameManager::~GameManager()	{};


// on event functions handling any registerd messages, mostly keyboard and kinect triggered messages
void	GameManager::OnEvent( const unsigned int message , const Message& parameters )
{
	if ( message == GAME_ENGINE_KEY_UP_ESCAPE )
	{
		if ( this->_in_menu  &&  !this->_active_game )
		{
			wcout << L"Exiting game" << endl;
			TriggerEvent(GAME_ENGINE_CLOSE);
		}
		else if ( this->_in_menu  &&  this->_active_game )
		{
			if ( this->_kinect_single_player  ||  this->_kinect_multi_player )
				this->enable_kinect();

			this->_in_menu = false;
			this->_in_highscores = false;
			this->_in_scorescreen = false;
			this->_update_highscores = false;
			this->_game_paused = false;
			wcout << L"Resuming game" << endl;
		}
		else if ( this->_active_game )
		{
			this->_in_menu = true;
			this->_in_highscores = false;
			this->_in_scorescreen = false;
			this->_update_highscores = false;
			this->_game_paused = true;
			this->disable_kinect();
			wcout << L"Pausing game" << endl;
		}
		else if ( this->_in_highscores )
		{
			this->_in_highscores = false;
			this->_update_highscores = false;
			this->_in_scorescreen = false;
			this->_in_menu = true;
			wcout << L"Going to highscores." << endl;
		}
		else if ( this->_in_scorescreen )
		{
			this->_update_highscores = true;
			this->_in_scorescreen = false;
			this->_in_menu = false;
			this->_in_highscores = false;
		}
		else if ( this->_update_highscores )
		{
			this->_update_highscores = false;
			this->_in_scorescreen = false;
			this->_in_menu = true;
			this->_in_highscores = false;
		}
	}
	else if ( message == GAME_ENGINE_KEY_UP_ENTER )
	{
		if ( this->_update_highscores )
		{
			for ( int i = this->_max_high_scores-2;  i >= static_cast<int>(this->_new_highscore_place);  --i )
			{
				this->_highscore_scores[i+1] = this->_highscore_scores[i];
				this->_highscore_names[i+1] = this->_highscore_names[i];

				if ( static_cast<unsigned int>(i) == this->_new_highscore_place )
				{
					this->_highscore_scores[i] = this->_new_highscore_score;
					this->_highscore_names[i] = this->_new_highscore_name;
				}
			}
			
			this->_update_highscores = false;
			this->_in_scorescreen = false;
			this->_in_menu = true;
			this->_in_highscores = false;
		}
	}
	else if ( message == GAME_ENGINE_KEY_UP_BACKSPACE )
	{
		if ( this->_update_highscores  &&  this->_new_highscore_name.length() >= 1 )
		{
			if ( this->_new_highscore_place < this->_max_high_scores )
				this->_new_highscore_name = this->_new_highscore_name.substr(0,this->_new_highscore_name.length()-1);
		}
	}
	else if ( message == GAME_ENGINE_CLOSE_WINDOWS  ||  message == GAME_ENGINE_CLOSE )
		this->_write_high_scores();
	else if ( message == GAME_ENGINE_KINECT_SKELETON )
		this->_kinect_func(reinterpret_cast<Skeleton*>(parameters.pointer(0)));
	else if (	( message >= GAME_ENGINE_KEY_UP_1  &&  message <= GAME_ENGINE_KEY_UP_5 )  ||  
				( message >= GAME_ENGINE_KEY_UP_NUMPAD_1  &&  message <= GAME_ENGINE_KEY_UP_NUMPAD_5 ) )
	{
		if ( this->_in_menu )
		{
			if ( message == GAME_ENGINE_KEY_UP_1  ||  message == GAME_ENGINE_KEY_UP_NUMPAD_1 )
			{
				this->_in_menu = false;
				this->_update_highscores = false;
				this->_in_scorescreen = false;
				this->_in_highscores = false;
				this->_active_game = true;
				this->_game_paused = false;
				this->_single_player = true;
				this->_kinect_single_player = false;
				this->_kinect_multi_player = false;
				this->_player1_score = 0;
				this->_player1_time = 0;
				this->_choose_letter(1);
				this->_time_left = this->_round_time;
				wcout << L"Starting single player game." << endl;
			}
			else if ( message == GAME_ENGINE_KEY_UP_2  ||  message == GAME_ENGINE_KEY_UP_NUMPAD_2 )
			{
				this->_in_menu = false;
				this->_update_highscores = false;
				this->_in_scorescreen = false;
				this->_in_highscores = false;
				this->_active_game = true;
				this->_game_paused = false;
				this->_single_player = false;
				this->_kinect_single_player = true;
				this->_kinect_multi_player = false;
				this->_player1_score = 0;
				this->_player1_time = 0;
				this->_choose_letter(1);
				this->_time_left = 2.25*this->_round_time;
				this->enable_kinect();
				wcout << L"Starting kinect single player game." << endl;
			}
			else if ( message == GAME_ENGINE_KEY_UP_3  ||  message == GAME_ENGINE_KEY_UP_NUMPAD_3 )
			{
				this->_in_menu = false;
				this->_update_highscores = false;
				this->_in_scorescreen = false;
				this->_in_highscores = false;
				this->_active_game = true;
				this->_game_paused = false;
				this->_single_player = false;
				this->_kinect_single_player = false;
				this->_kinect_multi_player = true;
				this->_player1_score = 0;
				this->_player1_time = 0;
				this->_choose_letter(1);
				this->_player2_score = 0;
				this->_player2_time = 0;
				this->_choose_letter(2);
				this->_time_left = 2.25*this->_round_time;
				this->enable_kinect();
				wcout << L"Starting kinect multiplayer player game." << endl;
			}
			else if ( message == GAME_ENGINE_KEY_UP_4  ||  message == GAME_ENGINE_KEY_UP_NUMPAD_4 )
			{
				this->_in_menu = false;
				this->_update_highscores = false;
				this->_in_scorescreen = false;
				this->_in_highscores = true;
				wcout << L"Going to highscores." << endl;
			}
			else if ( message == GAME_ENGINE_KEY_UP_5  ||  message == GAME_ENGINE_KEY_UP_NUMPAD_5 )
			{
				wcout << L"Exiting game" << endl;
				TriggerEvent(GAME_ENGINE_CLOSE);
			}
		}
	}
	else if ( message >= GAME_ENGINE_KEY_DOWN_A  &&  message <= GAME_ENGINE_KEY_DOWN_Z )
	{
		if ( this->_active_game  &&   !this->_game_paused )
		{
			unsigned int	key  = message - GAME_ENGINE_KEY_DOWN_A;;



			if ( this->_single_player )
			{
				if ( this->_check_key(static_cast<unsigned int>(parameters.data(0)),key) )
				{
					this->_update_score(static_cast<unsigned int>(parameters.data(0)));
					this->_choose_letter(static_cast<unsigned int>(parameters.data(0)));
					this->_player1_time = 0.0;
				}
			}
			else if ( this->_kinect_single_player  &&  parameters.data(0) > 0 )
			{
				if ( this->_check_key(static_cast<unsigned int>(parameters.data(0)),key) )
				{
					this->_update_score(static_cast<unsigned int>(parameters.data(0)));
					this->_choose_letter(static_cast<unsigned int>(parameters.data(0)));
					this->_player1_time = 0.0;
				}
			}
			else if ( this->_kinect_multi_player  &&  parameters.data(0) > 0 )
			{
				if ( this->_check_key(static_cast<unsigned int>(parameters.data(0)),key) )
				{
					this->_update_score(static_cast<unsigned int>(parameters.data(0)));
					this->_choose_letter(static_cast<unsigned int>(parameters.data(0)));

					if ( parameters.data(0) == 1 )
						this->_player1_time = 0.0;
					else
						this->_player2_time = 0.0;
				}
			}
		};
	}
	else if ( message >= GAME_ENGINE_KEY_UP_A  &&  message <= GAME_ENGINE_KEY_UP_Z )
	{
		if ( this->_update_highscores  &&  parameters.data(0) <= 1 )
		{
			if ( this->_new_highscore_place < this->_max_high_scores )
			{
				this->_new_highscore_name += static_cast<char>(message-GAME_ENGINE_KEY_UP_A) + 'A';
			}
		}
	}
	else
		wcout << message << endl;
}

// register any wanted events with the message manager
void	GameManager::init_once()
{
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_A);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_B);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_C);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_D);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_E);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_F);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_G);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_H);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_I);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_J);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_K);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_L);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_M);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_N);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_O);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_P);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_Q);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_R);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_S);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_T);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_U);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_V);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_W);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_X);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_Y);
	this->RegisterEvent(GAME_ENGINE_KEY_DOWN_Z);
	
	this->RegisterEvent(GAME_ENGINE_KEY_UP_A);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_B);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_C);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_D);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_E);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_F);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_G);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_H);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_I);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_J);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_K);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_L);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_M);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_N);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_O);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_P);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_Q);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_R);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_S);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_T);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_U);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_V);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_W);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_X);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_Y);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_Z);

	this->RegisterEvent(GAME_ENGINE_KEY_UP_1);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_2);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_3);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_4);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_5);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_NUMPAD_1);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_NUMPAD_2);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_NUMPAD_3);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_NUMPAD_4);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_NUMPAD_5);

	this->RegisterEvent(GAME_ENGINE_KEY_UP_ESCAPE);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_ENTER);
	this->RegisterEvent(GAME_ENGINE_KEY_UP_BACKSPACE);


	this->RegisterEvent(GAME_ENGINE_CLOSE);
	this->RegisterEvent(GAME_ENGINE_CLOSE_WINDOWS);

	this->_load_high_scores();
};

void	GameManager::init_content( HDC hdc )					{ this->_init_gl(hdc); };
void	GameManager::init_content( LPDIRECT3DDEVICE9 device )	{ this->_init_directx(device); };

void	GameManager::destroy_content( HDC )							{ this->_destroy_gl(); };
void	GameManager::destroy_content( LPDIRECT3DDEVICE9 device )	{ this->_destroy_directx(device); };

void	GameManager::init_kinect()
{
	TriggerEvent(GAME_ENGINE_INIT_KINECT);
};

void			GameManager::enable_kinect()
{
	this->RegisterEvent(GAME_ENGINE_KINECT_SKELETON);
};

void	GameManager::disable_kinect()
{
	this->UnregisterEvent(GAME_ENGINE_KINECT_SKELETON);
};

void	GameManager::resize( const unsigned int width , const unsigned int height )								{ this->_set_gl_viewport(0,0,width,height); };
void	GameManager::resize( const unsigned int width , const unsigned int height , LPDIRECT3DDEVICE9 device )	{ this->_set_directx_viewport(width,height,device); };
void	GameManager::render( const unsigned int width , const unsigned int height )								{ this->_render_gl(width,height); };
void	GameManager::render( LPDIRECT3DDEVICE9 device )															{ this->_render_directx(device); };

void	GameManager::update_time( double time )
{
	double	difference = time - this->_current_time;



	this->_current_time = time;
	if ( this->_active_game  &&  !this->_game_paused )
	{
		this->_time_left -= difference*0.001;
		this->_update_player_time(difference*0.001);

		if ( this->_time_left <= 0.0 )
		{
			this->_active_game = false;
			this->_in_menu = false;
			this->_update_highscores = false;
			this->_in_highscores = false;
			this->_in_scorescreen = true;
			this->_check_highscore();
			wcout << L"Game Ended. Entering scorescreen." << endl;
		}
	}
}