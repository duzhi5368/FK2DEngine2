/**
*	created:		2013-4-12   0:18
*	filename: 		FKLabelClickable
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../FK2DEngine2.h"
#include "../../Include/FKSkin.h"
#include "../../Include/Controls/FKLabelClickable.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( LabelClickable )
{
	SetIsToggle( false );
	SetCursor( FK2DEngine2::CursorType::Finger );
	SetAlignment( FK2DEngine2::Pos::Left | FK2DEngine2::Pos::CenterV );
}
//------------------------------------------------------------------------
void LabelClickable::Render( Skin::Base* skin )
{
	//skin->DrawButton( this, IsDepressed(), IsToggle() && GetToggleState() );
}
//------------------------------------------------------------------------