/**
*	created:		2013-4-11   19:55
*	filename: 		FKBaseProperty
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "../FKBase.h"
#include "../../FK2DEngine2.h"
#include "../../FKSkin.h"
#include "../../FKUtility.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	namespace Controls
	{
		namespace Property
		{
			class FK_EXPORT Base : public FK2DEngine2::Controls::Base
			{
				public:

					FK_CONTROL_INLINE( Base, FK2DEngine2::Controls::Base )
					{
						SetHeight( 17 );
					}

					virtual TextObject GetPropertyValue() = 0;

					virtual void SetPropertyValue( const TextObject & v, bool bFireChangeEvents = false ) = 0;

					virtual bool IsEditing() = 0;

					virtual void DoChanged()
					{
						Event::Information info;
						info.String = GetPropertyValue();
						onChange.Call( this, info );
					}

					void OnPropertyValueChanged( FK2DEngine2::Controls::Base* /*control*/ )
					{
						DoChanged();
					}

					Event::Caller	onChange;
			};
		}
	}
}
//------------------------------------------------------------------------