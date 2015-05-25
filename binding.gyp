{
  'targets': [
    {
      'target_name': 'xshot',
      'sources': [ 'xshot.cpp' ],
      'include_dirs': [ 
        '<!(node -e "require(\'nan\')")'
      ],
      'link_settings': {
        'xcode_settings': {
          'OTHER_LDFLAGS': [
            '-framework CoreVideo'
          ]
        }
      }
    }
  ]
}