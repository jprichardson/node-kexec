#include <cstdio>
#include <stdlib.h>
#include <string.h>
#if defined(__NODE_V0_11_OR_12__) || defined(__NODE_GE_V4__)
#include <fcntl.h>
#endif

//#ifdef __POSIX__
#include <unistd.h>
/*#else
#include <process.h>
#endif*/

#include <nan.h>


using v8::Array;
using v8::FunctionTemplate;
using v8::Handle;
using v8::Integer;
using v8::Local;
using v8::Object;
using v8::String;


static int clear_cloexec (int desc)
{
    int flags = fcntl (desc, F_GETFD, 0);
    if (flags <  0)
        return flags; //return if reading failed

    flags &= ~FD_CLOEXEC; //clear FD_CLOEXEC bit
    return fcntl (desc, F_SETFD, flags);
}

static int do_exec(char *argv[])
{
        clear_cloexec(0); //stdin
        clear_cloexec(1); //stdout
        clear_cloexec(2); //stderr
        return execvp(argv[0], argv);
}

NAN_METHOD(kexec) {
    Nan::HandleScope scope;

    /*
     * Steve Blott: 17 Jan, 2014
     *              Temporary comment by way of explanation...
     *              To be deleted.
     *
     * With a single argument:
     *   - pass it to execvp as "sh -c 'args[0]'"
     *   - this is the existing usage
     *
     * With exactly two arguments:
     *   - the first is the command name
     *   - the second is an array of arguments
     *     ...as in process.child_process.spawn()
     *
     * This approach is not great, but it allows the established usage to
     * coexist with direct execvp-usage, and avoids making any changes to the
     * established API.
     */

    if ( 1 == info.Length() && info[0]->IsString() )
    {
        String::Utf8Value str(info[0]);
        char* argv[] = { const_cast<char *>("/bin/sh"), const_cast<char *>("-c"), *str, NULL};

        int err = do_exec(argv);

        info.GetReturnValue().Set(Nan::New<Integer>(err));
    }

    if ( 2 == info.Length() && info[0]->IsString() && info[1]->IsArray() )
    {
        String::Utf8Value str(info[0]);

        // Substantially copied from:
        // https://github.com/joyent/node/blob/2944e03/src/node_child_process.cc#L92-104
        Local<Array> argv_handle = Local<Array>::Cast(info[1]);
        int argc = argv_handle->Length();

        int argv_length = argc + 1 + 1;
        char **argv = new char*[argv_length];

        argv[0] = *str;
        argv[argv_length-1] = NULL;
        for (int i = 0; i < argc; i++) {
            String::Utf8Value arg(argv_handle->Get(Nan::New<Integer>(i))->ToString());
            argv[i+1] = strdup(*arg);
        }

        int err = do_exec(argv);

        // Failed...!
        // FIXME: It might be better to raise an exception here.
        for (int i = 0; i < argc; i++)
            free(argv[i+1]);
        delete [] argv;

        info.GetReturnValue().Set(Nan::New<Integer>(err));
    }

    return Nan::ThrowTypeError("kexec: invalid arguments");
}


#define EXPORT(name, symbol) exports->Set( \
  Nan::New<String>(name).ToLocalChecked(), \
  Nan::New<FunctionTemplate>(symbol)->GetFunction() \
)

void init (Handle<Object> exports) {
    EXPORT("kexec", kexec);
}

NODE_MODULE(kexec, init);
