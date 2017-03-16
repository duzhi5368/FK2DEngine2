/**
*	created:		2013-4-11   22:25
*	filename: 		FKTexture
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <string>
//------------------------------------------------------------------------
#include "FKBaseRender.h"
#include "FKTextObject.h"
#include "../FK2DEngine2.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	struct Texture
	{
		typedef std::list<Texture*>		List;

		TextObject	name;
		void*	data;
		bool	failed;
		int		width;
		int		height;

		Texture()
		{
			data = NULL;
			width = 4;
			height = 4;
			failed = false;
		}

		~Texture()
		{
		}

		void Load( const TextObject & str, FK2DEngine2::Renderer::Base* render )
		{
			name = str;
			FK2DEngine2::Debug::AssertCheck( render != NULL, "No renderer!" );
			render->LoadTexture( this );
		}

		void Release( FK2DEngine2::Renderer::Base* render )
		{
			render->FreeTexture( this );
		}

		bool FailedToLoad() const
		{
			return failed;
		}
	};

}
//------------------------------------------------------------------------