/**
*	created:		2013-4-13   21:05
*	filename: 		FKSlider
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKRadioButtonController.h"
#include "../FK2DEngine2/Include/Controls/FKVerticalSlider.h"
#include "../FK2DEngine2/Include/Controls/FKHorizontalSlider.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Slider : public GUnit
{
public:

	FK_CONTROL_INLINE( Slider, GUnit )
	{
		{
			FK2DEngine2::Controls::HorizontalSlider* pSlider = new FK2DEngine2::Controls::HorizontalSlider( this );
			pSlider->SetPos( 10, 10 );
			pSlider->SetSize( 150, 20 );
			pSlider->SetRange( 0, 100 );
			pSlider->SetFloatValue( 25 );
			pSlider->onValueChanged.Add( this, &Slider::SliderMoved );
		}
		{
			FK2DEngine2::Controls::HorizontalSlider* pSlider = new FK2DEngine2::Controls::HorizontalSlider( this );
			pSlider->SetPos( 10, 40 );
			pSlider->SetSize( 150, 20 );
			pSlider->SetRange( 0, 100 );
			pSlider->SetFloatValue( 20 );
			pSlider->SetNotchCount( 10 );
			pSlider->SetClampToNotches( true );
			pSlider->onValueChanged.Add( this, &Slider::SliderMoved );
		}
		{
			FK2DEngine2::Controls::VerticalSlider* pSlider = new FK2DEngine2::Controls::VerticalSlider( this );
			pSlider->SetPos( 160, 10 );
			pSlider->SetSize( 20, 200 );
			pSlider->SetRange( 0, 100 );
			pSlider->SetFloatValue( 25 );
			pSlider->onValueChanged.Add( this, &Slider::SliderMoved );
		}
		{
			FK2DEngine2::Controls::VerticalSlider* pSlider = new FK2DEngine2::Controls::VerticalSlider( this );
			pSlider->SetPos( 190, 10 );
			pSlider->SetSize( 20, 200 );
			pSlider->SetRange( 0, 100 );
			pSlider->SetFloatValue( 20 );
			pSlider->SetNotchCount( 10 );
			pSlider->SetClampToNotches( true );
			pSlider->onValueChanged.Add( this, &Slider::SliderMoved );
		}
	}

	void SliderMoved( Base* pControl )
	{
		FK2DEngine2::Controls::Slider* pSlider = ( FK2DEngine2::Controls::Slider* ) pControl;
		UnitPrint( Utility::Format( L"Slider Value: %.2f", ( float ) pSlider->GetFloatValue() ) );
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Slider, L"Slider" );
//------------------------------------------------------------------------