{
  'targets': [
    {
      'target_name': 'kexec',
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      'sources': [ 'src/kexec.cc' ],
      'include_dirs': [ "<!@(node -p \"require('node-addon-api').include\")" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
