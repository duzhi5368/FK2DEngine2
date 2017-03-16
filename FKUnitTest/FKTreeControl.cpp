/**
*	created:		2013-4-13   21:10
*	filename: 		FKTreeControl
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../FK2DEngine2/Include/UnitTest/FKUnitTest.h"
#include "../FK2DEngine2/Include/Controls/FKTreeControl.h"
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
class TreeControl : public GUnit
{
public:

	FK_CONTROL_INLINE( TreeControl, GUnit )
	{
		{
			FK2DEngine2::Controls::TreeControl* ctrl = new FK2DEngine2::Controls::TreeControl( this );
			ctrl->AddNode( L"Node One" );
			FK2DEngine2::Controls::TreeNode* pNode = ctrl->AddNode( L"Node Two" );
			pNode->AddNode( L"Node Two Inside" );
			pNode->AddNode( L"Eyes" );
			pNode->AddNode( L"Brown" )->AddNode( L"Node Two Inside" )->AddNode( L"Eyes" )->AddNode( L"Brown" );
			pNode->AddNode( L"More" );
			pNode->AddNode( L"Nodes" );
			ctrl->AddNode( L"Node Three" );
			ctrl->SetBounds( 30, 30, 200, 200 );
			ctrl->ExpandAll();
		}
		{
			FK2DEngine2::Controls::TreeControl* ctrl = new FK2DEngine2::Controls::TreeControl( this );
			ctrl->AllowMultiSelect( true );
			ctrl->AddNode( L"Node One" );
			FK2DEngine2::Controls::TreeNode* pNode = ctrl->AddNode( L"Node Two" );
			pNode->AddNode( L"Node Two Inside" );
			pNode->AddNode( L"Eyes" );
			FK2DEngine2::Controls::TreeNode* pNodeTwo = pNode->AddNode( L"Brown" )->AddNode( L"Node Two Inside" )->AddNode( L"Eyes" );
			pNodeTwo->AddNode( L"Brown" );
			pNodeTwo->AddNode( L"Green" );
			pNodeTwo->AddNode( L"Slime" );
			pNodeTwo->AddNode( L"Grass" );
			pNodeTwo->AddNode( L"Pipe" );
			pNode->AddNode( L"More" );
			pNode->AddNode( L"Nodes" );
			ctrl->AddNode( L"Node Three" );
			ctrl->SetBounds( 240, 30, 200, 200 );
			ctrl->ExpandAll();
		}
	}

};
//------------------------------------------------------------------------
DEFINE_UNIT_TEST( TreeControl, L"TreeControl" );
//------------------------------------------------------------------------