{
  'targets': [
    {
      'target_name': 'kexec',
      'sources': [ 'src/kexec.cc' ],
      'defines': [
        '<!@(node -v |grep "v0.1[12]" > /dev/null && echo "__NODE_GTE_V0_11__" || echo "__NODE_LT_V0_11__")',
        '<!@(command -v iojs > /dev/null && echo "__NODE_GTE_V0_11__" || echo "__NODE_LT_V0_11__")'
      ]
    }
  ]
}
