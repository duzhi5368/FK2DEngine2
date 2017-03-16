/**
*	created:		2013-4-13   21:08
*	filename: 		FKTabControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKTabControl.h"
#include "../FK2DEngine2/Include/Controls/FKRadioButtonController.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class TabControl : public GUnit
{
public:

	Controls::TabControl* m_pDockControlLeft;

	FK_CONTROL_INLINE( TabControl, GUnit )
	{
		{
			m_pDockControlLeft = new Controls::TabControl( this );
			m_pDockControlLeft->SetBounds( 10, 10, 200, 200 );
			{
				Controls::TabButton* pButton = m_pDockControlLeft->AddPage( L"Controls" );
				Base* pPage = pButton->GetPage();
				{
					Controls::RadioButtonController* pRadio = new Controls::RadioButtonController( pPage );
					pRadio->SetBounds( 10, 10, 100, 100 );
					pRadio->AddOption( "Top" )->Select();
					pRadio->AddOption( "Bottom" );
					pRadio->AddOption( "Left" );
					pRadio->AddOption( "Right" );
					pRadio->onSelectionChange.Add( this, &ThisClass::OnDockChange );
				}
			}
			m_pDockControlLeft->AddPage( L"Red" );
			m_pDockControlLeft->AddPage( L"Green" );
			m_pDockControlLeft->AddPage( L"Blue" );
		}
		{
			Controls::TabControl* pDragMe = new Controls::TabControl( this );
			pDragMe->SetBounds( 220, 10, 200, 200 );
			pDragMe->AddPage( L"You" );
			pDragMe->AddPage( L"Can" );
			pDragMe->AddPage( L"Reorder" )->SetImage( L"test16.png" );
			pDragMe->AddPage( L"These" );
			pDragMe->AddPage( L"Tabs" );
			pDragMe->SetAllowReorder( true );
		}
	}

	void OnDockChange( FK2DEngine2::Controls::Base* pControl )
	{
		FK2DEngine2::Controls::RadioButtonController* rc = ( FK2DEngine2::Controls::RadioButtonController* ) pControl;

		if ( rc->GetSelectedLabel() == L"Top" )		{ m_pDockControlLeft->SetTabStripPosition( Pos::Top ); }
		if ( rc->GetSelectedLabel() == L"Bottom" )	{ m_pDockControlLeft->SetTabStripPosition( Pos::Bottom ); }
		if ( rc->GetSelectedLabel() == L"Left" )	{ m_pDockControlLeft->SetTabStripPosition( Pos::Left ); }
		if ( rc->GetSelectedLabel() == L"Right" )	{ m_pDockControlLeft->SetTabStripPosition( Pos::Right ); }
	}

	FK2DEngine2::Font	m_Font;
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( TabControl, L"TabControl" );
//------------------------------------------------------------------------