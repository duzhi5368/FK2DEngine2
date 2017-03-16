/**
*	created:		2013-4-12   16:17
*	filename: 		FKDockBase
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../FK2DEngine2.h"
#include "../../Include/FKSkin.h"
#include "../../Include/Controls/FKDockBase.h"
#include "../../Include/Controls/FKDockedTabControl.h"
#include "../../Include/Controls/FKHighlight.h"
#include "../../Include/FKDragAndDrop.h"
#include "../../Include/Controls/FKResizer.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
using namespace FK2DEngine2::Controls;
//------------------------------------------------------------------------
FK_CONTROL_CONSTRUCTOR( DockBase )
{
	SetPadding( Padding( 1, 1, 1, 1 ) );
	SetSize( 200, 200 );
	m_DockedTabControl = NULL;
	m_Left = NULL;
	m_Right = NULL;
	m_Top = NULL;
	m_Bottom = NULL;
	m_bDrawHover = false;
}

TabControl* DockBase::GetTabControl()
{
	return m_DockedTabControl;
}

void DockBase::SetupChildDock( int iPos )
{
	if ( !m_DockedTabControl )
	{
		m_DockedTabControl = new DockedTabControl( this );
		m_DockedTabControl->onLoseTab.Add( this, &DockBase::OnTabRemoved );
		m_DockedTabControl->SetTabStripPosition( Pos::Bottom );
		m_DockedTabControl->SetShowTitlebar( true );
	}

	Dock( iPos );
	int iSizeDirection = Pos::Left;

	if ( iPos == Pos::Left ) { iSizeDirection = Pos::Right; }

	if ( iPos == Pos::Top ) { iSizeDirection = Pos::Bottom; }

	if ( iPos == Pos::Bottom ) { iSizeDirection = Pos::Top; }

	ControlsInternal::Resizer* sizer = new ControlsInternal::Resizer( this );
	sizer->Dock( iSizeDirection );
	sizer->SetResizeDir( iSizeDirection );
	sizer->SetSize( 2, 2 );
	sizer->SetTarget( this );
}

void DockBase::Render( Skin::Base* /*skin*/ )
{
	// FK2DEngine2::Render->SetDrawColor( Colors::Black );
	// FK2DEngine2::Render->DrawLinedRect( GetRenderBounds() );
}

DockBase** DockBase::GetChildDockPtr( int iPos )
{
	if ( iPos == Pos::Left ) { return &m_Left; }

	if ( iPos == Pos::Right ) { return &m_Right; }

	if ( iPos == Pos::Top ) { return &m_Top; }

	if ( iPos == Pos::Bottom ) { return &m_Bottom; }

	return NULL;
}

DockBase* DockBase::GetChildDock( int iPos )
{
	DockBase** pDock = GetChildDockPtr( iPos );

	if ( !( *pDock ) )
	{
		( *pDock ) = new DockBase( this );
		( *pDock )->SetupChildDock( iPos );
	}
	else
	{
		( *pDock )->SetHidden( false );
	}

	return *pDock;
}

int DockBase::GetDroppedTabDirection( int x, int y )
{
	int w = Width();
	int h = Height();
	float top = ( float ) y / ( float ) h;
	float left = ( float ) x / ( float ) w;
	float right = ( float )( w - x ) / ( float ) w;
	float bottom = ( float )( h - y ) / ( float ) h;
	float minimum = FK2DEngine2::Min( FK2DEngine2::Min( FK2DEngine2::Min( top, left ), right ), bottom );
	m_bDropFar = ( minimum < 0.2f );

	if ( minimum > 0.3 ) { return Pos::Fill; }

	if ( top == minimum && ( !m_Top || m_Top->Hidden() ) ) { return Pos::Top; }

	if ( left == minimum && ( !m_Left || m_Left->Hidden() ) ) { return Pos::Left; }

	if ( right == minimum && ( !m_Right || m_Right->Hidden() ) ) { return Pos::Right; }

	if ( bottom == minimum && ( !m_Bottom || m_Bottom->Hidden() ) ) { return Pos::Bottom; }

	return Pos::Fill;
}

bool DockBase::DragAndDrop_CanAcceptPackage( FK2DEngine2::DragAndDrop::Package* pPackage )
{
	if ( pPackage->name == "TabButtonMove" )
	{ return true; }

	if ( pPackage->name == "TabWindowMove" )
	{ return true; }

	return false;
}

bool DockBase::DragAndDrop_HandleDrop( FK2DEngine2::DragAndDrop::Package* pPackage, int x, int y )
{
	FK2DEngine2::Point pPos = CanvasPosToLocal( FK2DEngine2::Point( x, y ) );
	int dir = GetDroppedTabDirection( pPos.x, pPos.y );
	DockedTabControl* pAddTo = m_DockedTabControl;

	if ( dir == Pos::Fill && pAddTo == NULL ) { return false; }

	if ( dir != Pos::Fill )
	{
		DockBase* pDock = GetChildDock( dir );
		pAddTo = pDock->m_DockedTabControl;

		if ( !m_bDropFar ) { pDock->BringToFront(); }
		else { pDock->SendToBack(); }
	}

	if ( pPackage->name == "TabButtonMove" )
	{
		TabButton* pTabButton = fk_cast<TabButton> ( DragAndDrop::SourceControl );

		if ( !pTabButton ) { return false; }

		pAddTo->AddPage( pTabButton );
	}

	if ( pPackage->name == "TabWindowMove" )
	{
		DockedTabControl* pTabControl = fk_cast<DockedTabControl> ( DragAndDrop::SourceControl );

		if ( !pTabControl ) { return false; }

		if ( pTabControl == pAddTo ) { return false; }

		pTabControl->MoveTabsTo( pAddTo );
	}

	Invalidate();
	return true;
}

