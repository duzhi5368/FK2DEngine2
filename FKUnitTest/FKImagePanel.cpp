/**
*	created:		2013-4-13   20:42
*	filename: 		FKImagePanel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKImagePanel.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class ImagePanel : public GUnit
{
public:

	FK_CONTROL_INLINE( ImagePanel, GUnit )
	{
		// Normal
		{
			Controls::ImagePanel* img = new Controls::ImagePanel( this );
			img->SetImage( L"FK.png" );
			img->SetBounds( 10, 10, 100, 100 );
		}
		// Missing
		{
			Controls::ImagePanel* img = new Controls::ImagePanel( this );
			img->SetImage( L"missingimage.png" );
			img->SetBounds( 120, 10, 100, 100 );
		}
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( ImagePanel, L"ImagePanel" );
//------------------------------------------------------------------------