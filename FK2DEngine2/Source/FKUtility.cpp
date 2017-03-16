/**
*	created:		2013-4-11   20:49
*	filename: 		FKUtility
*	author:			FreeKnight
*	Copyright (C): 	
*	purpose:		
*/
//------------------------------------------------------------------------
#include "../Include/FKToolTip.h"
#include "../Include/FKUtility.h"
//------------------------------------------------------------------------
#include <cstdio>
//------------------------------------------------------------------------
using namespace FK2DEngine2;
//------------------------------------------------------------------------
#ifdef _MSC_VER
	#pragma warning(disable:4267)	// ×ª»»size_tÎªint
#endif
//------------------------------------------------------------------------
#ifdef __MINGW32__
	#undef vswprintf
	#define vswprintf _vsnwprintf
#endif
//------------------------------------------------------------------------
#ifdef _MSC_VER
	#define FK_FNULL "NUL"
#else
	#define FK_FNULL "/dev/null"
#endif
//------------------------------------------------------------------------

#ifndef va_copy 
# ifdef __va_copy 
# define va_copy(DEST,SRC) __va_copy((DEST),(SRC)) 
# else 
# define va_copy(DEST, SRC) memcpy((&DEST), (&SRC), sizeof(va_list)) 
# endif 
#endif  
//------------------------------------------------------------------------
UnicodeString FK2DEngine2::Utility::Format( const wchar_t* fmt, ... )
{
	va_list s;
	int len = 0;
	
	va_start( s, fmt );
	
	{	
		FILE* fnull = fopen( FK_FNULL, "wb" );
		va_list c;
		va_copy( c, s );
		len = vfwprintf( fnull, fmt, c );
		va_end( c );
		fclose( fnull );
	} 
	
	UnicodeString strOut;
	
	if (len > 0)
	{
		strOut.resize( len + 1 );
		va_list c;
		va_copy( c, s );
		len = vswprintf( &strOut[0], strOut.size(), fmt, c );
		va_end( c );
		strOut.resize( len );
	}
	
	va_end( s );
	
	return strOut;
}
//------------------------------------------------------------------------
void FK2DEngine2::Utility::Strings::Split( const FK2DEngine2::String & str, const FK2DEngine2::String & seperator,
										  Strings::List & outbits, bool bLeave )
{
	int iOffset = 0;
	int iLength = str.length();
	int iSepLen = seperator.length();
	size_t i = str.find( seperator, 0 );

	while ( i != std::string::npos )
	{
		outbits.push_back( str.substr( iOffset, i - iOffset ) );
		iOffset = i + iSepLen;
		i = str.find( seperator, iOffset );

		if ( bLeave ) { iOffset -= iSepLen; }
	}

	outbits.push_back( str.substr( iOffset, iLength - iOffset ) );
}
//------------------------------------------------------------------------
void FK2DEngine2::Utility::Strings::Split( const FK2DEngine2::UnicodeString & str, const FK2DEngine2::UnicodeString & seperator,
										  Strings::UnicodeList & outbits, bool bLeave )
{
	int iOffset = 0;
	int iLength = str.length();
	int iSepLen = seperator.length();
	size_t i = str.find( seperator, 0 );

	while ( i != std::wstring::npos )
	{
		outbits.push_back( str.substr( iOffset, i - iOffset ) );
		iOffset = i + iSepLen;
		i = str.find( seperator, iOffset );

		if ( bLeave ) { iOffset -= iSepLen; }
	}

	outbits.push_back( str.substr( iOffset, iLength - iOffset ) );
}
//------------------------------------------------------------------------
int FK2DEngine2::Utility::Strings::To::Int( const FK2DEngine2::String & str )
{
	if ( str == "" ) { return 0; }

	return atoi( str.c_str() );
}
//------------------------------------------------------------------------
float FK2DEngine2::Utility::Strings::To::Float( const FK2DEngine2::String & str )
{
	if ( str == "" ) { return 0.0f; }

	return ( float ) atof( str.c_str() );
}
//------------------------------------------------------------------------
float FK2DEngine2::Utility::Strings::To::Float( const FK2DEngine2::UnicodeString & str )
{
	return wcstod( str.c_str(), NULL );
}
//------------------------------------------------------------------------
bool FK2DEngine2::Utility::Strings::To::Bool( const FK2DEngine2::String & str )
{
	if ( str.size() == 0 ) { return false; }

	if ( str[0] == 'T' || str[0] == 't' || str[0] == 'y' || str[0] == 'Y' ) { return true; }

	if ( str[0] == 'F' || str[0] == 'f' || str[0] == 'n' || str[0] == 'N' ) { return false; }

	if ( str[0] == '0' ) { return false; }

	return true;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Utility::Strings::To::Floats( const FK2DEngine2::String & str, float* f, size_t iCount )
{
	Strings::List lst;
	Strings::Split( str, " ", lst );

	if ( lst.size() != iCount ) { return false; }

	for ( size_t i = 0; i < iCount; i++ )
	{
		f[i] = Strings::To::Float( lst[i] );
	}

	return true;
}
//------------------------------------------------------------------------
bool FK2DEngine2::Utility::Strings::Wildcard( const TextObject & strWildcard, const TextObject & strHaystack )
{
	const UnicodeString & W = strWildcard.GetUnicode();
	const UnicodeString & H = strHaystack.GetUnicode();

	if ( strWildcard == "*" ) { return true; }

	int iPos = W.find( L"*", 0 );

	if ( iPos == UnicodeString::npos ) { return strWildcard == strHaystack; }

	if ( iPos > 0 && W.substr( 0, iPos ) != H.substr( 0, iPos ) )
	{ return false; }

	if ( iPos != W.length() - 1 )
	{
		UnicodeString strEnd = W.substr( iPos + 1, W.length() );

		if ( strEnd != H.substr( H.length() - strEnd.length(), H.length() ) )
		{ return false; }
	}

	return true;
}
//------------------------------------------------------------------------
void FK2DEngine2::Utility::Strings::ToUpper( FK2DEngine2::UnicodeString & str )
{
	transform( str.begin(), str.end(), str.begin(), towupper );
}
//------------------------------------------------------------------------
void FK2DEngine2::Utility::Strings::Strip( FK2DEngine2::UnicodeString & str, const FK2DEngine2::UnicodeString & chars )
{
	FK2DEngine2::UnicodeString Source = str;
	str = L"";

	for ( unsigned int i = 0; i < Source.length(); i++ )
	{
		if ( chars.find( Source[i] ) != FK2DEngine2::UnicodeString::npos )
		{ continue; }

		str += Source[i];
	}
}
//------------------------------------------------------------------------