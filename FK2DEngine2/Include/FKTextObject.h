/**
*	created:		2013-4-11   17:28
*	filename: 		FKTextObject
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include "FKUtility.h"
//------------------------------------------------------------------------
namespace FK2DEngine2
{
	class TextObject
	{
		public:

			TextObject() {}

			TextObject( const FK2DEngine2::String & text )
			{
				m_String = text;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			TextObject( const char* text )
			{
				m_String = text;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			TextObject( const wchar_t* text )
			{
				m_Unicode = text;
				m_String = FK2DEngine2::Utility::UnicodeToString( m_Unicode );
			}

			TextObject( const FK2DEngine2::UnicodeString & unicode )
			{
				*this = unicode;
			}

			operator const FK2DEngine2::String & () { return m_String; }
			operator const FK2DEngine2::UnicodeString & () { return m_Unicode; }

			void operator = ( const char* str )
			{
				m_String = str;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			void operator = ( const FK2DEngine2::String & str )
			{
				m_String = str;
				m_Unicode = FK2DEngine2::Utility::StringToUnicode( m_String );
			}

			void operator = ( const FK2DEngine2::UnicodeString & unicodeStr )
			{
				m_Unicode = unicodeStr;
				m_String = FK2DEngine2::Utility::UnicodeToString( m_Unicode );
			}

			bool operator == ( const TextObject & to ) const
			{
				return m_Unicode == to.m_Unicode;
			}

			const FK2DEngine2::String & Get() const
			{
				return m_String;
			}

			const char* c_str() const
			{
				return m_String.c_str();
			}

			const FK2DEngine2::UnicodeString & GetUnicode() const
			{
				return m_Unicode;
			}

			int length() const { return m_Unicode.length(); }

			FK2DEngine2::UnicodeString		m_Unicode;
			FK2DEngine2::String				m_String;
	};
}
//------------------------------------------------------------------------