/**
*	created:		2013-4-13   20:35
*	filename: 		FKColorPicker
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKColorPicker.h"
#include "../FK2DEngine2/Include/Controls/FKHSVColorPicker.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class ColorPicker : public GUnit
{
public:

	FK_CONTROL_INLINE( ColorPicker, GUnit )
	{
		Controls::ColorPicker* pCtrl = new Controls::ColorPicker( this );
		pCtrl->SetBounds( 0, 10, 250, 250 );
		Controls::HSVColorPicker* pHSVCtrl = new Controls::HSVColorPicker( this );
		pHSVCtrl->SetBounds( 260, 10, 250, 150 );
	}
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( ColorPicker, L"ColorPicker" );
//------------------------------------------------------------------------