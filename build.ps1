# configure + build with MinGW Makefiles (MSYS2 MinGW-w64 g++)
[System.IO.Directory]::CreateDirectory('build')
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release