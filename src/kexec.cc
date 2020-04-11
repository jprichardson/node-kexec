#include <napi.h>

#include <sstream>
#include <string>
#include <vector>

#include <unistd.h>
#include <fcntl.h>

static void invalidArgs(Napi::Env env) {
    Napi::TypeError::New(env, "invalid arguments: expected string or string, Array<string>").ThrowAsJavaScriptException();
}

static void operationError(Napi::Env env, const char *operation, int code) {
   std::ostringstream msg;
   msg << operation << " failed with code " << code;
   Napi::Error::New(env, msg.str()).ThrowAsJavaScriptException();
}

void Kexec(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    if (info.Length() < 1 || info.Length() > 2 || !info[0].IsString()) {
        invalidArgs(env);
        return;
    }
    // Hold onto a reference to the std::string, to ensure the backing store for the c_str value isn't de-allocated.
    std::string strCmd = info[0].As<Napi::String>().Utf8Value();
    char *cmd = const_cast<char*>(strCmd.c_str());

    char **argv;
    if (1 == info.Length()) {
        argv = new char*[4];
        argv[0] = const_cast<char *>("/bin/sh");
        argv[1] = const_cast<char *>("-c");
        argv[2] = cmd;
        argv[3] = NULL;
    } else {
        if (!info[1].IsArray()) {
            invalidArgs(env);
             return;
        }
        Napi::Array argsFromJS = info[1].As<Napi::Array>();
        const int numArgs = argsFromJS.Length();

        std::vector<std::string> strArgs(numArgs);
        argv = new char*[numArgs + 2];
        argv[0] = cmd;
        for (int argIdx = 0; argIdx < numArgs; ++argIdx) {
            Napi::Value arg = argsFromJS[argIdx];
            if (!arg.IsString()) {
                invalidArgs(env);
                return;
            }
            strArgs[argIdx] = arg.As<Napi::String>().Utf8Value();
            argv[argIdx + 1] = const_cast<char *>(strArgs[argIdx].c_str());
        }
        argv[numArgs + 1] = NULL;
    }

    // Run setfd on descriptors 0 through 2
    for (int descriptor = 0; descriptor <= 2; ++descriptor) {
        int flags = fcntl (descriptor, F_GETFD, 0);
        if (flags <  0) {
            operationError(env, "fcntl GETFD", flags);
            return;
        }

        flags &= ~FD_CLOEXEC; //clear FD_CLOEXEC bit
        int setfdErrCode = fcntl (descriptor, F_SETFD, flags);
        if (setfdErrCode) {
            operationError(env, "fcntl SETFD", setfdErrCode);
            return;
        }
    }

    int execvpErrCode = execvp(argv[0], argv);

    // Because of the exec, we only get here if there's a failure.
    delete [] argv;

    operationError(env, "execvp", execvpErrCode);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "kexec"), Napi::Function::New(env, Kexec));
  return exports;
}

NODE_API_MODULE(kexec, Init)
