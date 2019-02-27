#include <napi.h>
/*
 * dbs_cc_crypt.cpp
 *
 */

extern "C"
{
#include "Cryptlib.h"
}
// #include "stdafx.h"

#include "HexUtils.h"
/*
#include "../core/core.h"
#include "../core/sock.h"
#include "../crypto/crypt-main.h"


#include "dbs_main.h"
#include "dbs_cc_crypt.h"
#include "msg.h"
#include "client.h"
#include "client_crypt.h"
#include "HexUtils.h"				// Encode / Decode
#include <math.h>
*/

// #include "../core/log.h"

#define CRYPT_OP_BUFFER_LEN		24

#define Salt 0xCAFECAFE

// --------------------------------------------------------------------------------------------------------------------
// Logging
// --------------------------------------------------------------------------------------------------------------------
static inline void b_log_notice(const char *format, ...)
{
    // if (B_LOG_NOTICE >= _b_log_level) {
    //     va_list args;

    //     va_start(args, format);
    //     b_logv(B_LOG_NOTICE, format, args);
    //     va_end(args);
    // }
}
// --------------------------------------------------------------------------------------------------------------------



bool StartCCrypter(void)
{
	int status = cryptInit();
	if (cryptStatusError( status ))
		return false;

	CRYPT_QUERY_INFO cryptQueryInfo;
	status = cryptQueryCapability( CRYPT_ALGO_3DES, &cryptQueryInfo );
	if (cryptStatusOK(status))
	{
		b_log_notice("cryptQueryCapability (3DES) ok");
	}
	else
	{
		b_log_notice("cryptQueryCapability (3DES) failed: status=%d", status);
	}

	return true;
}

void ShutdownCCrypter(void)
{
	cryptEnd();
}

bool EncryptCCTest(Napi::Env env, const char* pstrInput, char* pstrOutput)
{
	bool retVal = false;
	pstrOutput = NULL;
	//
	//CString strInput = Input;
	// CString strOutput;
	CRYPT_CONTEXT cryptContext;
	
	unsigned char Buffer[CRYPT_OP_BUFFER_LEN];
	memset(Buffer, 0xFF, CRYPT_OP_BUFFER_LEN);
	strncpy((char *)Buffer, pstrInput, CRYPT_OP_BUFFER_LEN);

	int status = cryptCreateContext( &cryptContext, CRYPT_UNUSED, CRYPT_ALGO_3DES );
	if (cryptStatusOK(status))
	{
		Napi::Error::New(env, "ALL GOOD");
	} else {

		Napi::Error::New(env, "CRYPT ERROR");
	}

	return true;
}

