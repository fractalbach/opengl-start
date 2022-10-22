# Opengl-start

Experiments with OpenGL!

# Development (Linux)

This is how I set up things for development. To automatically do all of the
steps that are outlined below, you can use the `install` the script:

```bash
./install
```

After making changes to the code, one can easily re-build and run by using the
convient `run` script:

```bash
./run
```

NOTE: If running the output binary directly, do so when the shell's current 
directory is in the `build` directory.


## Inside the Install Script

Install conan using python

```bash
pip install conan
```

Create a Conan Profile

```bash
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan profile update conf.tools.system.package_manager:mode=enabled default
conan profile update conf.tools.system.package_manager:sudo=True default
```

Install Dependencies with Conan and Build

```bash
mkdir build
cd build
export CONAN_SYSREQUIRES_MODE="enabled"
export CONAN_SYSREQUIRES_SUDO="1"
conan install ..
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . 
```
