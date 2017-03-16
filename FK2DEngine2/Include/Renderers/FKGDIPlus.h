/**
*	created:		2013-4-11   23:44
*	filename: 		FKGDIPlus
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../../FK2DEngine2.h"
#include "../FKBaseRender.h"
//------------------------------------------------------------------------
#ifdef FK_USE_GDI
//------------------------------------------------------------------------
#include <gdiplus.h>
//------------------------------------------------------------------------
// 使用GDI方式将会很慢，因为每次都会调用 redraw 不推荐使用
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Renderer
	{
		//------------------------------------------------------------------------
		class FK_EXPORT GDIPlus : public FK2DEngine2::Renderer::Base
		{
			public:

				GDIPlus( HWND pHWND = NULL );
				~GDIPlus();

				virtual void Begin();
				virtual void End();

				virtual void SetDrawColor( FK2DEngine2::Color color );

				virtual void DrawFilledRect( FK2DEngine2::Rect rect );

				virtual void LoadFont( FK2DEngine2::Font* pFont );
				virtual void FreeFont( FK2DEngine2::Font* pFont );
				virtual void RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::UnicodeString & text );
				virtual FK2DEngine2::Point MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::UnicodeString & text );

				void StartClip();
				void EndClip();

				void DrawTexturedRect( FK2DEngine2::Texture* pTexture, FK2DEngine2::Rect pTargetRect, float u1 = 0.0f, float v1 = 0.0f, float u2 = 1.0f, float v2 = 1.0f );
				void LoadTexture( FK2DEngine2::Texture* pTexture );
				void FreeTexture( FK2DEngine2::Texture* pTexture );
				FK2DEngine2::Color PixelColour( FK2DEngine2::Texture* pTexture, unsigned int x, unsigned int y, const FK2DEngine2::Color & col_default );

			public:

				virtual bool InitializeContext( FK2DEngine2::WindowProvider* pWindow );
				virtual bool ShutdownContext( FK2DEngine2::WindowProvider* pWindow );
				virtual bool PresentContext( FK2DEngine2::WindowProvider* pWindow );
				virtual bool ResizedContext( FK2DEngine2::WindowProvider* pWindow, int w, int h );
				virtual bool BeginContext( FK2DEngine2::WindowProvider* pWindow );
				virtual bool EndContext( FK2DEngine2::WindowProvider* pWindow );

			protected:

				int m_iWidth;
				int m_iHeight;

				Gdiplus::Color	m_Colour;

				HWND			m_HWND;
				HDC				m_hDC;
				ULONG_PTR       m_gdiplusToken;

				Gdiplus::Graphics*		graphics;
		};
		//------------------------------------------------------------------------
		class GDIPlusBuffered : public GDIPlus
		{
			public:

				GDIPlusBuffered( HWND pHWND = NULL );
				~GDIPlusBuffered();

				virtual void Begin();
				virtual void End();

			private:

				void CreateBackbuffer();
				void DestroyBackbuffer();

				Gdiplus::Bitmap*			m_Bitmap;

		};
		//------------------------------------------------------------------------
	}
}
//------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------