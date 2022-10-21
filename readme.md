# Opengl-start

Experiments with OpenGL

# Development

How I set up things for development

Install conan using python
```
pip install conan
```

Make build folder, update conan profile
```
mkdir output
cd output
conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan profile update conf.tools.system.package_manager:mode=enabled default
conan profile update conf.tools.system.package_manager:sudo=True default
```

Installing dependencies with conan
```
export CONAN_SYSREQUIRES_MODE="enabled"
export CONAN_SYSREQUIRES_SUDO="1"
conan install ..
```

Build Project (Linux)
```
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build . 
```


