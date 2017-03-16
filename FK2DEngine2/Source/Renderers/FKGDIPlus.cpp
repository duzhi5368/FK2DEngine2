/**
*	created:		2013-4-11   23:49
*	filename: 		FKGDIPlus
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#ifdef FK_USE_GDI
//------------------------------------------------------------------------
#include <windows.h>
#include <gdiplus.h>
//------------------------------------------------------------------------
#include "../../Include/Renderers/FKGDIPlus.h"
#include "../../Include/FKUtility.h"
#include "../../Include/FKFont.h"
#include "../../Include/FKTexture.h"
#include "../../Include/FKWindowProvider.h"
//------------------------------------------------------------------------
#include <math.h>
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Renderer
	{
		GDIPlus::GDIPlus( HWND pHWND )
		{
			m_HWND = pHWND;
			m_hDC = NULL;
			graphics = NULL;
			m_iWidth = 0;
			m_iHeight = 0;
			// ³õÊ¼»¯ GDI+.
			Gdiplus::GdiplusStartupInput gdiplusStartupInput;
			Gdiplus::GdiplusStartup( &m_gdiplusToken, &gdiplusStartupInput, NULL );
		}

		GDIPlus::~GDIPlus()
		{
			Gdiplus::GdiplusShutdown( m_gdiplusToken );
		}

		void GDIPlus::Begin()
		{
			m_hDC = GetDC( m_HWND );
			graphics = Gdiplus::Graphics::FromHDC( m_hDC );
		}

		void GDIPlus::End()
		{
			if ( graphics )
			{
				delete graphics;
				graphics = NULL;
			}

			ReleaseDC( m_HWND, m_hDC );
			m_hDC = NULL;
		}



		void GDIPlus::DrawFilledRect( FK2DEngine2::Rect rect )
		{
			Translate( rect );
			Gdiplus::SolidBrush solidBrush( m_Colour );
			graphics->FillRectangle( &solidBrush, rect.x, rect.y, rect.w, rect.h );
		}

		void GDIPlus::SetDrawColor( FK2DEngine2::Color color )
		{
			m_Colour = Gdiplus::Color( color.a, color.r, color.g, color.b );
		}

		void GDIPlus::LoadFont( FK2DEngine2::Font* font )
		{
			Gdiplus::FontStyle fs = Gdiplus::FontStyleRegular;
			font->realsize = font->size * Scale();
			Gdiplus::Font* pFont = new Gdiplus::Font( font->facename.c_str(), font->realsize, fs, Gdiplus::UnitPixel, NULL );
			font->data = pFont;
		}

		void GDIPlus::FreeFont( FK2DEngine2::Font* pFont )
		{
			if ( !pFont->data ) { return; }

			Gdiplus::Font* font = ( ( Gdiplus::Font* ) pFont->data );
			delete font;
			pFont->data = NULL;
		}

		void GDIPlus::RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::UnicodeString & text )
		{
			Translate( pos.x, pos.y );

			if ( !pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			Gdiplus::StringFormat strFormat( Gdiplus::StringFormat::GenericDefault() );
			Gdiplus::SolidBrush solidBrush( m_Colour );
			Gdiplus::RectF r( pos.x, pos.y, 1000, 1000 );
			Gdiplus::Font* pGDIFont = ( Gdiplus::Font* ) pFont->data;
			graphics->DrawString( text.c_str(), text.length() + 1, pGDIFont, r, &strFormat, &solidBrush );
		}

		FK2DEngine2::Point GDIPlus::MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::UnicodeString & text )
		{
			FK2DEngine2::Point p( 1, 1 );

			if ( !pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				FreeFont( pFont );
				LoadFont( pFont );
			}

			Gdiplus::StringFormat strFormat( Gdiplus::StringFormat::GenericDefault() );
			strFormat.SetFormatFlags( Gdiplus::StringFormatFlagsMeasureTrailingSpaces | strFormat.GetFormatFlags() );
			Gdiplus::SizeF size;
			Gdiplus::Graphics g( m_HWND );
			Gdiplus::Font* pGDIFont = ( Gdiplus::Font* ) pFont->data;
			g.MeasureString( text.c_str(), -1, pGDIFont, Gdiplus::SizeF( 10000, 10000 ), &strFormat, &size );
			return FK2DEngine2::Point( size.Width + 1, size.Height + 1 );
		}

		void GDIPlus::StartClip()
		{
			const FK2DEngine2::Rect & rect = ClipRegion();
			graphics->SetClip( Gdiplus::Rect( rect.x * Scale(), rect.y * Scale(), rect.w * Scale(), rect.h * Scale() ), Gdiplus::CombineMode::CombineModeReplace );
		}

		void GDIPlus::EndClip()
		{
			graphics->ResetClip();
		}

		void GDIPlus::DrawTexturedRect( FK2DEngine2::Texture* pTexture, FK2DEngine2::Rect pTargetRect, float u1, float v1, float u2, float v2 )
		{
			Gdiplus::Bitmap* pImage = ( Gdiplus::Bitmap* ) pTexture->data;

			if ( !pImage || pImage->GetType() == Gdiplus::ImageTypeUnknown )
			{ return DrawMissingImage( pTargetRect ); }

			Translate( pTargetRect );
			Gdiplus::RectF TargetRect( pTargetRect.x, pTargetRect.y, pTargetRect.w, pTargetRect.h );

			float fW = pImage->GetWidth();
			float fH = pImage->GetHeight();
			u1 *= fW;
			v1 *= fH;
			u2 *= fW;
			u2 -= u1;
			v2 *= fH;
			v2 -= v1;
			graphics->DrawImage( pImage, TargetRect, u1, v1, u2, v2, Gdiplus::UnitPixel );
		}

		void GDIPlus::LoadTexture( FK2DEngine2::Texture* pTexture )
		{
			Gdiplus::Bitmap* pImage = new Gdiplus::Bitmap( pTexture->name.GetUnicode().c_str() );
			pTexture->data = pImage;
			pTexture->width = pImage->GetWidth();
			pTexture->height = pImage->GetHeight();
		}

		void GDIPlus::FreeTexture( FK2DEngine2::Texture* pTexture )
		{
			Gdiplus::Bitmap* pImage = ( Gdiplus::Bitmap* ) pTexture->data;

			if ( !pImage ) { return; }

			delete pImage;
		}

		FK2DEngine2::Color GDIPlus::PixelColour( FK2DEngine2::Texture* pTexture, unsigned int x, unsigned int y, const FK2DEngine2::Color & col_default )
		{
			Gdiplus::Bitmap* pImage = ( Gdiplus::Bitmap* ) pTexture->data;

			if ( !pImage ) { return col_default; }

			Gdiplus::Color c;
			pImage->GetPixel( x, y, &c );
			return FK2DEngine2::Color( c.GetR(), c.GetG(), c.GetB(), c.GetA() );
		}


		bool GDIPlus::InitializeContext( FK2DEngine2::WindowProvider* pWindow )
		{
			m_HWND = ( HWND ) pWindow->GetWindow();
			return true;
		}

		bool GDIPlus::ShutdownContext( FK2DEngine2::WindowProvider* pWindow )
		{
			return true;
		}

		bool GDIPlus::PresentContext( FK2DEngine2::WindowProvider* pWindow )
		{
			return true;
		}

		bool GDIPlus::ResizedContext( FK2DEngine2::WindowProvider* pWindow, int w, int h )
		{
			return true;
		}

		bool GDIPlus::BeginContext( FK2DEngine2::WindowProvider* pWindow )
		{
			return true;
		}

		bool GDIPlus::EndContext( FK2DEngine2::WindowProvider* pWindow )
		{
			return true;
		}
	}
}
//------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------