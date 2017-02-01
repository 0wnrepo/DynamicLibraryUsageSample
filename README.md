# DynamicLibraryUsageSample
Example of how to builde a dynamic load library (dll) in one project and how (and what) to add in an other project to use the methods defined in that dynamic library, using only the dll-file or dll togehther with the lib-file.

- DynamicLibraryDllLibSample - The Dynamic Library Project. Build it first to get the ".dll" and ".lib" File. By default the Project is set to Debug-build.
- DynamicLibraryDllLibApp - Project that uses both files (LIB-file and DLL-file) to extract and use the methods from the DLL-file Library Project. The "DynamicLibraryDllLibSample.h" file in this project was added directly from the Library path (Add -> Existing Item -> "..\DynamicLibraryDllLibSample\DynamicLibraryDllLibSample\DynamicLibraryDllLibSample.h")
- DynamicLibraryDllOnlySample - The Dynamic Library Project. Build it first to get the ".dll" and ".lib" File. By default the Project is set to Debug-build.
- DynamicLibraryDllOnlyApp - Project that uses only DLL-file to extract and use the methods from the DLL-file Library Project. The "DynamicLibraryDllOnlyApp.h" file in this project was added directly from the Library path (Add -> Existing Item -> "..\DynamicLibraryDllOnlyApp\DynamicLibraryDllOnlyApp\DynamicLibraryDllOnlyApp.h")

- Dependency Walker - folder inside Samples folders. Contains an archive with a Software that we can use to see the methods defined in the dll-files

Additional Steps for DynamicLibraryApp if you create you own project from the Start.
