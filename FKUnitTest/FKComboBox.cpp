/**
*	created:		2013-4-13   20:37
*	filename: 		FKComboBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKComboBox.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class ComboBox : public GUnit
{
public:

	FK_CONTROL_INLINE( ComboBox, GUnit )
	{
		{
			FK2DEngine2::Controls::ComboBox* combo = new FK2DEngine2::Controls::ComboBox( this );
			combo->SetPos( 50, 50 );
			combo->SetWidth( 200 );
			combo->AddItem( L"Option One", "one" );
			combo->AddItem( L"Number Two", "two" );
			combo->AddItem( L"Door Three", "three" );
			combo->AddItem( L"Four Legs", "four" );
			combo->AddItem( L"Five Birds", "five" );
			combo->onSelection.Add( this, &ComboBox::OnComboSelect );
		}
		{
			// Empty..
			FK2DEngine2::Controls::ComboBox* combo = new FK2DEngine2::Controls::ComboBox( this );
			combo->SetPos( 50, 80 );
			combo->SetWidth( 200 );
		}
		{
			// Empty..
			FK2DEngine2::Controls::ComboBox* combo = new FK2DEngine2::Controls::ComboBox( this );
			combo->SetPos( 50, 110 );
			combo->SetWidth( 200 );

			for ( int i = 0; i < 500; i++ )
			{ combo->AddItem( L"Lots Of Options" ); }
		}
	}

	void OnComboSelect( FK2DEngine2::Controls::Base* pControl )
	{
		FK2DEngine2::Controls::ComboBox* combo = ( FK2DEngine2::Controls::ComboBox* ) pControl;
		UnitPrint( Utility::Format( L"Combo Changed: %ls", combo->GetSelectedItem()->GetText().GetUnicode().c_str() ) );
	}
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( ComboBox, L"ComboBox" );
//------------------------------------------------------------------------