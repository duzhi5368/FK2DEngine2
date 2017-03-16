/**
*	created:		2013-4-11   20:51
*	filename: 		FKToolTip
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "Controls/FKBase.h"
#include "../FK2DEngine2.h"
#include "FKSkin.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
namespace ToolTip
{
	FK_EXPORT bool TooltipActive();

	FK_EXPORT void Enable( Controls::Base* pControl );
	FK_EXPORT void Disable( Controls::Base* pControl );

	FK_EXPORT void ControlDeleted( Controls::Base* pControl );

	FK_EXPORT void RenderToolTip( Skin::Base* skin );
}
//------------------------------------------------------------------------