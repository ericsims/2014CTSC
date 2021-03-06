{
  'targets': [
    {
      'target_name': 'track',
       'libraries': [
          '-lutil',
          '-L/usr/lib',
          '-L/usr/local/lib',
          '-lopencv_core',
          '-lopencv_imgproc',
          '-lopencv_objdetect',
          '-lopencv_highgui'
        ],
      'sources': [ 
      	'lib/track.cc',
      	'lib/Cordinate.cc',
      	'lib/Cordinate.h',
      	'lib/Callback.cc',
      	'lib/Callback.h',
      	'lib/Map.cc',
      	'lib/Map.h',
      	'lib/Time.cc',
      	'lib/Time.h',
      	'lib/rs232.c',
      	'lib/rs232.h',
      	'lib/Cv.cc',
      	'lib/Cv.h',
      	'lib/Serial.cc'
      ]
    }
  ]
}