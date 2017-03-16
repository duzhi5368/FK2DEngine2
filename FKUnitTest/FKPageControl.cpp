/**
*	created:		2013-4-13   20:53
*	filename: 		FKPageControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/FKControls.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class PageControl : public GUnit
{
public:

	FK_CONTROL_INLINE( PageControl, GUnit )
	{
		FK2DEngine2::Controls::PageControl* control = new FK2DEngine2::Controls::PageControl( this );
		control->SetSize( 500, 300 );
		control->SetPageCount( 5 );
		control->onPageChanged.Add( this, &ThisClass::OnPageChanged );
		control->onFinish.Add( this, &ThisClass::OnFinish );
		// Page 0
		{
			FK2DEngine2::Controls::Button* pButton = new FK2DEngine2::Controls::Button( control->GetPage( 0 ) );
			pButton->Dock( Pos::Fill );
			pButton->SetText( "This button is fill docked on page 0" );
		}
		// Page 1
		{
			FK2DEngine2::Controls::Button* pButton = new FK2DEngine2::Controls::Button( control->GetPage( 1 ) );
			pButton->Dock( Pos::Top );
			pButton->SetText( "This button is top docked on page 1" );
		}
		// Page 2
		{
			FK2DEngine2::Controls::Button* pButton = new FK2DEngine2::Controls::Button( control->GetPage( 2 ) );
			pButton->SetSize( 400, 1000 );
			pButton->SetPos( 50, 50 );
			pButton->SetText( "This button is long to test scrolling (page 2)" );
		}
	}

	void OnPageChanged( Event::Info info )
	{
		UnitPrint( Utility::Format( L"PageControl Changed Page: %i", info.Integer ) );
	}

	void OnFinish( Event::Info info )
	{
		UnitPrint( L"Finish Pressed" );
	}
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( PageControl, L"PageControl" );
//------------------------------------------------------------------------