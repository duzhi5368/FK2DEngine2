/**
*	created:		2013-4-12   0:12
*	filename: 		FKDirect2D
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#ifdef FK_USE_D2D
//------------------------------------------------------------------------
#include <windows.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
//------------------------------------------------------------------------
#include "../../Include/Renderers/FKDirect2D.h"
#include "../../Include/FKUtility.h"
#include "../../Include/FKFont.h"
#include "../../Include/FKTexture.h"
#include "../../Include/FKWindowProvider.h"
//------------------------------------------------------------------------
struct FontData
{
	IDWriteTextFormat*	pTextFormat;
};
//------------------------------------------------------------------------
struct TextureData
{
	ID2D1Bitmap*		pBitmap; // device-specific
	IWICBitmapSource*	pWICBitmap;
};
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Renderer
	{

		Direct2D::Direct2D() : m_Color( D2D1::ColorF::White )
		{
			m_pRT				= NULL;
			m_pDWriteFactory	= NULL;
			m_pWICFactory		= NULL;
		}

		Direct2D::Direct2D( ID2D1RenderTarget* pRT, IDWriteFactory* pDWriteFactory, IWICImagingFactory* pWICFactory ) : m_Color( D2D1::ColorF::White )
		{
			DeviceAcquired( pRT );
			m_pDWriteFactory	= pDWriteFactory;
			m_pWICFactory		= pWICFactory;
		}

		Direct2D::~Direct2D()
		{
		}

		void Direct2D::Begin()
		{
		}

		void Direct2D::End()
		{
		}

		void Direct2D::DrawFilledRect( FK2DEngine2::Rect rect )
		{
			Translate( rect );

			if ( m_pSolidColorBrush )
			{
				m_pRT->FillRectangle( D2D1::RectF( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h ), m_pSolidColorBrush );
			}
		}

		void Direct2D::SetDrawColor( FK2DEngine2::Color color )
		{
			m_Color = D2D1::ColorF( color.r / 255.0f , color.g / 255.0f , color.b / 255.0f , color.a / 255.0f );
			m_pSolidColorBrush->SetColor( m_Color );
		}

		bool Direct2D::InternalLoadFont( FK2DEngine2::Font* pFont )
		{
			IDWriteTextFormat* pTextFormat = NULL;
			HRESULT hr = m_pDWriteFactory->CreateTextFormat(
				pFont->facename.c_str(),
				NULL,
				pFont->bold ? DWRITE_FONT_WEIGHT_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				pFont->size,
				L"",
				&pTextFormat
				);

			if ( SUCCEEDED( hr ) )
			{
				FontData*	pFontData = new FontData();
				pFontData->pTextFormat = pTextFormat;
				pFont->data = pFontData;
				pFont->realsize = pFont->size * Scale();
				return true;
			}

			return false;
		}

		void Direct2D::LoadFont( FK2DEngine2::Font* pFont )
		{
			if ( InternalLoadFont( pFont ) )
			{ m_FontList.push_back( pFont ); }
		}

		void Direct2D::InternalFreeFont( FK2DEngine2::Font* pFont, bool bRemove )
		{
			if ( bRemove )
			{ m_FontList.remove( pFont ); }

			if ( !pFont->data ) { return; }

			FontData* pFontData = ( FontData* ) pFont->data;
			pFontData->pTextFormat->Release();
			delete pFontData;
			pFont->data = NULL;
		}

		void Direct2D::FreeFont( FK2DEngine2::Font* pFont )
		{
			InternalFreeFont( pFont );
		}

		void Direct2D::RenderText( FK2DEngine2::Font* pFont, FK2DEngine2::Point pos, const FK2DEngine2::UnicodeString & text )
		{
			if ( !pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				InternalFreeFont( pFont, false );
				InternalLoadFont( pFont );
			}

			FontData* pFontData = ( FontData* ) pFont->data;
			Translate( pos.x, pos.y );

			if ( m_pSolidColorBrush )
			{
				m_pRT->DrawTextW( text.c_str(), text.length(), pFontData->pTextFormat, D2D1::RectF( pos.x, pos.y, pos.x + 50000, pos.y + 50000 ), m_pSolidColorBrush );
			}
		}

		FK2DEngine2::Point Direct2D::MeasureText( FK2DEngine2::Font* pFont, const FK2DEngine2::UnicodeString & text )
		{
			if ( !pFont->data || fabs( pFont->realsize - pFont->size * Scale() ) > 2 )
			{
				InternalFreeFont( pFont, false );
				InternalLoadFont( pFont );
			}

			FontData* pFontData = ( FontData* ) pFont->data;
			FK2DEngine2::Point size;
			IDWriteTextLayout* pLayout;
			DWRITE_TEXT_METRICS metrics;
			m_pDWriteFactory->CreateTextLayout( text.c_str(), text.length(), pFontData->pTextFormat, 50000, 50000, &pLayout );
			pLayout->GetMetrics( &metrics );
			pLayout->Release();
			return FK2DEngine2::Point( metrics.widthIncludingTrailingWhitespace, metrics.height );
		}

		void Direct2D::DeviceLost()
		{
			if ( m_pSolidColorBrush != NULL )
			{
				m_pSolidColorBrush->Release();
				m_pSolidColorBrush = NULL;
			}

			for ( Texture::List::const_iterator tex_it = m_TextureList.begin(); tex_it != m_TextureList.end(); ++tex_it )
			{
				InternalFreeTexture( *tex_it, false );
			}
		}

		void Direct2D::DeviceAcquired( ID2D1RenderTarget* pRT )
		{
			m_pRT = pRT;
			HRESULT hr = m_pRT->CreateSolidColorBrush( m_Color, &m_pSolidColorBrush );

			for ( Texture::List::const_iterator tex_it = m_TextureList.begin(); tex_it != m_TextureList.end(); ++tex_it )
			{
				InternalLoadTexture( *tex_it );
			}
		}

		void Direct2D::StartClip()
		{
			FK2DEngine2::Rect rect = ClipRegion();
			D2D1_RECT_F r = D2D1::RectF( rect.x * Scale(), rect.y * Scale(), ( rect.x + rect.w ) * Scale(), ( rect.y + rect.h ) * Scale() );
			m_pRT->PushAxisAlignedClip( r, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE );
		}

		void Direct2D::EndClip()
		{
			m_pRT->PopAxisAlignedClip();
		}

		void Direct2D::DrawTexturedRect( FK2DEngine2::Texture* pTexture, FK2DEngine2::Rect rect, float u1, float v1, float u2, float v2 )
		{
			TextureData* pTexData = ( TextureData* ) pTexture->data;

			if ( !pTexData || pTexData->pBitmap == NULL )
			{ return DrawMissingImage( rect ); }

			Translate( rect );
			m_pRT->DrawBitmap( pTexData->pBitmap,
				D2D1::RectF( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h ),
				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF( u1 * pTexture->width, v1 * pTexture->height, u2 * pTexture->width, v2 * pTexture->height )
				);
		}

		bool Direct2D::InternalLoadTexture( FK2DEngine2::Texture* pTexture )
		{
			IWICBitmapDecoder* pDecoder = NULL;
			IWICBitmapFrameDecode* pSource = NULL;
			IWICFormatConverter* pConverter = NULL;
			ID2D1Bitmap*			pD2DBitmap = NULL;
			HRESULT hr = m_pWICFactory->CreateDecoderFromFilename(
				pTexture->name.GetUnicode().c_str(),
				NULL,
				GENERIC_READ,
				WICDecodeMetadataCacheOnLoad,
				&pDecoder
				);

			if ( SUCCEEDED( hr ) )
			{
				hr = pDecoder->GetFrame( 0, &pSource );
			}

			if ( SUCCEEDED( hr ) )
			{
				// 将图片转换为 32bppPBGRA 格式
				// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
				hr = m_pWICFactory->CreateFormatConverter( &pConverter );
			}

			if ( SUCCEEDED( hr ) )
			{
				hr = pConverter->Initialize(
					pSource,
					GUID_WICPixelFormat32bppPBGRA,
					WICBitmapDitherTypeNone,
					NULL,
					0.f,
					WICBitmapPaletteTypeMedianCut
					);
			}

			if ( SUCCEEDED( hr ) )
			{
				hr = m_pRT->CreateBitmapFromWicBitmap(
					pConverter,
					NULL,
					&pD2DBitmap
					);
			}

			if ( SUCCEEDED( hr ) )
			{
				TextureData* texdata = new TextureData();
				texdata->pWICBitmap = pSource;
				texdata->pBitmap = pD2DBitmap;
				pTexture->data = texdata;
				D2D1_SIZE_F size = texdata->pBitmap->GetSize();
				pTexture->width = size.width;
				pTexture->height = size.height;
				pTexture->failed = false;
			}
			else
			{
				pTexture->failed = true;
			}

			if ( pDecoder != NULL )
			{ pDecoder->Release(); }

			if ( pConverter != NULL )
			{ pConverter->Release(); }

			return SUCCEEDED( hr );
		}

		void Direct2D::LoadTexture( FK2DEngine2::Texture* pTexture )
		{
			if ( InternalLoadTexture( pTexture ) )
			{ m_TextureList.push_back( pTexture ); }
		}

		void Direct2D::InternalFreeTexture( FK2DEngine2::Texture* pTexture, bool bRemove )
		{
			if ( bRemove )
			{ m_TextureList.remove( pTexture ); }

			if ( pTexture->data != NULL )
			{
				TextureData* texdata = ( TextureData* ) pTexture->data;

				if ( texdata->pWICBitmap != NULL )
				{ texdata->pWICBitmap->Release(); }

				if ( texdata->pBitmap != NULL )
				{ texdata->pBitmap->Release(); }

				delete texdata;
			}

			pTexture->data = NULL;
		}

		void Direct2D::FreeTexture( FK2DEngine2::Texture* pTexture )
		{
			InternalFreeTexture( pTexture );
		}

		FK2DEngine2::Color Direct2D::PixelColour( FK2DEngine2::Texture* pTexture, unsigned int x, unsigned int y, const FK2DEngine2::Color & col_default )
		{
			TextureData* pTexData = ( TextureData* ) pTexture->data;

			if ( !pTexData || pTexData->pBitmap == NULL )
			{ return col_default; }

			WICRect sourceRect;
			sourceRect.X = x;
			sourceRect.Y = y;
			sourceRect.Width = sourceRect.Height = 1;
			// 这些图都是 GUID_WICPixelFormat32bppPBGRA 格式
			byte pixelBuffer[4 * 1 * 1];
			pTexData->pWICBitmap->CopyPixels( &sourceRect, 4, 4 * pTexture->width * pTexture->height, pixelBuffer );
			return FK2DEngine2::Color( pixelBuffer[2], pixelBuffer[1], pixelBuffer[0], pixelBuffer[3] );
		}


		void Direct2D::DrawLinedRect( FK2DEngine2::Rect rect )
		{
			Translate( rect );

			if ( m_pSolidColorBrush )
			{
				m_pRT->DrawRectangle( D2D1::RectF( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h ), m_pSolidColorBrush );
			}
		}

		void Direct2D::DrawShavedCornerRect( FK2DEngine2::Rect rect, bool bSlight )
		{
			Translate( rect );

			if ( m_pSolidColorBrush )
			{
				m_pRT->DrawRoundedRectangle( D2D1::RoundedRect( D2D1::RectF( rect.x, rect.y, rect.x + rect.w, rect.y + rect.h ), 10.f, 10.f ), m_pSolidColorBrush );
			}
		}

		void Direct2D::Release()
		{
			Texture::List::iterator tex_it = m_TextureList.begin();

			while ( tex_it != m_TextureList.end() )
			{
				FreeTexture( *tex_it );
				tex_it = m_TextureList.begin();
			}

			Font::List::iterator it = m_FontList.begin();

			while ( it != m_FontList.end() )
			{
				FreeFont( *it );
				it = m_FontList.begin();
			}
		}


		bool Direct2D::InternalCreateDeviceResources()
		{
			HRESULT hr = S_OK;

			if ( !m_pRT )
			{
				RECT rc;
				GetClientRect( m_pHWND, &rc );
				D2D1_SIZE_U size = D2D1::SizeU(
					rc.right - rc.left,
					rc.bottom - rc.top
					);
				ID2D1HwndRenderTarget* pRT;
				// Create a Direct2D render target.
				hr = m_pD2DFactory->CreateHwndRenderTarget(
					D2D1::RenderTargetProperties(),
					D2D1::HwndRenderTargetProperties( m_pHWND, size ),
					&pRT
					);

				if ( SUCCEEDED( hr ) )
				{
					pRT->SetTextAntialiasMode( D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE );
					DeviceAcquired( pRT );
				}
			}

			return SUCCEEDED( hr );
		}

		void Direct2D::InternalReleaseDeviceResources()
		{
			if ( m_pRT != NULL )
			{
				m_pRT->Release();
				m_pRT = NULL;
			}
		}

		bool Direct2D::InitializeContext( FK2DEngine2::WindowProvider* pWindow )
		{
			m_pHWND = ( HWND ) pWindow->GetWindow();
			HRESULT hr = D2D1CreateFactory(
				D2D1_FACTORY_TYPE_SINGLE_THREADED,
				&m_pD2DFactory
				);

			if ( FAILED( hr ) )
			{ return false; }

			hr = DWriteCreateFactory(
				DWRITE_FACTORY_TYPE_SHARED,
				__uuidof( IDWriteFactory ),
				reinterpret_cast<IUnknown**>( &m_pDWriteFactory )
				);

			if ( FAILED( hr ) )
			{ return false; }

			hr = CoInitialize( NULL );

			if ( FAILED( hr ) )
			{ return false; }

			hr = CoCreateInstance(
				CLSID_WICImagingFactory,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_IWICImagingFactory,
				reinterpret_cast<void**>( &m_pWICFactory )
				);

			if ( FAILED( hr ) )
			{ return false; }

			return InternalCreateDeviceResources();
		}

		bool Direct2D::ShutdownContext( FK2DEngine2::WindowProvider* pWindow )
		{
			InternalReleaseDeviceResources();
			DeviceLost();
			return true;
		}

		bool Direct2D::PresentContext( FK2DEngine2::WindowProvider* pWindow )
		{
			return true;
		}

		bool Direct2D::ResizedContext( FK2DEngine2::WindowProvider* pWindow, int w, int h )
		{
			HRESULT hr = ( ( ID2D1HwndRenderTarget* ) m_pRT )->Resize( D2D1::SizeU( w, h ) );
			return SUCCEEDED( hr );
		}

		bool Direct2D::BeginContext( FK2DEngine2::WindowProvider* pWindow )
		{
			if ( SUCCEEDED( InternalCreateDeviceResources() ) )
			{
				m_pRT->BeginDraw();
				return true;
			}

			return false;
		}

		bool Direct2D::EndContext( FK2DEngine2::WindowProvider* pWindow )
		{
			HRESULT hr = m_pRT->EndDraw();

			if ( hr == D2DERR_RECREATE_TARGET )
			{
				InternalReleaseDeviceResources();
				DeviceLost();
			}

			return SUCCEEDED( hr );
		}
	}
}
//------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------