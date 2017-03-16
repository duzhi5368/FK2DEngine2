/**
*	created:		2013-4-13   1:13
*	filename: 		FKDemoWindowsGDI
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
//------------------------------------------------------------------------
#include <windows.h>
#include <objbase.h>
#include <GdiPlus.h>
//------------------------------------------------------------------------
#include "../FK2DEngine2/FK2DEngine2.h"
#include "../FK2DEngine2/Include/Skins/FKSimple.h"
#include "../FK2DEngine2/Include/Skins/FKTexturedBase.h"
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Input/FKWindows.h"
#include "../FK2DEngine2/Include/Renderers/FKGDIPlus.h"
//------------------------------------------------------------------------
#pragma comment( lib, "gdiplus.lib" )
//------------------------------------------------------------------------
HWND CreateGameWindow( void )
{
	WNDCLASS	wc;
	ZeroMemory( &wc, sizeof( wc ) );
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= DefWindowProc;
	wc.hInstance		= GetModuleHandle( NULL );
	wc.lpszClassName	= L"FKWindow";
	wc.hCursor			= LoadCursor( NULL, IDC_ARROW );
	RegisterClass( &wc );
	HWND hWindow = CreateWindowEx( ( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE ) , wc.lpszClassName, L"FKWindowsGDISample", ( WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN ) & ~( WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME ), -1, -1, 1004, 650, NULL, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( hWindow, SW_SHOW );
	SetForegroundWindow( hWindow );
	SetFocus( hWindow );
	return hWindow;
}
//------------------------------------------------------------------------
HWND						g_pHWND = NULL;
//------------------------------------------------------------------------
int main()
{
	g_pHWND = CreateGameWindow();

	FK2DEngine2::Renderer::GDIPlusBuffered* pRenderer = new FK2DEngine2::Renderer::GDIPlusBuffered( g_pHWND );

	FK2DEngine2::Skin::TexturedBase* skin = new FK2DEngine2::Skin::TexturedBase( pRenderer );
	skin->Init( "DefaultSkin.png" );

	FK2DEngine2::Controls::Canvas* pCanvas = new FK2DEngine2::Controls::Canvas( skin );
	pCanvas->SetSize( 998, 650 - 24 );
	pCanvas->SetDrawBackground( true );
	pCanvas->SetBackgroundColor( FK2DEngine2::Color( 150, 170, 170, 255 ) );

	UnitTest* pUnit = new UnitTest( pCanvas );
	pUnit->SetPos( 10, 10 );

	FK2DEngine2::Input::Windows GwenInput;
	GwenInput.Initialize( pCanvas );

	MSG msg;

	while ( true )
	{
		if ( !IsWindowVisible( g_pHWND ) )
		{ break; }

		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			GwenInput.ProcessMessage( msg );

			if ( msg.message == WM_QUIT )
			{ break; }

			if ( msg.message == WM_PAINT )
			{
				pCanvas->Redraw();
			}

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		if ( pCanvas->NeedsRedraw() )
		{
			pCanvas->RenderCanvas();
		}
	}

	delete pCanvas;
	delete skin;
	delete pRenderer;
}
//------------------------------------------------------------------------