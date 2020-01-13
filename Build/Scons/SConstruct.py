import os
import fnmatch
import subprocess

#plasmaRoot = os.environ["PLASMA_SOURCE"] + "/";
plasmaRoot = "/home/chrispe/PlasmaAll/Plasma/"
pythonPath = "/usr/include/python3.2/";
backToRoot = "../../";
externalPath = "PlasmaExternal/"
#externalPath = "/PlasmaExternal/"

# All of our dependencies (the include directories)
includes =  [
              plasmaoRoot + "Libraries/Common",
              plasmaoRoot + "Libraries",
              plasmaoRoot + "Systems",
       
              plasmaoRoot + "External/GL",
              plasmaoRoot + "External/GLEW/include",
              plasmaoRoot + "External/Cg/include",
              plasmaoRoot + "External/FMOD/inc",
              plasmaoRoot + "External/ZLib/include",

              plasmaoRoot + "Extensions",
              plasmaoRoot + "Extensions/Scintilla/include",
              plasmaoRoot + "Extensions/Scintilla/lexlib",
              plasmaoRoot + "Extensions/Scintilla/src",
              
              "/usr/include/python3.2",

              plasmaRoot + externalPath + "soil",
              plasmaRoot + externalPath + "freetype/include/freetype/config/",
              plasmaRoot + externalPath + "freetype/include",

              "/home/chrispe/PlasmaAll/Plasma/Lightning/Project",

	            "/usr/include/nvidia-current/",
            ]

# The paths we use to provide libraries to the linkers
libraryPaths =  [
                  pythonPath + "/libs",
                  "/usr/lib/mesa/",
		              #"/usr/lib/nvidia-current/",
                ]


# All the options to the MSCV linker
linkerOptionsMsvc = [
                      "/SUBSYSTEM:WINDOWS",
                      "/MACHINE:X86",
                      "/NXCOMPAT",
                      "/DYNAMICBASE",
                      
                      "/LTCG",
                      "/TLBID:1",
                      "/ALLOWISOLATION",
                      "/INCREMENTAL:NO",
                    ]

# All the options to the GCC linker
linkerOptionsGcc =  [
                      #"-mwindows",
                    ]

# All the options to the MSCV compiler
compilerOptionsMsvc = [
                        "/MT",
                        "/Gd",
                        "/Zi",
                        "/MP",
                        "/O2",
                        "/Oi",
                        "/Oy-",
                        "/GL",
                        "/Gm-",
                        "/EHsc",
                        "/GS-",
                        "/Zc:wchar_t",
                        "/Zc:forScope",
                        "/GR-",
                      ]

# All the options to the GCC compiler
compilerOptionsGccWin =  [
                        "-std=c++0x",
                        "-fpermissive",
                        "-w",
                        "-mwindows"
                      ]

compilerOptionsGccLin =  [
                        "-std=c++0x",
                        "-fpermissive",
                        "-w",
                        "-g"
                        ]


# The standard MSCV libraries that we depend on
librariesMsvc = [
                  "kernel32.lib",
                  "user32.lib",
                  "gdi32.lib",
                  "winspool.lib",
                  "comdlg32.lib",
                  "advapi32.lib",
                  "shell32.lib",
                  "ole32.lib",
                  "oleaut32.lib",
                  "uuid.lib",
                  "odbc32.lib",
                  "odbccp32.lib",
                ]

# The standard GCC libraries that we depend on
librariesGccWin  = [ 
                  "opengl32", 
                  "python32", 
                  "fmodex", 
                  "z" , 
                  "ws2_32", 
                  "freetype", 
                  "iphlpapi" , 
                  "shell32" , 
                  "comctl32", 
                  "comdlg32" , 
                  "gdi32" , 
                  "user32",
                  "mingw32"
                ]

librariesGccLin  = [ 
                    "GL",
                    "fmodex-4.40.00",
                    "python3.2mu",
                    "Cg",
                    "CgGL",
                  ]

