/**
*	created:		2013-4-13   21:11
*	filename: 		FKWindow
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Window : public GUnit
{
public:

	FK_CONTROL_INLINE( Window, GUnit )
	{
		{
			Controls::Button* pButton = new Controls::Button( this );
			pButton->SetText( "Normal Window" );
			pButton->onPress.Add( this, &ThisClass::OpenWindow );
			pButton->SetPos( 0, 0 );
		}
		{
			Controls::Button* pButton = new Controls::Button( this );
			pButton->SetText( "Modal Window" );
			pButton->onPress.Add( this, &ThisClass::OpenModalWindow );
			pButton->SetPos( 0, 32 );
		}
		m_iWindowCount = 1;
	}

	void OpenWindow()
	{
		Controls::WindowControl* pWindow = new Controls::WindowControl( GetCanvas() );
		pWindow->SetTitle( Utility::Format( L"Window %i", m_iWindowCount ) );
		pWindow->SetSize( 200 + rand() % 100, 200 + rand() % 100 );
		pWindow->SetPos( rand() % 700, rand() % 400 );
		pWindow->SetDeleteOnClose( true );
		m_iWindowCount++;
	}

	void OpenModalWindow()
	{
		Controls::WindowControl* pWindow = new Controls::WindowControl( GetCanvas() );
		pWindow->SetTitle( Utility::Format( L"Window %i", m_iWindowCount ) );
		pWindow->SetSize( 200 + rand() % 100, 200 + rand() % 100 );
		pWindow->MakeModal( true );
		pWindow->Position( Pos::Center );
		pWindow->SetDeleteOnClose( true );
		m_iWindowCount++;
	}

	int m_iWindowCount;

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Window, L"Window" );
//------------------------------------------------------------------------