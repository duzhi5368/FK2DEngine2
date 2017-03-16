/**
*	created:		2013-4-12   0:10
*	filename: 		FKDirect2D
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FK2DEngine2.h"
//------------------------------------------------------------------------
#ifdef FK_USE_D2D
//------------------------------------------------------------------------
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
//------------------------------------------------------------------------
#include "../FKBaseRender.h"
#include "../FKTexture.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Renderer
	{

		class FK_EXPORT Direct2D : public FK2DEngine2::Renderer::Base
		{
			public:

				Direct2D();
				Direct2D( ID2D1RenderTarget* pDevice, IDWriteFactory* pDWriteFactory, IWICImagingFactory* pWICFactory );
				~Direct2D();

				virtual void Begin();
				virtual void End();
				virtual void Release();

				virtual void SetDrawColor( FK2DEngine2::Color color );

				virtual void DrawFilledRect( FK2DEngine2::Rect rect );

				virtual void LoadFont( FK2DEngine2::Font* pFont );
				virtual void FreeFont( FK2DEngine2::Font* pFont );
				virtual void RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::UnicodeString & text );
				virtual FK2DEngine2::Point MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::UnicodeString & text );

				virtual void DeviceLost();
				virtual void DeviceAcquired( ID2D1RenderTarget* pRT );

				void StartClip();
				void EndClip();

				void DrawTexturedRect( FK2DEngine2::Texture* pTexture, FK2DEngine2::Rect pTargetRect, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f );
				void LoadTexture( FK2DEngine2::Texture* pTexture );
				void FreeTexture( FK2DEngine2::Texture* pTexture );
				FK2DEngine2::Color PixelColour( FK2DEngine2::Texture* pTexture, unsigned int x, unsigned int y, const FK2DEngine2::Color & col_default );

				void DrawLinedRect( FK2DEngine2::Rect rect );
				void DrawShavedCornerRect( FK2DEngine2::Rect rect, bool bSlight = false );

			public:

				bool InitializeContext( FK2DEngine2::WindowProvider* pWindow );
				bool ShutdownContext( FK2DEngine2::WindowProvider* pWindow );
				bool PresentContext( FK2DEngine2::WindowProvider* pWindow );
				bool ResizedContext( FK2DEngine2::WindowProvider* pWindow, int w, int h );
				bool BeginContext( FK2DEngine2::WindowProvider* pWindow );
				bool EndContext( FK2DEngine2::WindowProvider* pWindow );

			private:
				bool InternalCreateDeviceResources();
				void InternalReleaseDeviceResources();

				ID2D1Factory*	m_pD2DFactory;
				HWND			m_pHWND;

			private:
				bool InternalLoadTexture( FK2DEngine2::Texture* pTexture );
				bool InternalLoadFont( FK2DEngine2::Font* pFont );

				void InternalFreeFont( FK2DEngine2::Font* pFont, bool bRemove = true );
				void InternalFreeTexture( FK2DEngine2::Texture* pTexture, bool bRemove = true );

			private:

				IDWriteFactory*		m_pDWriteFactory;
				IWICImagingFactory*	m_pWICFactory;
				ID2D1RenderTarget*	m_pRT;

				ID2D1SolidColorBrush* m_pSolidColorBrush;

				D2D1::ColorF		m_Color;

				FK2DEngine2::Texture::List	m_TextureList;
				FK2DEngine2::Font::List	m_FontList;

		};

	}
}
//------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------