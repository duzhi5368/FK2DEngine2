/**
*	created:		2013-4-13   21:01
*	filename: 		FKRadioButton
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKRadioButtonController.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class RadioButton : public GUnit
{
public:

	FK_CONTROL_INLINE( RadioButton, GUnit )
	{
		FK2DEngine2::Controls::RadioButtonController* rc = new FK2DEngine2::Controls::RadioButtonController( this );
		rc->AddOption( "Option 1" );
		rc->AddOption( "Option 2" );
		rc->AddOption( "Option 3" );
		rc->AddOption( L"\u0627\u0644\u0622\u0646 \u0644\u062D\u0636\u0648\u0631" );
		rc->SetBounds( 30, 30, 200, 200 );
		rc->onSelectionChange.Add( this, &RadioButton::OnChange );
	}

	void OnChange( Controls::Base* pControl )
	{
		FK2DEngine2::Controls::RadioButtonController* rc = ( FK2DEngine2::Controls::RadioButtonController* ) pControl;
		FK2DEngine2::Controls::LabeledRadioButton* pSelected = rc->GetSelected();
		UnitPrint( Utility::Format( L"RadioButton changed (using 'OnChange' event)\n Chosen Item: '%ls'", pSelected->GetLabel()->GetText().GetUnicode().c_str() ) );
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( RadioButton, L"RadioButton" );
//------------------------------------------------------------------------