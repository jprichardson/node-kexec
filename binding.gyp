{
  'targets': [
    { 'target_name': '' }
  ],
  'conditions': [
    ['OS=="mac"', {
      'targets': [{
        'target_name': 'kexec',
        'sources': [ 'src/kexec.cc' ],
        'defines': [
          '<!@(node -v |grep "v[^0]" > /dev/null && echo "__NODE_GE_V4__" || true)',
          '<!@(node -v |grep "v0\.1[12]" > /dev/null && echo "__NODE_V0_11_OR_12__" || true)',
          '<!@(command -v iojs > /dev/null && echo "__NODE_V0_11_OR_12__" || true)',
          '<!@(node -v |grep "v0\.10" > /dev/null && echo "__NODE_V0_10__" || true)',
        ],
        "include_dirs": ["<!(node -e \"require('nan')\")"]
      }]
    }]
  ]
}
