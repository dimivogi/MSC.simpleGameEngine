#pragma	once

#include	<vector>
#include	<string>
#include	<cstdarg>
#include	"GameEngine.h"
#include	"G:\GXBase\inc\GXBase.h"

using		namespace std;
using		namespace GameEngine;



#ifndef		_GAME_MANAGER_H_
	#define	_GAME_MANAGER_H_


	#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE) 

	struct CUSTOMVERTEX
	{
		float x, y, z;	// The transformed position for the vertex
		DWORD color;    // The vertex color
	};


	// Class repsonsible for the game logic
	class	GameManager	:	public GenericObject
	{
		private:

			static const int		_max_high_scores = 5;
			static const int		_max_high_score_name_length = 5;
			static const int		_max_points_per_answer = 20;


			Skeleton				_skeletons[2];
			unsigned int			_skeleton_last_message[2];

			// Buffer to hold vertices
			LPDIRECT3DVERTEXBUFFER9	_dx_vbo; 
			CUSTOMVERTEX			_dx_vertices[6];
			D3DXMATRIX				_dx_matProj;  
			D3DXMATRIX				_dx_matView;
			D3DXMATRIX				_dx_matWorld;

			gxbase::Image			_texture_images[27];
			GLuint					_texture_ids[27];
			GLuint					_font_ids[4];
			GLYPHMETRICSFLOAT		_font_content[4][256];

			string					_highscore_names[_max_high_scores];
			unsigned int			_highscore_scores[_max_high_scores];

			unsigned int			_new_highscore_player;
			string					_new_highscore_name;
			unsigned int			_new_highscore_score;
			unsigned int			_new_highscore_place;
			double					_current_time;
			double					_round_time;
			double					_time_left;
			double					_maximum_response_time;
			double					_maximum_kinect_response_time;
			double					_player1_time;
			double					_player2_time;
			unsigned int			_player1_score;
			unsigned int			_player2_score;
			unsigned int			_player1_letter;
			unsigned int			_player2_letter;
			bool					_in_menu;
			bool					_active_game;
			bool					_game_paused;
			bool					_in_highscores;
			bool					_update_highscores;
			bool					_in_scorescreen;
			bool					_single_player;
			bool					_kinect_single_player;
			bool					_kinect_multi_player;
			
			
			void					_load_high_scores();
			void					_write_high_scores();
			void					_build_fonts( HDC hdc );
			void					_print_font( const unsigned int font , const char *fmt, ... );	
			void					_create_texture_from_bmp( const unsigned int i , const GLuint , const string& filename );
			void					_create_gl_textures();
			void					_set_gl_perspective( const unsigned int width , const unsigned int height ) const;
			void					_set_gl_ortho() const;
			void					_set_gl_viewport( const unsigned int start_x , const unsigned int start_y , const unsigned int width , const unsigned int height ) const;
			void					_set_directx_viewport( const unsigned int width , const unsigned int height , LPDIRECT3DDEVICE9 device );
			void					_init_gl( HDC hdc );
			void					_init_directx( LPDIRECT3DDEVICE9 device );
			void					_destroy_directx( LPDIRECT3DDEVICE9 device );
			void					_destroy_gl();
			void					_render_gl( const unsigned int width , const unsigned int height );
			void					_render_directx( LPDIRECT3DDEVICE9 device );

			void					_kinect_func( const Skeleton* input );
			void					_trigger_events();
			void					_update_player_time( double time );
			void					_update_score( const unsigned int player );
			void					_choose_letter( const unsigned int player );
			bool					_check_key( const unsigned int player , const unsigned int key );
			void					_check_highscore();

			void					_draw_skeleton( const unsigned int skeleton );
			void					_draw_menu();
			void					_draw_high_scores();
			void					_draw_update_high_scores();
			void					_draw_play_screen( const unsigned int player , const unsigned int width , const unsigned int height );
			void					_draw_scorescreen( const unsigned int width , const unsigned int height );


		public:

			GameManager();
			~GameManager();


			void					OnEvent( const unsigned int message , const Message& parameters );


			void					init_once();
			void					init_content( HDC hdc );
			void					init_content( LPDIRECT3DDEVICE9 device );
			void					destroy_content( HDC hdc );
			void					destroy_content( LPDIRECT3DDEVICE9 device );
			void					init_kinect();
			void					enable_kinect();
			void					disable_kinect();
			void					resize( const unsigned int width , const unsigned int height );
			void					resize( const unsigned int width , const unsigned int height , LPDIRECT3DDEVICE9 device );
			void					render( const unsigned int width , const unsigned int height );
			void					render( LPDIRECT3DDEVICE9 device = NULL );
			void					update_time( double time );

	};


#endif		/* _GAME_MANAGER_H_ */