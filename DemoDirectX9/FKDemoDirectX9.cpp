/**
*	created:		2013-4-13   0:55
*	filename: 		FKDemoDirectX9
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN 
//------------------------------------------------------------------------
#include <windows.h>
//------------------------------------------------------------------------
#include <d3d9.h>
#include <D3dx9core.h>
#include <D3dx9math.h>
#include <DxErr.h>
//------------------------------------------------------------------------
#include <stdlib.h>
#include <memory.h>
#include <tchar.h>
//------------------------------------------------------------------------
#include "../FK2DEngine2/FK2DEngine2.h"
#include "../FK2DEngine2/Include/Skins/FKSimple.h"
#include "../FK2DEngine2/Include/Skins/FKTexturedBase.h"
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Input/FKWindows.h"
#include "../FK2DEngine2/Include/Renderers/FKDirectX9.h"
//------------------------------------------------------------------------
HWND					g_pHWND = NULL;
LPDIRECT3D9				g_pD3D = NULL;
IDirect3DDevice9*		g_pD3DDevice = NULL;
D3DPRESENT_PARAMETERS	g_D3DParams;
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
	HWND hWindow = CreateWindowEx( ( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE ) , wc.lpszClassName, L"FKDirect3DSample", ( WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN ) & ~( WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME ), -1, -1, 1004, 650, NULL, NULL, GetModuleHandle( NULL ), NULL );
	ShowWindow( hWindow, SW_SHOW );
	SetForegroundWindow( hWindow );
	SetFocus( hWindow );
	return hWindow;
}
//------------------------------------------------------------------------
void ResetD3DDevice()
{
	g_pD3DDevice->Reset( &g_D3DParams );
}
//------------------------------------------------------------------------
void CreateD3DDevice()
{
	ZeroMemory( &g_D3DParams, sizeof( g_D3DParams ) );
	RECT ClientRect;
	GetClientRect( g_pHWND, &ClientRect );
	g_D3DParams.Windowed = TRUE;
	g_D3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	g_D3DParams.BackBufferWidth = ClientRect.right;
	g_D3DParams.BackBufferHeight = ClientRect.bottom;
	g_D3DParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	g_D3DParams.BackBufferFormat = D3DFMT_X8R8G8B8;
	//g_D3DParams.EnableAutoDepthStencil = TRUE;
	//g_D3DParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	g_D3DParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	HRESULT hr = g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_pHWND, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &g_D3DParams, &g_pD3DDevice );

	if ( FAILED( hr ) )
	{
		OutputDebugString( L"Couldn't create D3D Device for some reason!" );
		return;
	}
}
//------------------------------------------------------------------------
int main( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	g_pD3D = Direct3DCreate9( D3D_SDK_VERSION );
	g_pHWND = CreateGameWindow();
	CreateD3DDevice();
	RECT FrameBounds;
	GetClientRect( g_pHWND, &FrameBounds );

	FK2DEngine2::Renderer::DirectX9* pRenderer = new FK2DEngine2::Renderer::DirectX9( g_pD3DDevice );

	FK2DEngine2::Skin::TexturedBase* pSkin = new FK2DEngine2::Skin::TexturedBase( pRenderer );
	pSkin->Init( "DefaultSkin.png" );

	FK2DEngine2::Controls::Canvas* pCanvas = new FK2DEngine2::Controls::Canvas( pSkin );
	pCanvas->SetSize( FrameBounds.right, FrameBounds.bottom );
	pCanvas->SetDrawBackground( true );
	pCanvas->SetBackgroundColor( FK2DEngine2::Color( 150, 170, 170, 255 ) );

	UnitTest* pUnit = new UnitTest( pCanvas );
	pUnit->SetPos( 10, 10 );

	FK2DEngine2::Input::Windows FKInput;
	FKInput.Initialize( pCanvas );

	MSG msg;

	while ( true )
	{
		if ( !IsWindowVisible( g_pHWND ) )
		{ break; }

		if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			FKInput.ProcessMessage( msg );

			if ( msg.message == WM_QUIT )
			{ break; }

			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			g_pD3DDevice->BeginScene();
			g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1, 0 );

			pCanvas->RenderCanvas();
			g_pD3DDevice->EndScene();
			g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
		}
	}

	delete pCanvas;
	delete pSkin;
	delete pRenderer;

	if ( g_pD3DDevice )
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if ( g_pD3D )
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}
//------------------------------------------------------------------------