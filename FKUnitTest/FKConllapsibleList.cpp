/**
*	created:		2013-4-13   20:34
*	filename: 		FKConllapsibleList
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKCollapsibleList.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class CollapsibleList : public GUnit
{
public:

	FK_CONTROL_INLINE( CollapsibleList, GUnit )
	{
		FK2DEngine2::Controls::CollapsibleList* pControl = new FK2DEngine2::Controls::CollapsibleList( this );
		pControl->SetSize( 100, 200 );
		pControl->SetPos( 10, 10 );
		{
			FK2DEngine2::Controls::CollapsibleCategory* cat = pControl->Add( "Category One" );
			cat->Add( "Hello" );
			cat->Add( "Two" );
			cat->Add( "Three" );
			cat->Add( "Four" );
		}
		{
			FK2DEngine2::Controls::CollapsibleCategory* cat = pControl->Add( "Shopping" );
			cat->Add( "Special" );
			cat->Add( "Two Noses" );
			cat->Add( "Orange ears" );
			cat->Add( "Beer" );
			cat->Add( "Three Eyes" );
			cat->Add( "Special" );
			cat->Add( "Two Noses" );
			cat->Add( "Orange ears" );
			cat->Add( "Beer" );
			cat->Add( "Three Eyes" );
			cat->Add( "Special" );
			cat->Add( "Two Noses" );
			cat->Add( "Orange ears" );
			cat->Add( "Beer" );
			cat->Add( "Three Eyes" );
		}
		{
			FK2DEngine2::Controls::CollapsibleCategory* cat = pControl->Add( "Category One" );
			cat->Add( "Hello" );
			cat->Add( "Two" );
			cat->Add( "Three" );
			cat->Add( "Four" );
		}
	}
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( CollapsibleList, L"CollapsibleList" );
//------------------------------------------------------------------------