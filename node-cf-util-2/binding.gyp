{
  "targets": [
    {
      "target_name": "hello",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc": [ "-std=c++11" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "sources": [ "hello.cc", 
        "./cf-crypter.cpp",
        "./HexUtils.cpp",
        "./cl342/test/certimp.c",
        "./cl342/test/certproc.c",
        "./cl342/test/certs.c",
        "./cl342/test/devices.c",
        "./cl342/test/envelope.c",
        "./cl342/test/highlvl.c",
        "./cl342/test/keydbx.c",
        "./cl342/test/keyfile.c",
        "./cl342/test/loadkey.c",
        "./cl342/test/lowlvl.c",
        "./cl342/test/s_cmp.c",
        "./cl342/test/s_scep.c",
        "./cl342/test/sreqresp.c",
        "./cl342/test/ssh.c",
        "./cl342/test/ssl.c",
        "./cl342/test/stress.c",
        "./cl342/test/testfunc.c",
        "./cl342/test/testlib.c",
        "./cl342/test/utils.c" 
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "./cl342",
        "./cl342/test",
        "D:\\Projects\\learn\\nodejs\\node-architecture\\node-cf-util-2\\cl342",
        "D:\\Projects\\learn\\nodejs\\node-architecture\\node-cf-util-2\\cl342\\test"
      ],
      "libraries": ["-lD:\\Projects\\learn\\nodejs\\node-architecture\\node-cf-util-2\\cl342\\binaries64_vs10\\cl64.lib",
      "-lwsock32.lib",
      "-lodbccp32.lib",
      "-luser32.lib",
      "-llegacy_stdio_definitions.lib"],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS','STATIC_LIB' ],
      "configurations": {
        "release": {
          "msvs_settings": {
            "VCCLCompilerTool": {      
              "RuntimeLibrary": 2, # multi threaded DLL
            }
          }
        },
      },
      'msvs_settings_IGNORE':{
        "VCCLCompilerTool": {
          'WholeProgramOptimization':'false'
        },
        "VCLibrarianTool": {
          'AdditionalOptions':[
            '/LTCG:OFF'
          ]
        },
        "VCLinkerTool": {
          'LinkIncremental':1
        },
      }
    }
  ]
}