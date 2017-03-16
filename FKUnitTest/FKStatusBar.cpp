/**
*	created:		2013-4-13   21:07
*	filename: 		FKStatusBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKStatusBar.h"
#include "../FK2DEngine2/Include/Controls/FKLabel.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class StatusBar : public GUnit
{
public:

	FK_CONTROL_INLINE( StatusBar, GUnit )
	{
		Dock( Pos::Fill );
		FK2DEngine2::Controls::StatusBar* pStatus = new FK2DEngine2::Controls::StatusBar( this );
		FK2DEngine2::Controls::Label* pRight = new FK2DEngine2::Controls::Label( pStatus );
		pRight->SetText( L"Label Added to Right" );
		pStatus->AddControl( pRight, true );
	}

	void Layout( FK2DEngine2::Skin::Base* skin ) {}
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( StatusBar, L"StatusBar" );
//------------------------------------------------------------------------