/**
*	created:		2013-4-13   20:55
*	filename: 		FKProperties
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKProperties.h"
#include "../FK2DEngine2/Include/Controls/FKPropertyTree.h"
#include "../FK2DEngine2/Include/Controls/Property/FKColorSelector.h"
#include "../FK2DEngine2/Include/Controls/Property/FKCheckbox.h"
#include "../FK2DEngine2/Include/Controls/Property/FKComboBox.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Properties : public GUnit
{
public:

	FK_CONTROL_INLINE( Properties, GUnit )
	{
		{
			FK2DEngine2::Controls::Properties* props = new FK2DEngine2::Controls::Properties( this );
			props->SetBounds( 10, 10, 150, 300 );
			{
				{
					FK2DEngine2::Controls::PropertyRow* pRow = props->Add( L"First Name" );
					pRow->onChange.Add( this, &Properties::OnFirstNameChanged );
				}
				props->Add( L"Middle Name" );
				props->Add( L"Last Name" );
			}
		}
		{
			FK2DEngine2::Controls::PropertyTree* ptree = new FK2DEngine2::Controls::PropertyTree( this );
			ptree->SetBounds( 200, 10, 200, 200 );
			{
				FK2DEngine2::Controls::Properties* props = ptree->Add( L"Item One" );
				props->Add( L"Middle Name" );
				props->Add( L"Last Name" );
				props->Add( L"Four" );
			}
			{
				FK2DEngine2::Controls::Properties* props = ptree->Add( L"Item Two" );
				props->Add( L"More Items" );
				props->Add( L"Checkbox", new FK2DEngine2::Controls::Property::Checkbox( props ), L"1" );
				props->Add( L"To Fill" );
				props->Add( L"ColorSelector", new FK2DEngine2::Controls::Property::ColorSelector( props ), L"255 0 0" );
				props->Add( L"Out Here" );
				// Combo Box Test
				{
					FK2DEngine2::Controls::Property::ComboBox* pCombo = new FK2DEngine2::Controls::Property::ComboBox( props );
					pCombo->GetComboBox()->AddItem( L"Option One", "one" );
					pCombo->GetComboBox()->AddItem( L"Number Two", "two" );
					pCombo->GetComboBox()->AddItem( L"Door Three", "three" );
					pCombo->GetComboBox()->AddItem( L"Four Legs", "four" );
					pCombo->GetComboBox()->AddItem( L"Five Birds", "five" );
					FK2DEngine2::Controls::PropertyRow* pRow = props->Add( L"ComboBox", pCombo, L"1" );
					pRow->onChange.Add( this, &Properties::OnFirstNameChanged );
				}
			}
			ptree->ExpandAll();
		}
	}

	void OnFirstNameChanged( Controls::Base* pControl )
	{
		FK2DEngine2::Controls::PropertyRow* pRow = ( FK2DEngine2::Controls::PropertyRow* ) pControl;
		UnitPrint( Utility::Format( L"First Name Changed: %ls", pRow->GetProperty()->GetPropertyValue().GetUnicode().c_str() ) );
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Properties, L"Properties" );
//------------------------------------------------------------------------