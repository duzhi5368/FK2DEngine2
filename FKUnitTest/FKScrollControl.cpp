/**
*	created:		2013-4-13   21:02
*	filename: 		FKScrollControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKScrollControl.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class ScrollControl : public GUnit
{
public:

	FK_CONTROL_INLINE( ScrollControl, GUnit )
	{
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 10, 10, 100, 100 );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Twice As Big" );
			pTestButton->SetBounds( 0, 0, 200, 200 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 110, 10, 100, 100 );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Same Size" );
			pTestButton->SetBounds( 0, 0, 100, 100 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 210, 10, 100, 100 );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Wide" );
			pTestButton->SetBounds( 0, 0, 200, 50 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 310, 10, 100, 100 );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Tall" );
			pTestButton->SetBounds( 0, 0, 50, 200 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 410, 10, 100, 100 );
			pCtrl->SetScroll( false, true );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Vertical" );
			pTestButton->SetBounds( 0, 0, 200, 200 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 510, 10, 100, 100 );
			pCtrl->SetScroll( true, false );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Horinzontal" );
			pTestButton->SetBounds( 0, 0, 200, 200 );
		}
		// Bottom Row
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 10, 110, 100, 100 );
			pCtrl->SetAutoHideBars( true );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Twice As Big" );
			pTestButton->SetBounds( 0, 0, 200, 200 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 110, 110, 100, 100 );
			pCtrl->SetAutoHideBars( true );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Same Size" );
			pTestButton->SetBounds( 0, 0, 100, 100 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 210, 110, 100, 100 );
			pCtrl->SetAutoHideBars( true );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Wide" );
			pTestButton->SetBounds( 0, 0, 200, 50 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 310, 110, 100, 100 );
			pCtrl->SetAutoHideBars( true );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Tall" );
			pTestButton->SetBounds( 0, 0, 50, 200 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 410, 110, 100, 100 );
			pCtrl->SetAutoHideBars( true );
			pCtrl->SetScroll( false, true );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Vertical" );
			pTestButton->SetBounds( 0, 0, 200, 200 );
		}
		{
			FK2DEngine2::Controls::ScrollControl* pCtrl = new FK2DEngine2::Controls::ScrollControl( this );
			pCtrl->SetBounds( 510, 110, 100, 100 );
			pCtrl->SetAutoHideBars( true );
			pCtrl->SetScroll( true, false );
			Controls::Button* pTestButton = new Controls::Button( pCtrl );
			pTestButton->SetText( L"Horinzontal" );
			pTestButton->SetBounds( 0, 0, 200, 200 );
		}
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( ScrollControl, L"Scroll" );
//------------------------------------------------------------------------