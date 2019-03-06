#include "windows.h"
#include <napi.h>

// predeclaration of c++ function
bool EncryptCC(const char* pstrInput, char* pstrOutput);
bool EncryptCCTest(Napi::Env env, const char* pstrInput, char* pstrOutput);


Napi::String Method(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, "world");
}

Napi::String Encrypt(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  // lets try and call the encrypt function here .. 
  char *pstrOutput = NULL;
  EncryptCCTest(env, "Hello World", pstrOutput);
  // EncryptCC("Hello World", pstrOutput);
  if (pstrOutput) {
    delete [] pstrOutput;
  }

  return Napi::String::New(env, "world");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "hello"), Napi::Function::New(env, Method));
  exports.Set(Napi::String::New(env, "encrypt"), Napi::Function::New(env, Encrypt));
  return exports;
}

NODE_API_MODULE(hello, Init)