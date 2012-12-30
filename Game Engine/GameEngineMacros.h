#pragma	once

#ifndef	_GAME_ENGINE_MACROS_H_
	#define	_GAME_ENGINE_MACROS_H_

	
	#ifndef	__WFILE__
		//	taken from msdn it's a way to implement a __WFILE__ macro
		#define		WIDEN2(x)	L ## x
		#define		WIDEN(x)	WIDEN2(x)
		#define		__WFILE__	WIDEN(__FILE__)
	#endif	/* __WFILE__ */

	#ifndef	DLL_OUTPUT
		#ifdef	_WINDLL
			#define	DLL_OUTPUT	__declspec(dllexport)
		#else
			#define	DLL_OUTPUT	__declspec(dllimport)
		#endif	/* _WINDLL */
	#endif	/* DLL_OUPUT */


#endif	/* _GAME_ENGINE_MACROS_H_ */