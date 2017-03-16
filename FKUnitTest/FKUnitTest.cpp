/**
*	created:		2013-4-13   21:12
*	filename: 		FKUnitTest
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKDockedTabControl.h"
#include "../FK2DEngine2/Include/Controls/FKWindowControl.h"
#include "../FK2DEngine2/Include/Controls/FKCollapsibleList.h"
#include "../FK2DEngine2/Include/Controls/Layout/FKPosition.h"
#include "../FK2DEngine2/Include/FKPlatform.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
#define ADD_UNIT_TEST( name )\
	GUnit* RegisterUnitTest_##name( FK2DEngine2::Controls::Base* tab );\
	{\
		Controls::Button* pButton = cat->Add( #name );\
		pButton->SetName( #name );\
		GUnit* test = RegisterUnitTest_##name( pCenter );\
		test->Hide();\
		test->SetUnitTest( this );\
		pButton->onPress.Add( this, &ThisClass::OnCategorySelect, FK2DEngine2::Event::Packet( test ) );\
	}\
 
//------------------------------------------------------------------------
FK2DEngine2::Controls::TabButton* pButton = NULL;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( UnitTest )
{
	m_pLastControl = NULL;
	Dock( Pos::Fill );
	SetSize( 1024, 768 );
	Controls::CollapsibleList* pList = new Controls::CollapsibleList( this );
	GetLeft()->GetTabControl()->AddPage( "CollapsibleList", pList );
	GetLeft()->SetWidth( 150 );
	m_TextOutput = new Controls::ListBox( GetBottom() );
	pButton = GetBottom()->GetTabControl()->AddPage( "Output", m_TextOutput );
	GetBottom()->SetHeight( 200 );
	m_StatusBar = new Controls::StatusBar( this );
	m_StatusBar->Dock( Pos::Bottom );
	Controls::Layout::Center* pCenter = new Controls::Layout::Center( this );
	pCenter->Dock( Pos::Fill );
	{
		Controls::CollapsibleCategory* cat = pList->Add( "Basic" );
		ADD_UNIT_TEST( Button );
		ADD_UNIT_TEST( Label );
		ADD_UNIT_TEST( LabelMultiline );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "Non-Interactive" );
		ADD_UNIT_TEST( ProgressBar );
		ADD_UNIT_TEST( GroupBox );
		ADD_UNIT_TEST( ImagePanel );
		ADD_UNIT_TEST( StatusBar );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "Controls" );
		ADD_UNIT_TEST( ComboBox );
		ADD_UNIT_TEST( TextBox );
		ADD_UNIT_TEST( ListBox );
		ADD_UNIT_TEST( CrossSplitter );
		ADD_UNIT_TEST( RadioButton );
		ADD_UNIT_TEST( Checkbox );
		ADD_UNIT_TEST( Numeric );
		ADD_UNIT_TEST( Slider );
		ADD_UNIT_TEST( MenuStrip );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "Containers" );
		ADD_UNIT_TEST( Window );
		ADD_UNIT_TEST( TreeControl );
		ADD_UNIT_TEST( Properties );
		ADD_UNIT_TEST( TabControl );
		ADD_UNIT_TEST( ScrollControl );
		ADD_UNIT_TEST( PageControl );
	}
	{
		Controls::CollapsibleCategory* cat = pList->Add( "Non-Standard" );
		ADD_UNIT_TEST( CollapsibleList );
		ADD_UNIT_TEST( ColorPicker );
	}
	m_StatusBar->SendToBack();
	PrintText( L"Unit Test Started.\n" );
	m_fLastSecond = FK2DEngine2::Platform::GetTimeInSeconds();
	m_iFrames = 0;
	pList->GetNamedChildren( "MenuStrip" ).DoAction();
}
//------------------------------------------------------------------------
void UnitTest::OnCategorySelect( FK2DEngine2::Event::Info info )
{
	if ( m_pLastControl )
	{
		m_pLastControl->Hide();
	}

	info.Packet->Control->Show();
	m_pLastControl = info.Packet->Control;
}
//------------------------------------------------------------------------
void UnitTest::PrintText( const FK2DEngine2::UnicodeString & str )
{
	m_TextOutput->AddItem( str );
	m_TextOutput->ScrollToBottom();
}
//------------------------------------------------------------------------
void UnitTest::Render( FK2DEngine2::Skin::Base* skin )
{
	m_iFrames++;

	if ( m_fLastSecond < FK2DEngine2::Platform::GetTimeInSeconds() )
	{
		m_StatusBar->SetText( FK2DEngine2::Utility::Format( L"FK2DEngine2 Unit Test - %i fps", m_iFrames * 2 ) );
		m_fLastSecond = FK2DEngine2::Platform::GetTimeInSeconds() + 0.5f;
		m_iFrames = 0;
	}

	BaseClass::Render( skin );
}
//------------------------------------------------------------------------
void GUnit::UnitPrint( FK2DEngine2::UnicodeString str )
{
	m_pUnitTest->PrintText( str );
}
//------------------------------------------------------------------------
void GUnit::UnitPrint( FK2DEngine2::String str )
{
	UnitPrint( Utility::StringToUnicode( str ) );
}
//------------------------------------------------------------------------