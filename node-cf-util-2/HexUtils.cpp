// #include "stdafx.h"

#include "HexUtils.h"

#define HEX_ENC_BASE(ch)		((BYTE)((ch)<10? '0': 'A'-10))
#define HEX_DEC_BASE(ch)		((BYTE)((ch)<'A'? '0': 'A'- 10))
#define HEX_ENC_BASE_LC(ch)		((BYTE)((ch)<10? '0': 'a'-10))
#define HEX_DEC_BASE_LC(ch)		((BYTE)((ch)<'a'? '0': 'a'- 10))


void HexEncode(char *hex, const BYTE *ascii, unsigned ascii_len)
{
	BYTE ch, ch4;
	for (unsigned i=0; i < ascii_len; ++i) {
		ch = ascii[i];
		
		ch4 = (BYTE)(ch >> 4);
		*hex++ = (BYTE)(ch4 + HEX_ENC_BASE(ch4));

		ch4 = (BYTE)(((BYTE)(ch << 4)) >> 4);
		*hex++ = (BYTE)(ch4 + HEX_ENC_BASE(ch4));
	}
		
}

void HexDecode(BYTE *ascii, const char *hex, unsigned ascii_len)
{
	BYTE ch, ch4_1, ch4_2;
	for (unsigned i=0; i < ascii_len; ++i) {
		ch	= *hex++;
		ch4_1 = (BYTE)(ch - HEX_DEC_BASE(ch));

		ch = *hex++;
		ch4_2 = (BYTE)(ch - HEX_DEC_BASE(ch));

		ascii[i] = (BYTE)(((BYTE)(ch4_1 << 4)) | ch4_2);
	}
}

void HexEncodeLC(char *hex, const BYTE *ascii, unsigned ascii_len)
{
	BYTE ch, ch4;
	for (unsigned i=0; i < ascii_len; ++i) {
		ch = ascii[i];
		
		ch4 = (BYTE)(ch >> 4);
		*hex++ = (BYTE)(ch4 + HEX_ENC_BASE_LC(ch4));

		ch4 = (BYTE)(((BYTE)(ch << 4)) >> 4);
		*hex++ = (BYTE)(ch4 + HEX_ENC_BASE_LC(ch4));
	}
		
}

void HexDecodeLC(BYTE *ascii, const char *hex, unsigned ascii_len)
{
	BYTE ch, ch4_1, ch4_2;
	for (unsigned i=0; i < ascii_len; ++i) {
		ch	= *hex++;
		ch4_1 = (BYTE)(ch - HEX_DEC_BASE_LC(ch));

		ch = *hex++;
		ch4_2 = (BYTE)(ch - HEX_DEC_BASE_LC(ch));

		ascii[i] = (BYTE)(((BYTE)(ch4_1 << 4)) | ch4_2);
	}
}

/* Encode/decode tables from RFC 1113 */

#define BPAD		'='		/* Padding for odd-sized output */
#define BERR		0xFF	/* Illegal char marker */
#define BEOF		0x7F	/* EOF marker (padding char or EOL) */

