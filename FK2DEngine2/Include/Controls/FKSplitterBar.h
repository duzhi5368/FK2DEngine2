/**
*	created:		2013-4-12   1:02
*	filename: 		FKSplitterBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKDragger.h"
#include "../../FK2DEngine2.h"
#include "FKBase.h"
#include "FKDragger.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT SplitterBar : public ControlsInternal::Dragger
		{
		public:

			FK_CONTROL( SplitterBar, ControlsInternal::Dragger );

			void Layout( Skin::Base* skin );
		};
	}
}
//------------------------------------------------------------------------