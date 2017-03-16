/**
*	created:		2013-4-12   18:02
*	filename: 		FKPropertyTree
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../../FK2DEngine2.h"
#include "../../Include/Controls/FKPropertyTree.h"
#include "../../Include/FKSkin.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{

		Properties* PropertyTree::Add( const TextObject & text )
		{
			TreeNode* node = new PropertyTreeNode( this );
			node->SetText( text );
			node->Dock( Pos::Top );
			Properties* props = new Properties( node );
			props->Dock( Pos::Top );
			return props;
		}

		Properties* PropertyTree::Find( const TextObject & text )
		{
			Controls::Base::List & children = GetChildNodes();

			for ( Base::List::iterator iter = children.begin(); iter != children.end(); ++iter )
			{
				PropertyTreeNode* pChild = fk_cast<PropertyTreeNode> ( *iter );

				if ( !pChild ) { continue; }

				if ( pChild->GetText() == text )
				{
					Base::List & nodechildren = pChild->GetChildren();

					for ( Base::List::iterator iter = nodechildren.begin(); iter != nodechildren.end(); ++iter )
					{
						Properties* pPropertyChild = fk_cast<Properties> ( *iter );

						if ( !pPropertyChild ) { continue; }

						return pPropertyChild;
					}
				}
			}

			return NULL;
		}
	}
}
//------------------------------------------------------------------------