static const char binToAscii[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const BYTE asciiToBin[ 256 ] =
	{ BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BEOF, BERR, BERR, BEOF, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, 0x3E, BERR, BERR, BERR, 0x3F,
	  0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
	  0x3C, 0x3D, BERR, BERR, BERR, BEOF, BERR, BERR,
	  BERR, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
	  0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
	  0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
	  0x17, 0x18, 0x19, BERR, BERR, BERR, BERR, BERR,
	  BERR, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
	  0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
	  0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
	  0x31, 0x32, 0x33, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR,
	  BERR, BERR, BERR, BERR, BERR, BERR, BERR, BERR
	};

/* Basic single-char en/decode functions.  We cast the value to an unsigned
   char to avoid generating negative array offsets if the sign bit is set,
   since the strings are passed as char *'s */

#define encode(data)	binToAscii[ ( BYTE ) data ]
#define decode(data)	asciiToBin[ ( BYTE ) data ]


/* Encode a block of binary data into the base64 format, returning the total
number of output bytes */

int Base64encode( char *outBuffer, const void *inBuffer, const int count)
{
	BYTE *inBufferPtr = ( BYTE * ) inBuffer;
	int srcIndex = 0, destIndex = 0, lineCount = 0, remainder = count % 3;
	
	/* Encode the data */
	while (srcIndex < count)
	{
		lineCount += 3;
		
		/* Encode a block of data from the input buffer */
		outBuffer[ destIndex++ ] = encode( inBufferPtr[ srcIndex ] >> 2 );
		BYTE a = 0, b = 0;
		a = ( ( inBufferPtr[ srcIndex ] << 4 ) & 0x30 );
		if ((srcIndex + 1) < count)
			b = ( ( inBufferPtr[ srcIndex + 1 ] >> 4 ) & 0x0F );
		outBuffer[ destIndex++ ] = encode( a | b );
		srcIndex++;
		a = 0;
		b = 0;
		if (srcIndex < count)
			a = ( ( inBufferPtr[ srcIndex ] << 2 ) & 0x3C );
		if ((srcIndex + 1) < count)
			b = ( ( inBufferPtr[ srcIndex + 1 ] >> 6 ) & 0x03 );
		outBuffer[ destIndex++ ] = encode( a | b );
		srcIndex++;
		a = 0;
		if (srcIndex < count)
			a = inBufferPtr[ srcIndex++ ] & 0x3F;
		outBuffer[ destIndex++ ] = encode( a );
	}
	
	/* Go back and add padding and correctly encode the last char if we've
	   encoded too many characters */
	if( remainder == 2 )
	{
		/* There were only 2 bytes in the last group */
		outBuffer[ destIndex - 1 ] = BPAD;
	}
	else if( remainder == 1 )
	{
		/* There was only 1 byte in the last group */
		outBuffer[ destIndex - 2 ] = outBuffer[ destIndex - 1 ] = BPAD;
	}

	{
		/* It's not a certificate, truncate the unnecessary padding and add
		der terminador */
		destIndex -= ( 3 - remainder ) % 3;
		outBuffer[ destIndex ] = '\0';
	}

	/* Return a count of encoded bytes */
	return destIndex;
}

int Base64decode( void *outBuffer, const char *inBuffer, const int count)
{
	int srcIndex = 0, destIndex = 0;
	BYTE *outBufferPtr = (BYTE *)outBuffer;

	/* Decode the base64 string as a fixed-length continuous string without
	padding or newlines */
	while( srcIndex < count )
	{
		BYTE c0, c1, c2 = 0, c3 = 0;
		const int delta = count - srcIndex;

		/* Decode a block of data from the input buffer */
		c0 = decode( inBuffer[ srcIndex++ ] );
		c1 = decode( inBuffer[ srcIndex++ ] );
		if( delta > 2 )
		{
			c2 = decode( inBuffer[ srcIndex++ ] );
			if( delta > 3 )
				c3 = decode( inBuffer[ srcIndex++ ] );
		}
		if( ( c0 | c1 | c2 | c3 ) == BERR )
			return( 0 );

		/* Copy the decoded data to the output buffer */
		outBufferPtr[ destIndex++ ] = ( c0 << 2 ) | ( c1 >> 4 );
		if( delta > 2 )
		{
			outBufferPtr[ destIndex++ ] = ( c1 << 4 ) | ( c2 >> 2);
			if( delta > 3 )
				outBufferPtr[ destIndex++ ] = ( c2 << 6 ) | ( c3 );
		}
	}

	/* Return count of decoded bytes */
	return( destIndex );
}


// A better bas64 decoder
/* aaaack but it's fast and const should make it shared text page. */
static const unsigned char pr2six[256] =
{
	/* ASCII table */
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
	64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
	64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

int goodBase64decode_len(const char *bufcoded)
{
	int nbytesdecoded;
	register const unsigned char *bufin;
	register int nprbytes;

	bufin = (const unsigned char *) bufcoded;
	while (pr2six[*(bufin++)] <= 63);

	nprbytes = (bufin - (const unsigned char *) bufcoded) - 1;
	nbytesdecoded = ((nprbytes + 3) / 4) * 3;

	return nbytesdecoded + 1;
}

int goodBase64decode(char *bufplain, const char *bufcoded)
{
	int nbytesdecoded;
	register const unsigned char *bufin;
	register unsigned char *bufout;
	register int nprbytes;

	bufin = (const unsigned char *) bufcoded;
	while (pr2six[*(bufin++)] <= 63);
	nprbytes = (bufin - (const unsigned char *) bufcoded) - 1;
	nbytesdecoded = ((nprbytes + 3) / 4) * 3;

	bufout = (unsigned char *) bufplain;
	bufin = (const unsigned char *) bufcoded;

	while (nprbytes > 4) {
	*(bufout++) =
		(unsigned char) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
	*(bufout++) =
		(unsigned char) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
	*(bufout++) =
		(unsigned char) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
	bufin += 4;
	nprbytes -= 4;
	}

	/* Note: (nprbytes == 1) would be an error, so just ingore that case */
	if (nprbytes > 1) {
	*(bufout++) =
		(unsigned char) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
	}
	if (nprbytes > 2) {
	*(bufout++) =
		(unsigned char) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
	}
	if (nprbytes > 3) {
	*(bufout++) =
		(unsigned char) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
	}

	*(bufout++) = '\0';
	nbytesdecoded -= (4 - nprbytes) & 3;
	return nbytesdecoded;
}