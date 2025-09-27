# configure + build with MinGW Makefiles (MSYS2 MinGW-w64 g++)
mkdir build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
# executable is placed in the project root (per your CMake)
.\tram-sim.exe