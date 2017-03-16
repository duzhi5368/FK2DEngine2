/**
*	created:		2013-4-12   22:29
*	filename: 		FKWindowCanvas
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKBase.h"
#include "../FKInputHandler.h"
#include "../FKWindowProvider.h"
#include "FKDragger.h"
#include "FKLabel.h"
#include "FKWindowButtons.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		class FK_EXPORT WindowCanvas : public Canvas, public FK2DEngine2::WindowProvider
		{
			public:

				FK_CLASS( WindowCanvas, Controls::Canvas );

				WindowCanvas( int x, int y, int w, int h, FK2DEngine2::Skin::Base* pRenderer, const FK2DEngine2::String & strWindowTitle = "" );
				~WindowCanvas();

				virtual void DoThink();

				virtual bool WantsQuit() { return m_bQuit; }

				virtual void* GetWindow();

				virtual bool InputQuit();

				Skin::Base* GetSkin( void );

				virtual void Render( Skin::Base* skin );

				virtual void SetPos( int x, int y );
				virtual bool IsOnTop();

				virtual void Layout( Skin::Base* skin );

				virtual bool CanMaximize() { return m_bCanMaximize; }
				virtual void SetCanMaximize( bool b );
				virtual void SetMaximize( bool b );

				virtual void SetSizable( bool b ) { m_Sizer->SetHidden( !b ); }
				virtual bool GetSizable() { return m_Sizer->Visible(); }

			protected:

				virtual void RenderCanvas();
				virtual void DestroyWindow();

				virtual void CloseButtonPressed();
				virtual void MaximizeButtonPressed();
				virtual void MinimizeButtonPressed();

				virtual void Dragger_Start();
				virtual void Dragger_Moved();
				virtual void Sizer_Moved();
				virtual void OnTitleDoubleClicked();

				void*		m_pOSWindow;
				bool		m_bQuit;

				FK2DEngine2::Skin::Base*			m_pSkinChange;

				ControlsInternal::Dragger*	m_TitleBar;
				ControlsInternal::Dragger*	m_Sizer;
				FK2DEngine2::Controls::Label*		m_Title;


				FK2DEngine2::Point		m_WindowPos;
				FK2DEngine2::Point		m_HoldPos;

				bool			m_bCanMaximize;
				bool			m_bIsMaximized;

				FK2DEngine2::Controls::WindowCloseButton*		m_pClose;
				FK2DEngine2::Controls::WindowMaximizeButton*	m_pMaximize;
				FK2DEngine2::Controls::WindowMinimizeButton*	m_pMinimize;

		};
	}
}
//------------------------------------------------------------------------