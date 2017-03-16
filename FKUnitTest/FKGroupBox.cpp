/**
*	created:		2013-4-13   20:41
*	filename: 		FKGroupBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKGroupBox.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class GroupBox : public GUnit
{
public:

	FK_CONTROL_INLINE( GroupBox, GUnit )
	{
		FK2DEngine2::Controls::GroupBox* pGroup = new FK2DEngine2::Controls::GroupBox( this );
		pGroup->SetText( "Group Box" );
		pGroup->SetSize( 300, 200 );
	}
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( GroupBox, L"GroupBox" );
//------------------------------------------------------------------------