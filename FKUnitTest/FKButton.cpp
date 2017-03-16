/**
*	created:		2013-4-13   1:06
*	filename: 		FKButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Button : public GUnit
{
public:

	FK_CONTROL_INLINE( Button, GUnit )
	{
		// Normal button
		Controls::Button* pButtonA = new Controls::Button( this );
		pButtonA->SetText( L"Event Tester" );
		pButtonA->onPress.Add( this, &Button::onButtonA );
		{
			Controls::Button* pButtonA = new Controls::Button( this );
			pButtonA->SetBounds( 200, 30, 300, 200 );
			pButtonA->SetText( L"Event Tester" );
			pButtonA->onPress.Add( this, &Button::onButtonA );
		}
		// Unicode test
		Controls::Button* pButtonB = new Controls::Button( this );
		pButtonB->SetText( L"\u0417\u0430\u043C\u0435\u0436\u043D\u0430\u044F \u043C\u043E\u0432\u0430" );
		FK2DEngine2::Align::PlaceBelow( pButtonB, pButtonA, 10 );
		// Image with text
		Controls::Button* pButtonC = new Controls::Button( this );
		pButtonC->SetText( L"Image Button" );
		pButtonC->SetImage( L"test16.png" );
		FK2DEngine2::Align::PlaceBelow( pButtonC, pButtonB, 10 );
		// Just image
		Controls::Button* pButtonD = new Controls::Button( this );
		pButtonD->SetText( L"" );
		pButtonD->SetImage( L"test16.png" );
		pButtonD->SetSize( 20, 20 );
		FK2DEngine2::Align::PlaceBelow( pButtonD, pButtonC, 10 );
		// Toggle button
		Controls::Button* pButtonE = new Controls::Button( this );
		pButtonE->SetText( L"Toggle Me" );
		pButtonE->SetIsToggle( true );
		pButtonE->onToggle.Add( this, &Button::OnToggle );
		pButtonE->onToggleOn.Add( this, &Button::OnToggleOn );
		pButtonE->onToggleOff.Add( this, &Button::OnToggleOff );
		FK2DEngine2::Align::PlaceBelow( pButtonE, pButtonD, 10 );
		// Disabled Button
		Controls::Button* pButtonF = new Controls::Button( this );
		pButtonF->SetText( L"Disabled :D" );
		pButtonF->SetDisabled( true );
		FK2DEngine2::Align::PlaceBelow( pButtonF, pButtonE, 10 );
		// Tooltip Button
		Controls::Button* pButtonG = new Controls::Button( this );
		pButtonG->SetText( L"With Tooltip" );
		pButtonG->SetToolTip( "This is a tooltip!" );
		FK2DEngine2::Align::PlaceBelow( pButtonG, pButtonF, 10 );
	}

	void onButtonA( Controls::Base* pControl )
	{
		UnitPrint( L"Button Pressed (using 'OnPress' event)" );
	}

	void OnToggle( Controls::Base* pControl )
	{
		UnitPrint( L"Button Toggled (using 'OnToggle' event)" );
	}

	void OnToggleOn( Controls::Base* pControl )
	{
		UnitPrint( L"Button Toggled ON (using 'OnToggleOn' event)" );
	}

	void OnToggleOff( Controls::Base* pControl )
	{
		UnitPrint( L"Button Toggled Off (using 'OnToggleOff' event)" );
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Button, L"Button" );
//------------------------------------------------------------------------