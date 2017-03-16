/**
*	created:		2013-4-11   17:05
*	filename: 		FK2DEngine2
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <stdlib.h>
#include <memory.h>
#include <set>
#include <list>
#include <algorithm>
//------------------------------------------------------------------------
#include "Include/FKMacros.h"
#include "Include/FKConfig.h"
#include "Include/FKExports.h"
#include "Include/FKStructures.h"
#include "Include/FKSkin.h"
#include "Include/Controls/FKBase.h"
#include "Include/Controls/FKCanvas.h"
#include "Include/FKAlign.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class Base;
		class Canvas;
	}

	namespace Renderer
	{
		class Base;
	}

	namespace Debug
	{
		void FK_EXPORT Msg( const wchar_t* str, ... );
		void FK_EXPORT Msg( const char* str, ... );
		void FK_EXPORT AssertCheck( bool b, const char* strMsg );
	}


	namespace Colors
	{
		static const Color Black( 0, 0, 0, 255 );
		static const Color Red( 255, 0, 0, 255 );
		static const Color Yellow( 255, 255, 0, 255 );
		static const Color White( 255, 255, 255, 255 );
		static const Color Blue( 0, 0, 255, 255 );
		static const Color Green( 0, 255, 0, 255 );
		static const Color Grey( 200, 200, 200, 255 );
		static const Color GreyLight( 230, 230, 230, 255 );
		static const Color FKPink( 255, 65, 199, 255 );


	};

	extern FK_EXPORT Controls::Base*	HoveredControl;
	extern FK_EXPORT Controls::Base*	KeyboardFocus;
	extern FK_EXPORT Controls::Base*	MouseFocus;

	namespace Input
	{
		inline void Blur()
		{
			if ( KeyboardFocus )
			{ KeyboardFocus->Blur(); }
		}
	}
} 
//------------------------------------------------------------------------