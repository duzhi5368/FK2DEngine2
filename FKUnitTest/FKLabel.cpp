/**
*	created:		2013-4-13   20:43
*	filename: 		FKLabel
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKLabel.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class Label : public GUnit
{
public:

	FK_CONTROL_INLINE( Label, GUnit )
	{
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( "Garry's Normal Label" );
			label->SizeToContents();
			label->SetPos( 10, 10 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Chinese: \u4E45\u6709\u5F52\u5929\u613F \u7EC8\u8FC7\u9B3C\u95E8\u5173" );
			label->SizeToContents();
			label->SetPos( 10, 30 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Japanese: \u751F\u3080\u304E\u3000\u751F\u3054\u3081\u3000\u751F\u305F\u307E\u3054" );
			label->SizeToContents();
			label->SetPos( 10, 50 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Korean: \uADF9\uC9C0\uD0D0\uD5D8\u3000\uD611\uD68C\uACB0\uC131\u3000\uCCB4\uACC4\uC801\u3000\uC5F0\uAD6C" );
			label->SizeToContents();
			label->SetPos( 10, 70 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Hindi: \u092F\u0947 \u0905\u0928\u0941\u091A\u094D\u091B\u0947\u0926 \u0939\u093F\u0928\u094D\u0926\u0940 \u092E\u0947\u0902 \u0939\u0948\u0964" );
			label->SizeToContents();
			label->SetPos( 10, 90 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Arabic: \u0627\u0644\u0622\u0646 \u0644\u062D\u0636\u0648\u0631 \u0627\u0644\u0645\u0624\u062A\u0645\u0631 \u0627\u0644\u062F\u0648\u0644\u064A" );
			label->SizeToContents();
			label->SetPos( 10, 110 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Wow, Coloured Text" );
			label->SetTextColor( FK2DEngine2::Color( 0, 0, 255, 255 ) );
			label->SizeToContents();
			label->SetPos( 10, 130 );
		}
		{
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Coloured Text With Alpha" );
			label->SetTextColor( FK2DEngine2::Color( 0, 0, 255, 100 ) );
			label->SizeToContents();
			label->SetPos( 10, 150 );
		}
		{
			m_Font.facename = L"Comic Sans MS";
			m_Font.size = 25;
			FK2DEngine2::Controls::Label* label = new FK2DEngine2::Controls::Label( this );
			label->SetText( L"Custom Font (Comic Sans 25)" );
			label->SetFont( &m_Font );
			label->SizeToContents();
			label->SetPos( 10, 170 );
		}
	}

	FK2DEngine2::Font	m_Font;
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( Label, L"Label" );
//------------------------------------------------------------------------