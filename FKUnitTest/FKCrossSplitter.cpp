/**
*	created:		2013-4-13   20:38
*	filename: 		FKCrossSplitter
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKCrossSplitter.h"
#include "../FK2DEngine2/Include/Controls/FKStatusBar.h"
#include "../FK2DEngine2/Include/Controls/FKButton.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class CrossSplitter : public GUnit
{
public:

	FK_CONTROL_INLINE( CrossSplitter, GUnit )
	{
		Dock( Pos::Fill );
		m_bSplittersVisible = false;
		m_iCurZoom = 0;
		m_Splitter = new FK2DEngine2::Controls::CrossSplitter( this );
		m_Splitter->SetPos( 0, 0 );
		m_Splitter->Dock( Pos::Fill );
		{
			FK2DEngine2::Controls::Button* testButton =  new FK2DEngine2::Controls::Button( m_Splitter );
			testButton->SetText( "TOPLEFT" );
			m_Splitter->SetPanel( 0, testButton );
		}
		{
			FK2DEngine2::Controls::Button* testButton =  new FK2DEngine2::Controls::Button( m_Splitter );
			testButton->SetText( "TOPRIGHT" );
			m_Splitter->SetPanel( 1, testButton );
		}
		{
			FK2DEngine2::Controls::Button* testButton =  new FK2DEngine2::Controls::Button( m_Splitter );
			testButton->SetText( "BOTTOMRIGHT" );
			m_Splitter->SetPanel( 2, testButton );
		}
		{
			FK2DEngine2::Controls::Button* testButton =  new FK2DEngine2::Controls::Button( m_Splitter );
			testButton->SetText( "BOTTOMLEFT" );
			m_Splitter->SetPanel( 3, testButton );
		}
		//Status bar to hold unit testing buttons
		FK2DEngine2::Controls::StatusBar* pStatus = new FK2DEngine2::Controls::StatusBar( this );
		pStatus->Dock( Pos::Bottom );
		{
			FK2DEngine2::Controls::Button* pButton = new FK2DEngine2::Controls::Button( pStatus );
			pButton->SetText( "Zoom" );
			pButton->onPress.Add( this, &CrossSplitter::ZoomTest );
			pStatus->AddControl( pButton, false );
		}
		{
			FK2DEngine2::Controls::Button* pButton = new FK2DEngine2::Controls::Button( pStatus );
			pButton->SetText( "UnZoom" );
			pButton->onPress.Add( this, &CrossSplitter::UnZoomTest );
			pStatus->AddControl( pButton, false );
		}
		{
			FK2DEngine2::Controls::Button* pButton = new FK2DEngine2::Controls::Button( pStatus );
			pButton->SetText( "CenterPanels" );
			pButton->onPress.Add( this, &CrossSplitter::CenterPanels );
			pStatus->AddControl( pButton, true );
		}
	}

	void ZoomTest( FK2DEngine2::Controls::Base* pFromPanel )
	{
		m_Splitter->Zoom( m_iCurZoom );
		m_iCurZoom++;

		if ( m_iCurZoom == 4 )
		{ m_iCurZoom = 0; }
	}

	void UnZoomTest( FK2DEngine2::Controls::Base* pFromPanel )
	{
		m_Splitter->UnZoom();
	}

	void CenterPanels( FK2DEngine2::Controls::Base* pFromPanel )
	{
		m_Splitter->CenterPanels();
		m_Splitter->UnZoom();
	}

	void Layout( FK2DEngine2::Skin::Base* skin ) {}

	bool m_bSplittersVisible;
	int	m_iCurZoom;
	Controls::CrossSplitter* m_Splitter;

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( CrossSplitter, L"CrossSplitter" );
//------------------------------------------------------------------------