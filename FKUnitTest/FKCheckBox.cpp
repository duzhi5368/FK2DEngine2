/**
*	created:		2013-4-13   20:32
*	filename: 		FKCheckBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKCheckBox.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Checkbox : public GUnit
{
public:

	FK_CONTROL_INLINE( Checkbox, GUnit )
	{
		FK2DEngine2::Controls::CheckBox* check = new FK2DEngine2::Controls::CheckBox( this );
		check->SetPos( 10, 10 );
		check->onChecked.Add( this, &Checkbox::OnChecked );
		check->onUnChecked.Add( this, &Checkbox::OnUnchecked );
		check->onCheckChanged.Add( this, &Checkbox::OnCheckChanged );
		FK2DEngine2::Controls::CheckBoxWithLabel* labeled = new FK2DEngine2::Controls::CheckBoxWithLabel( this );
		labeled->SetPos( 10, 30 );
		labeled->Label()->SetText( "Labeled CheckBox" );
		labeled->Checkbox()->onChecked.Add( this, &Checkbox::OnChecked );
		labeled->Checkbox()->onUnChecked.Add( this, &Checkbox::OnUnchecked );
		labeled->Checkbox()->onCheckChanged.Add( this, &Checkbox::OnCheckChanged );
		{
			FK2DEngine2::Controls::CheckBox* check = new FK2DEngine2::Controls::CheckBox( this );
			check->SetPos( 10, 54 );
			check->SetDisabled( true );
		}
	}

	void OnChecked( Controls::Base* pControl )
	{
		UnitPrint( L"Checkbox Checked (using 'OnChecked' event)" );
	}

	void OnUnchecked( Controls::Base* pControl )
	{
		UnitPrint( L"Checkbox Unchecked (using 'OnUnchecked' event)" );
	}

	void OnCheckChanged( Controls::Base* pControl )
	{
		UnitPrint( L"Checkbox CheckChanged (using 'OnCheckChanged' event)" );
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Checkbox, L"Checkbox" );
//------------------------------------------------------------------------