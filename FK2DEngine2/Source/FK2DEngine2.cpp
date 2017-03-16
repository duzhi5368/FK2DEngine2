/**
*	created:		2013-4-11   20:39
*	filename: 		FK2DEngine2
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2.h"
#include <stdio.h>
#include <stdarg.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	FK_EXPORT Controls::Base* HoveredControl = NULL;
	FK_EXPORT Controls::Base* KeyboardFocus = NULL;
	FK_EXPORT Controls::Base* MouseFocus = NULL;

	namespace Debug
	{
		void Msg( const char* str, ... )
		{
			char strOut[1024];
			va_list s;
			va_start( s, str );
			vsnprintf( strOut, sizeof( strOut ), str, s );
			va_end( s );
			FKUtil_OutputDebugCharString( strOut );
		}
#ifdef UNICODE
		void Msg( const wchar_t* str, ... )
		{
			wchar_t strOut[1024];
			va_list s;
			va_start( s, str );
			vswprintf( strOut, sizeof( strOut ), str, s );
			va_end( s );
			FKUtil_OutputDebugWideString( strOut );
		}
#endif
		void AssertCheck( bool b, const char* strMsg )
		{
			if ( b ) { return; }

			Msg( "Assert: %s\n", strMsg );
#ifdef _WIN32
			MessageBoxA( NULL, strMsg, "Assert", MB_ICONEXCLAMATION | MB_OK );
			_asm { int 3 }
#endif
		}
	}

}
//------------------------------------------------------------------------