
#ifndef DEMO_CRYPTO_H
#define DEMO_CRYPTO_H

#include <napi.h>

class Crypto : public Napi::ObjectWrap<Crypto>
{
private:
    Napi::FunctionReference _require;

public:
    explicit Crypto(const Napi::CallbackInfo &args);

    Napi::String md5(const Napi::CallbackInfo &args);

    static Napi::Function GetClass(Napi::Env);
};


#endif //DEMO_CRYPTO_H