bool DockBase::IsEmpty()
{
	if ( m_DockedTabControl && m_DockedTabControl->TabCount() > 0 ) { return false; }

	if ( m_Left && !m_Left->IsEmpty() ) { return false; }

	if ( m_Right && !m_Right->IsEmpty() ) { return false; }

	if ( m_Top && !m_Top->IsEmpty() ) { return false; }

	if ( m_Bottom && !m_Bottom->IsEmpty() ) { return false; }

	return true;
}

void DockBase::OnTabRemoved( FK2DEngine2::Controls::Base* /*pControl*/ )
{
	DoRedundancyCheck();
	DoConsolidateCheck();
}

void DockBase::DoRedundancyCheck()
{
	if ( !IsEmpty() ) { return; }

	DockBase* pDockParent = fk_cast<DockBase> ( GetParent() );

	if ( !pDockParent ) { return; }

	pDockParent->OnRedundantChildDock( this );
}

void DockBase::DoConsolidateCheck()
{
	if ( IsEmpty() ) { return; }

	if ( !m_DockedTabControl ) { return; }

	if ( m_DockedTabControl->TabCount() > 0 ) { return; }

	if ( m_Bottom && !m_Bottom->IsEmpty() )
	{
		m_Bottom->m_DockedTabControl->MoveTabsTo( m_DockedTabControl );
		return;
	}

	if ( m_Top && !m_Top->IsEmpty() )
	{
		m_Top->m_DockedTabControl->MoveTabsTo( m_DockedTabControl );
		return;
	}

	if ( m_Left && !m_Left->IsEmpty() )
	{
		m_Left->m_DockedTabControl->MoveTabsTo( m_DockedTabControl );
		return;
	}

	if ( m_Right && !m_Right->IsEmpty() )
	{
		m_Right->m_DockedTabControl->MoveTabsTo( m_DockedTabControl );
		return;
	}
}

void DockBase::OnRedundantChildDock( DockBase* pDockBase )
{
	pDockBase->SetHidden( true );
	DoRedundancyCheck();
	DoConsolidateCheck();
}

void DockBase::DragAndDrop_HoverEnter( FK2DEngine2::DragAndDrop::Package* /*pPackage*/, int /*x*/, int /*y*/ )
{
	m_bDrawHover = true;
}

void DockBase::DragAndDrop_HoverLeave( FK2DEngine2::DragAndDrop::Package* /*pPackage*/ )
{
	m_bDrawHover = false;
}

void DockBase::DragAndDrop_Hover( FK2DEngine2::DragAndDrop::Package* /*pPackage*/, int x, int y )
{
	FK2DEngine2::Point pPos = CanvasPosToLocal( FK2DEngine2::Point( x, y ) );
	int dir = GetDroppedTabDirection( pPos.x, pPos.y );

	if ( dir == Pos::Fill )
	{
		if ( !m_DockedTabControl )
		{
			m_HoverRect = FK2DEngine2::Rect( 0, 0, 0, 0 );
			return;
		}

		m_HoverRect = GetInnerBounds();
		return;
	}

	m_HoverRect = GetRenderBounds();
	int HelpBarWidth = 0;

	if ( dir == Pos::Left )
	{
		HelpBarWidth = m_HoverRect.w * 0.25f;
		m_HoverRect.w = HelpBarWidth;
	}

	if ( dir == Pos::Right )
	{
		HelpBarWidth = m_HoverRect.w * 0.25f;
		m_HoverRect.x = m_HoverRect.w - HelpBarWidth;
		m_HoverRect.w = HelpBarWidth;
	}

	if ( dir == Pos::Top )
	{
		HelpBarWidth = m_HoverRect.h * 0.25f;
		m_HoverRect.h = HelpBarWidth;
	}

	if ( dir == Pos::Bottom )
	{
		HelpBarWidth = m_HoverRect.h * 0.25f;
		m_HoverRect.y = m_HoverRect.h - HelpBarWidth;
		m_HoverRect.h = HelpBarWidth;
	}

	if ( ( dir == Pos::Top || dir == Pos::Bottom ) && !m_bDropFar )
	{
		if ( m_Left && m_Left->Visible() )
		{
			m_HoverRect.x += m_Left->Width();
			m_HoverRect.w -= m_Left->Width();
		}

		if ( m_Right && m_Right->Visible() )
		{
			m_HoverRect.w -= m_Right->Width();
		}
	}

	if ( ( dir == Pos::Left || dir == Pos::Right ) && !m_bDropFar )
	{
		if ( m_Top && m_Top->Visible() )
		{
			m_HoverRect.y += m_Top->Height();
			m_HoverRect.h -= m_Top->Height();
		}

		if ( m_Bottom && m_Bottom->Visible() )
		{
			m_HoverRect.h -= m_Bottom->Height();
		}
	}
}

void DockBase::RenderOver( Skin::Base* skin )
{
	if ( !m_bDrawHover ) { return; }

	FK2DEngine2::Renderer::Base* render = skin->GetRender();
	render->SetDrawColor( FK2DEngine2::Color( 255, 100, 255, 20 ) );
	render->DrawFilledRect( GetRenderBounds() );

	if ( m_HoverRect.w == 0 ) { return; }

	render->SetDrawColor( FK2DEngine2::Color( 255, 100, 255, 100 ) );
	render->DrawFilledRect( m_HoverRect );
	render->SetDrawColor( FK2DEngine2::Color( 255, 100, 255, 200 ) );
	render->DrawLinedRect( m_HoverRect );
}
//------------------------------------------------------------------------