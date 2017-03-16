/**
*	created:		2013-4-13   20:51
*	filename: 		FKNumeric
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKNumericUpDown.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Numeric : public GUnit
{
public:

	FK_CONTROL_INLINE( Numeric, GUnit )
	{
		Controls::NumericUpDown* pCtrl = new Controls::NumericUpDown( this );
		pCtrl->SetBounds( 10, 10, 50, 20 );
		pCtrl->SetValue( 50 );
		pCtrl->SetMax( 1000 );
		pCtrl->SetMin( -1000 );
		//	pCtrl->onPress.Add( this, &ThisClass::onButtonA );
	}

	void onButtonA( Controls::Base* pControl )
	{
		//	UnitPrint( L"Button Pressed (using 'OnPress' event)" );
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Numeric, L"Numeric" );
//------------------------------------------------------------------------