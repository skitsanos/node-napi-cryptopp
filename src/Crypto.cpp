//
// Created by Evgenios Skitsanos on 8/24/21.
//

#include <regex>
#include "Crypto.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptlib.h>
#include <hex.h>
#include <md5.h>

using namespace Napi;
using namespace CryptoPP;

////https://napi.inspiredware.com/getting-started/objectwrap.html
Crypto::Crypto(const CallbackInfo &args) : ObjectWrap(args)
{
    this->_env = args.Env();

    if (args.Length() < 1 || !args[0].IsFunction())
    {
        Napi::TypeError::New(this->_env, "Function expected").ThrowAsJavaScriptException();
    }

    //
    // verify arguments passed to ensure that it was the {require} function that was sent as an ergument
    //
    Napi::Function require = args[0].As<Napi::Function>();

    std::regex self_regex("^function require\\(path\\)",
                          std::regex_constants::ECMAScript | std::regex_constants::icase);

    if (!std::regex_search(require.ToString().Utf8Value().c_str(), self_regex))
    {
        Napi::TypeError::New(this->_env, "{require} Function expected").ThrowAsJavaScriptException();
    }

    this->_require = Persistent(require);
}

Napi::Function Crypto::GetClass(Napi::Env env)
{
    return DefineClass(env, "Crypto", {
            Crypto::InstanceMethod("md5",
                                   reinterpret_cast<InstanceMethodCallback>(&Crypto::md5)),
    });
}

Napi::String Crypto::md5(const CallbackInfo &args)
{
    if (args.Length() < 1 || !args[0].IsString())
    {
        Napi::TypeError::New(this->_env, "Function expected").ThrowAsJavaScriptException();
    }

    Napi::Env env = args.Env();

    CryptoPP::Weak::MD5 hash;
    CryptoPP::byte digest[CryptoPP::Weak::MD5::DIGESTSIZE];

    auto message = args[0].As<String>().Utf8Value();

    hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte *>(message.c_str()), message.length());

    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach( new CryptoPP::StringSink( output ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();

    return Napi::String::New(env, output);
}

