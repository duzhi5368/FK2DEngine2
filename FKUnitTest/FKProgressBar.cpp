/**
*	created:		2013-4-13   20:54
*	filename: 		FKProgressBar
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKRadioButtonController.h"
#include "../FK2DEngine2/Include/Controls/FKProgressBar.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class ProgressBar : public GUnit
{
public:

	FK_CONTROL_INLINE( ProgressBar, GUnit )
	{
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 20, 200, 20 ) );
			pb->SetValue( 0.27f );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 50, 200, 20 ) );
			pb->SetValue( 0.66f );
			pb->SetAlignment( Pos::Right | Pos::CenterV );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 80, 200, 20 ) );
			pb->SetValue( 0.88f );
			pb->SetAlignment( Pos::Left | Pos::CenterV );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 110, 200, 20 ) );
			pb->SetAutoLabel( false );
			pb->SetValue( 0.20f );
			pb->SetAlignment( Pos::Right | Pos::CenterV );
			pb->SetText( L"40,245 MB" );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 140, 200, 20 ) );
			pb->SetAutoLabel( false );
			pb->SetValue( 1.00f );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 170, 200, 20 ) );
			pb->SetAutoLabel( false );
			pb->SetValue( 0.00f );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 110, 200, 200, 20 ) );
			pb->SetAutoLabel( false );
			pb->SetValue( 0.50f );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 20, 20, 25, 200 ) );
			pb->SetVertical();
			pb->SetValue( 0.25f );
			pb->SetAlignment( Pos::Top | Pos::CenterH );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 50, 20, 25, 200 ) );
			pb->SetVertical();
			pb->SetValue( 0.40f );
		}
		{
			FK2DEngine2::Controls::ProgressBar* pb = new FK2DEngine2::Controls::ProgressBar( this );
			pb->SetBounds( FK2DEngine2::Rect( 80, 20, 25, 200 ) );
			pb->SetVertical();
			pb->SetAlignment( Pos::Bottom | Pos::CenterH );
			pb->SetValue( 0.65f );
		}
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( ProgressBar, L"ProgressBar" );
//------------------------------------------------------------------------