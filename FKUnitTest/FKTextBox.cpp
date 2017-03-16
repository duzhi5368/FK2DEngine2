/**
*	created:		2013-4-13   21:09
*	filename: 		FKTextBox
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKTextBox.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class TextBox : public GUnit
{
public:

	FK_CONTROL_INLINE( TextBox, GUnit )
	{
		{
			FK2DEngine2::Controls::TextBox* label = new FK2DEngine2::Controls::TextBox( this );
			label->SetText( "" );
			label->SetPos( 10, 10 );
			label->onTextChanged.Add( this, &ThisClass::OnEdit );
			label->onReturnPressed.Add( this, &ThisClass::OnSubmit );
		}
		{
			FK2DEngine2::Controls::TextBox* label = new FK2DEngine2::Controls::TextBox( this );
			label->SetText( "Normal Everyday Label" );
			label->SetPos( 10, 10 + 25 );
		}
		{
			FK2DEngine2::Controls::TextBox* label = new FK2DEngine2::Controls::TextBox( this );
			label->SetText( "Select All Text On Focus" );
			label->SetPos( 10, 10 + 25 * 2 );
			label->SetSelectAllOnFocus( true );
		}
		{
			FK2DEngine2::Controls::TextBox* label = new FK2DEngine2::Controls::TextBox( this );
			label->SetText( L"Different Coloured Text, for some reason" );
			label->SetTextColor( FK2DEngine2::Color( 255, 0, 255, 255 ) );
			label->SetPos( 10, 10 + 25 * 3 );
		}
		{
			FK2DEngine2::Controls::TextBoxNumeric* label = new FK2DEngine2::Controls::TextBoxNumeric( this );
			label->SetText( L"2004" );
			label->SetTextColor( FK2DEngine2::Color( 255, 0, 255, 255 ) );
			label->SetPos( 10, 10 + 25 * 4 );
		}
		{
			m_Font.facename = L"Impact";
			m_Font.size = 50;
			FK2DEngine2::Controls::TextBox* label = new FK2DEngine2::Controls::TextBox( this );
			label->SetText( L"Different Font" );
			label->SetPos( 10, 10 + 25 * 5 );
			label->SetFont( &m_Font );
			label->SetSize( 200, 55 );
		}
		{
			FK2DEngine2::Controls::TextBoxMultiline* label = new FK2DEngine2::Controls::TextBoxMultiline( this );
			label->SetText( "I think we're losing sight of the real issue here, which is: what are we gonna call ourselves?\n\nErm, and I think it comes down to a choice between \"The League Against Salivating Monsters\" or my own personal preference, which is \"The Committee for the Liberation and Integration of Terrifying Organisms and their Rehabilitation Into Society.\" Erm, one drawback with that: the abbreviation is \"CLITORIS.\"" );
			label->SetPos( 220, 10 );
			label->SetSize( 200, 180 );
		}
	}

	void OnEdit( FK2DEngine2::Controls::Base* pControl )
	{

		FK2DEngine2::Controls::TextBox* textbox = ( FK2DEngine2::Controls::TextBox* )( pControl );
		UnitPrint( Utility::Format( L"Textbox Edit: [%ls]\n", textbox->GetText().GetUnicode().c_str() ) );
	}

	void OnSubmit( FK2DEngine2::Controls::Base* pControl )
	{
		FK2DEngine2::Controls::TextBox* textbox = ( FK2DEngine2::Controls::TextBox* )( pControl );
		UnitPrint( Utility::Format( L"Textbox Submit: [%ls]\n", textbox->GetText().GetUnicode().c_str() ) );
	}

	FK2DEngine2::Font	m_Font;
};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( TextBox, L"TextBox" );
//------------------------------------------------------------------------
