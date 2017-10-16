#include <napi.h>


void SumSyncCallback(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 3) {
    Napi::TypeError::New(env, "Invalid argument count").ThrowAsJavaScriptException();
    return;
  }

  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsFunction()) {
    Napi::TypeError::New(env, "Invalid argument types").ThrowAsJavaScriptException();
    return;
  }

  double arg0 = info[0].As<Napi::Number>().DoubleValue();
  double arg1 = info[1].As<Napi::Number>().DoubleValue();
  Napi::Number num = Napi::Number::New(env, arg0 + arg1);

  Napi::Function cb = info[2].As<Napi::Function>();
  cb.MakeCallback(env.Global(), { env.Null(), num });
}


Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(
    Napi::String::New(env, "add"),
    Napi::Function::New(env, SumSyncCallback)
  );
  return exports;
}


NODE_API_MODULE(addon, Init)
