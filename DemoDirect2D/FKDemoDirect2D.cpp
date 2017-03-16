/**
*	created:		2013-4-13   1:14
*	filename: 		FKDemoDirect2D
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
//------------------------------------------------------------------------
#include <windows.h>
//------------------------------------------------------------------------
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
//------------------------------------------------------------------------
#include "../FK2DEngine2/FK2DEngine2.h"
#include "../FK2DEngine2/Include/Skins/FKSimple.h"
#include "../FK2DEngine2/Include/Skins/FKTexturedBase.h"
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Input/FKWindows.h"
#include "../FK2DEngine2/Include/Renderers/FKDirect2D.h"
//------------------------------------------------------------------------
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")
//------------------------------------------------------------------------
HWND					g_pHWND = NULL;
ID2D1Factory*			g_pD2DFactory = NULL;
IDWriteFactory*			g_pDWriteFactory = NULL;
IWICImagingFactory*		g_pWICFactory = NULL;
ID2D1HwndRenderTarget*	g_pRT = NULL;
//------------------------------------------------------------------------
FK2DEngine2::Renderer::Direct2D* g_pRenderer = NULL;
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
	HWND hWindow = CreateWindowEx( ( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE ) , wc.lpszClassName, L"FKDirect2DSample", ( WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN ) & ~( WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME ), -1, -1, 1004, 650, NULL, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( hWindow, SW_SHOW );
	SetForegroundWindow( hWindow );
	SetFocus( hWindow );
	return hWindow;
}
//------------------------------------------------------------------------
HRESULT createDeviceResources();
void discardDeviceResources();
void runSample();
//------------------------------------------------------------------------
int main( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	HRESULT hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&g_pD2DFactory
		);
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof( IDWriteFactory ),
		reinterpret_cast<IUnknown**>( &g_pDWriteFactory )
		);
	hr = CoInitialize( NULL );
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		reinterpret_cast<void**>( &g_pWICFactory )
		);
	g_pHWND = CreateGameWindow();
	createDeviceResources();

	g_pRenderer = new FK2DEngine2::Renderer::Direct2D( g_pRT, g_pDWriteFactory, g_pWICFactory );
	runSample();
	delete g_pRenderer;
	g_pRenderer = NULL;

	if ( g_pRT != NULL )
	{
		g_pRT->Release();
		g_pRT = NULL;
	}
}
//------------------------------------------------------------------------
HRESULT createDeviceResources()
{
	HRESULT hr = S_OK;

	if ( !g_pRT )
	{
		RECT rc;
		GetClientRect( g_pHWND, &rc );
		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);

		hr = g_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties( g_pHWND, size ),
			&g_pRT
			);

		if ( SUCCEEDED( hr ) && g_pRenderer != NULL )
		{
			g_pRT->SetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE );
			g_pRenderer->DeviceAcquired( g_pRT );
		}
	}

	return hr;
}
//------------------------------------------------------------------------
void discardDeviceResources()
{
	if ( g_pRT != NULL )
	{
		g_pRT->Release();
		g_pRT = NULL;
	}
}
//------------------------------------------------------------------------
void runSample()
{
	RECT FrameBounds;
	GetClientRect( g_pHWND, &FrameBounds );

	FK2DEngine2::Skin::TexturedBase skin( g_pRenderer );
	skin.Init( "DefaultSkin.png" );

	FK2DEngine2::Controls::Canvas* pCanvas = new FK2DEngine2::Controls::Canvas( &skin );
	pCanvas->SetSize( FrameBounds.right, FrameBounds.bottom );
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

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		{
			if ( SUCCEEDED( createDeviceResources() ) )
			{
				g_pRT->BeginDraw();
				g_pRT->SetTransform( D2D1::Matrix3x2F::Identity() );
				g_pRT->Clear( D2D1::ColorF( D2D1::ColorF::White ) );

				pCanvas->RenderCanvas();
				HRESULT hr = g_pRT->EndDraw();

				if ( hr == D2DERR_RECREATE_TARGET )
				{
					discardDeviceResources();
					g_pRenderer->DeviceLost();
				}
			}
		}
	}

	delete pCanvas;
}
//------------------------------------------------------------------------