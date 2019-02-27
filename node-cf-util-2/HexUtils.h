#ifndef _HEX_UTILS_H
#define _HEX_UTILS_H

// -----------------------------------------------------------------
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define STRICT 1
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
// -----------------------------------------------------------------

#include <windows.h>
// #include <windef.h>

void	HexEncode(char *hex, const BYTE *ascii, unsigned ascii_len);
void	HexDecode(BYTE *ascii, const char *hex, unsigned ascii_len);
void	HexEncodeLC(char *hex, const BYTE *ascii, unsigned ascii_len);			// Lower case versions of above
void	HexDecodeLC(BYTE *ascii, const char *hex, unsigned ascii_len);


int		Base64encode( char *outBuffer, const void *inBuffer, const int count);
int		Base64decode( void *outBuffer, const char *inBuffer, const int count);

int goodBase64decode_len(const char *bufcoded);
int goodBase64decode(char *bufplain, const char *bufcoded);

#endif