# The defines passed into the compiler
definesWin = [
            "WIN32",
            "_WIN32"
            "NDEBUG",
            "_CRT_SECURE_NO_WARNINGS",
          ]

definesLin = [
            "NDEBUG",
            "FT2_BUILD_LIBRARY"
             ]

#-------------------------------------------------       

# Create an GCC environment
#definesLin.append("__CYGWIN32__");
#definesLin.append("__MINGW32__");
definesLin.append("GLEW_STATIC");
definesLin.append("GLEW_NO_GLU");


#env = Environment(tools = ["mingw"])
env = Environment()
env.Append(LINKFLAGS = linkerOptionsGcc)
env.Append(CCFLAGS = compilerOptionsGccLin)
env.Append(LIBS = librariesGccLin)

# Create an MSVC environment
#env = Environment()
#env.Append(LINKFLAGS = linkerOptionsMsvc)
#env.Append(CCFLAGS = compilerOptionsMsvc)
#env.Append(LIBS = librariesMsvc)

#-------------------------------------------------

# Set the includes paths and the defines
env.Append(CPPPATH = includes)
env.Append(CPPDEFINES = definesLin)
env.Append(LIBPATH = libraryPaths)

projects =  [

              # Extensions
              { "name" : "Editor",            "location" : "Extensions/Editor"           },
              { "name" : "Gameplay",          "location" : "Extensions/Gameplay"         },
              { "name" : "Scintilla",         "location" : "Extensions/Scintilla"        },
              { "name" : "Widget",            "location" : "Extensions/Widget"           },
              { "name" : "RayTracer",         "location" : "Extensions/RayTracer"        },
              { "name" : "Pathfinding",       "location" : "Extensions/Pathfinding"      },

              # Systems
              { "name" : "Content",           "location" : "Systems/Content"             },
              { "name" : "Engine",            "location" : "Systems/Engine"              },
              { "name" : "Graphics",          "location" : "Systems/Graphics"            },
              { "name" : "Networking",        "location" : "Systems/Networking"          },
              { "name" : "Physics",           "location" : "Systems/Physics"             },
              { "name" : "PyScript",          "location" : "Systems/PyScript"            },
              { "name" : "Sound",             "location" : "Systems/Sound"               },

              # Libraries
              { "name" : "Platform",          "location" : "Libraries/Platform/Generic"  },
              { "name" : "Geometrics",        "location" : "Libraries/Geometrics"        },
              { "name" : "Math",              "location" : "Libraries/Math"              },
              { "name" : "Meta",              "location" : "Systems/Meta"                },
              { "name" : "Serialization",     "location" : "Libraries/Serialization"     },
              { "name" : "SpatialPartition",  "location" : "Libraries/SpatialPartition"  },
              { "name" : "Support",           "location" : "Libraries/Support"           },
              { "name" : "Common",            "location" : "Libraries/Common"            },
              
              { "name" : "Lightning",             "location" : "Lightning/Project/Lightning"         },

              # External
              { "name" : "Soil",              "location" : externalPath + "soil", 
                "sources" : 
                      ["image_DXT.c", "image_helper.c", "stb_image_aug.c", "SOIL.c"]     },                                             

              { "name" : "freetype",        "location" : externalPath + "freetype", 
                "sources" : 
                  ["ftbbox.c", "ftmm.c", "ftpfr.c", "ftsynth.c", "fttype1.c", "ftwinfnt.c",
                   "pcf.c",  "pfr.c", "psaux.c", "pshinter.c", "psmodule.c", "raster.c", 
                   "sfnt.c", "truetype.c", "type1.c", "type1cid.c", "type42.c", "winfnt.c", 
                   "autofit.c", "bdf.c", "cff.c", "ftbase.c", "ftbitmap.c", "ftcache.c", 
                   "ftgasp.c", "ftglyph.c", "ftgzip.c", "ftinit.c", "ftlzw.c", "ftstroke.c", 
                   "ftsystem.c", "smooth.c" ]},
              
              { "name" : "Glew",            "location" : externalPath + "glew", 
                "sources" :  
                  ["glew.c"]},

              #{ "name" : "WindowsPlatform",   "location" : "Libraries/Windows"           },       

              #{ "name" : "WindowsSystem",     "location" : "Systems/Windows"             }, 
             
              # Projects
              #{ "name" : "PlasmaEditor",        "location" : "Projects/Editor"             },

              { "name" : "PlasmaEditor",        "location" : "Projects/LinuxEditor"     },
            ]

