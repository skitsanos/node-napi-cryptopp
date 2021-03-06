/**
 *
 * @author skitsanos, http://github.com/skitsanos
 * @version 1.0.2
 */

#ifndef DEMO_DEMOCLASS_H
#define DEMO_DEMOCLASS_H

#include <napi.h>


class DemoClass : public Napi::ObjectWrap<DemoClass>
{
private:
    Napi::FunctionReference _require;

public:
    explicit DemoClass(const Napi::CallbackInfo &args);

    Napi::String sayHi(const Napi::CallbackInfo &args);

    Napi::Buffer<char> stringToBuffer(const Napi::CallbackInfo &args);

    Napi::Buffer<char> cryptoRandomBytes(const Napi::CallbackInfo &args);

    static Napi::Function GetClass(Napi::Env);
};


#endif //DEMO_DEMOCLASS_H
