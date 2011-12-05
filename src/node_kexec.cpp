
#include <v8.h>
#include <node.h>
#include <cstdio>

//#ifdef __POSIX__
#include <unistd.h>
/*#else
#include <process.h>
#endif*/

using namespace node;
using namespace v8;

static Handle<Value> kexec(const Arguments& args) {
    String::Utf8Value v8str(args[0]);
    char* argv2[] = {"", "-c", *v8str, NULL};

    execvp("/bin/sh", argv2);      
    return Undefined();
}

extern "C" {
    static void init (Handle<Object> target) {
        NODE_SET_METHOD(target, "kexec", kexec);
    }

    NODE_MODULE(kexec, init);
}