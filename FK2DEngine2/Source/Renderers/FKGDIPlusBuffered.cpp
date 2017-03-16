/**
*	created:		2013-4-13   23:40
*	filename: 		FKGDIPlusBuffered
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
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Renderer
	{
		GDIPlusBuffered::GDIPlusBuffered( HWND pHWND ) : GDIPlus( pHWND )
		{
			m_Bitmap = NULL;
		}

		GDIPlusBuffered::~GDIPlusBuffered()
		{
			DestroyBackbuffer();
		}

		void GDIPlusBuffered::CreateBackbuffer()
		{
			{
				RECT rect;
				GetClientRect( m_HWND, &rect );
				int width = rect.right - rect.left;
				int height = rect.bottom - rect.top;

				if ( m_iWidth != width ) { DestroyBackbuffer(); }

				if ( m_iHeight != height ) { DestroyBackbuffer(); }

				m_iWidth = width;
				m_iHeight = height;
			}

			if ( m_Bitmap ) { return; }

			Gdiplus::Graphics gfx( m_hDC );
			m_Bitmap = new Gdiplus::Bitmap( m_iWidth, m_iHeight, &gfx );
			graphics = Gdiplus::Graphics::FromImage( m_Bitmap );
		}

		void GDIPlusBuffered::DestroyBackbuffer()
		{
			if ( m_Bitmap )
			{
				delete m_Bitmap;
				m_Bitmap = NULL;
			}

			if ( graphics )
			{
				delete graphics;
				graphics = NULL;
			}
		}

		void GDIPlusBuffered::Begin()
		{
			m_hDC = GetDC( m_HWND );
			CreateBackbuffer();
		}

		void GDIPlusBuffered::End()
		{
			Gdiplus::Graphics gfx( m_hDC );
			gfx.DrawImage( m_Bitmap, 0, 0 );
			ReleaseDC( m_HWND, m_hDC );
			m_hDC = NULL;
		}
	}
}
//------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------