bool EncryptCC(const char* pstrInput, char* pstrOutput)
{
	bool retVal = false;
	pstrOutput = NULL;
	//
	//CString strInput = Input;
	// CString strOutput;
	CRYPT_CONTEXT cryptContext;
	
	unsigned char Buffer[CRYPT_OP_BUFFER_LEN];
	memset(Buffer, 0xFF, CRYPT_OP_BUFFER_LEN);
	strncpy((char *)Buffer, pstrInput, CRYPT_OP_BUFFER_LEN);
	
	int status = cryptCreateContext( &cryptContext, CRYPT_UNUSED, CRYPT_ALGO_3DES );
	if (cryptStatusOK(status))
	{
		//
		// Setup the Salt
		//
		DWORD SaltKey[2];
		SaltKey[0] = Salt;
		SaltKey[1] = !Salt;

		status = cryptSetAttribute(cryptContext, CRYPT_CTXINFO_KEYING_ITERATIONS, 500);
		if (cryptStatusOK(status))
		{
			status = cryptSetAttributeString( cryptContext, CRYPT_CTXINFO_KEYING_SALT, &SaltKey, 8 );
			if (cryptStatusOK(status))
			{
				status = cryptSetAttributeString( cryptContext, CRYPT_CTXINFO_KEYING_VALUE, "LeapfrogGaming3DES", 18 );
				if (cryptStatusOK(status))
				{
					status = cryptSetAttributeString( cryptContext, CRYPT_CTXINFO_IV, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
					if (cryptStatusOK(status))
					{
						status = cryptEncrypt( cryptContext, Buffer, CRYPT_OP_BUFFER_LEN );
						if( cryptStatusOK( status ) )
						{
							//
							// Base64 Encode the data now
							//
							pstrOutput = new char[128]();
							memset(pstrOutput, 0, 128);
							int len = Base64encode( pstrOutput, Buffer, CRYPT_OP_BUFFER_LEN);
							//strOutput = OutBuffer;
							retVal = true;
							
							// char OutBuffer[128];
							// memset(OutBuffer, 0, 128);
							// int len = Base64encode( OutBuffer, Buffer, CRYPT_OP_BUFFER_LEN);
							// strOutput = OutBuffer;
							// retVal = true;
						}
						else
						{
							b_log_notice("EncryptCC failed:cryptEncrypt status=%d", status);
						}
					}
					else
					{
						b_log_notice("EncryptCC failed:cryptSetAttributeString IV status=%d", status);
					}
				}
				else
				{
					b_log_notice("EncryptCC failed:cryptSetAttributeString keying status=%d", status);
				}
			}
		}
		// Go and destroy the context again
		cryptDestroyContext(cryptContext);
	}
	else
	{
		b_log_notice("EncryptCC failed:cryptCreateContext status=%d", status);
	}
	
	// Output = strOutput;
	return retVal;
}

bool DecryptCC(const char* pstrInput, char *pstrOutput)
{
	bool retVal = false;
	pstrOutput = NULL;
	// CString strInput = Input;
	// CString strOutput;
	//
	// Base64 Encode the data now
	//
	char B64Buffer[128];
	memset(B64Buffer, 0, 128);
	int len = Base64decode(B64Buffer, pstrInput, strlen(pstrInput) );
	if (len != CRYPT_OP_BUFFER_LEN)
	{
		// Output = "<error>";
		return false;
	}
		
	CRYPT_CONTEXT cryptContext;
	
	unsigned char Buffer[CRYPT_OP_BUFFER_LEN];
	memset(Buffer, 0xFF, CRYPT_OP_BUFFER_LEN);
	memcpy((char *)Buffer, B64Buffer, len);
	
	int status = cryptCreateContext( &cryptContext, CRYPT_UNUSED, CRYPT_ALGO_3DES );
	if (cryptStatusOK(status))
	{
		//
		// Setup the Salt
		//
		DWORD SaltKey[2];
		SaltKey[0] = Salt;
		SaltKey[1] = !Salt;
		
		status = cryptSetAttribute(cryptContext, CRYPT_CTXINFO_KEYING_ITERATIONS, 500);
		if (cryptStatusOK(status))
		{
			status = cryptSetAttributeString( cryptContext, CRYPT_CTXINFO_KEYING_SALT, &SaltKey, 8 );
			if (cryptStatusOK(status))
			{
				status = cryptSetAttributeString( cryptContext, CRYPT_CTXINFO_KEYING_VALUE, "LeapfrogGaming3DES", 18 );
				if (cryptStatusOK(status))
				{
					status = cryptSetAttributeString( cryptContext, CRYPT_CTXINFO_IV, "\x00\x00\x00\x00\x00\x00\x00\x00", 8);
					if (cryptStatusOK(status))
					{
						status = cryptDecrypt( cryptContext, Buffer, CRYPT_OP_BUFFER_LEN );
						if (cryptStatusOK( status ) )
						{
							// char *ptr = strOutput.GetBufferSetLength(CRYPT_OP_BUFFER_LEN);
							// memcpy(ptr, Buffer, CRYPT_OP_BUFFER_LEN);
							pstrOutput = new char[CRYPT_OP_BUFFER_LEN]();
							memcpy(pstrOutput, Buffer, CRYPT_OP_BUFFER_LEN);

							retVal = true;
						}
						else
						{
							// b_log_error("decryptCC:cryptDecrypt failed on %s", (LPCTSTR)Input);
						}
					}
					else
					{
						// b_log_error("decryptCC:cryptSetAttributeString IV failed on %s", (LPCTSTR)Input);
					}
				}
				else
				{
					// b_log_error("decryptCC:cryptSetAttributeString KEYING_VALUE failed on %s", (LPCTSTR)Input);
				}
			}
			else
			{
				// b_log_error("decryptCC:cryptSetAttributeString SALT failed on %s", (LPCTSTR)Input);
			}
		}
		// Go and destroy the context again
		cryptDestroyContext(cryptContext);
	}
	else
	{
		// b_log_error("decryptCC:cryptCreateContext failed on %s", (LPCTSTR)Input);
	}
	
	// Output = strOutput;
	// strOutput.ReleaseBuffer();
	return retVal;
}