# The compilation files we wish to ignore
ignores = [
            "MultiSAP.cpp",
            "MultiSapCast.cpp",
            "MultiSapCells.cpp",
            "StackWalker.cpp",
            #"Shader.cpp",
            "TcpSocket.cpp",
            "Regex.cpp",
            "HGrid.cpp",
            "StreamTexture.cpp",
          ]

createPrecompiled = False;

# A list of all the built libraries
builtLibraries = []

# 
allFiles = []


def PrecompiledHeader(fullfile):
  #os.execlp("g++", "g++", "-o", fullFile + ".pch", "-c",  fullFile);
  commandLine = "g++ -o " + fullFile + ".pch" + " -c ";

  for option in compilerOptionsGccLin:
    commandLine+=option;
    commandLine+=' ';
  
  for include in includes:
    commandLine+='-I';
    commandLine+=include;
    commandLine+=' ';

  commandLine+=fullFile;
  #print(commandLine);
  subprocess.call(commandLine, shell=True);

def processFile(files, file, root):
  # Get the full path to the file
  fullFile = os.path.join(walkroot, filename)

  # Get the relative path to the file
  # We have to append the relative directory used for build output - variant builds
  relativeFile = backToRoot + os.path.relpath(fullFile, plasmaRoot)

  # Add the file to the list of project files
  files.append(relativeFile)


# Loop through all the defined projects
for project in projects:
  # Get the projects name
  projectName = project["name"];

  print("Checking Project", projectName);
  
  # Create an array to store all the files to be compiled for that project
  files = []  

  checkSources = "sources" in project

  # Recursively loop through all the project directories at the root
  for walkroot, dirnames, filenames in os.walk(plasmaRoot + project["location"]):

    for filename in filenames:

      if(createPrecompiled and filename == "Precompiled.hpp"):
        fullFile = os.path.join(walkroot, filename)
        PrecompiledHeader(fullfile);
      
      # Loop through the cpp or c files
      if(fnmatch.fnmatch(filename, "*.c[px][px]") or 
         fnmatch.fnmatch(filename, "*.c") ):

        # Should we ignore the file?
        shouldIgnore = False
    
        # Loop through all of our ignores
        for ignore in ignores:
          # If the filename matches an ignore file...
          if(filename == ignore):
            # Ignore it!
            shouldIgnore = True

        if(checkSources):
          shouldIgnore = True

          for source in project["sources"]:
             if(filename == source):
                shouldIgnore = False

        # As long as we shouldn't ignore the file...
        if (shouldIgnore == False):
          processFile(files, file, walkroot);


  directBuild = True;

  #if( projectName=="PlasmaEditor" or "sources" in  project 
  #   or projectName=="Geometrics" or projectName == "Math" or
  #   projectName=="WindowsPlatform"):
  #   directBuild = True;

  if( projectName=="PlasmaEditor" ):
    directBuild = True;

  if directBuild:
    allFiles = allFiles + files

  # Compile the current project into a library
  if(projectName=="PlasmaEditor"):
  

    env.Program(target = "Plasma", source = allFiles, LIBS=builtLibraries+librariesGccLin)
    #env.Program(target = "Plasma.exe", source = allFiles, LIBS=librariesGcc)

  else:

    if( not directBuild ):
        builtLibrary = env.StaticLibrary(target = projectName, source = files, LIBS=builtLibraries)
        # Add the library to the list of built libraries
        builtLibraries.extend(builtLibrary);

# Build the final executable
#env.Program(target = "Plasma.exe", source = builtLibraries)
