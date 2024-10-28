Demo of Clay using "Clay Engine" library from https://github.com/VadimEngine/ClayEngine

# Instructions
## Build and Verify the Clay Static Library
- `git submodule update --init --recursive`
- `cd ./ThirdParty/Clay`
- `./build-tool.sh -Build all`
- `cmake -S . -B build -DBUILD_TESTS=ON`
- `cmake --build ./build/`

Verify the library build by running its unit test:
- `./build/test/Debug/ClayEngineTest.exe`

Alternately, the prebuilt binary and header files can be downloaded from the releases https://github.com/VadimEngine/ClayEngine/releases. If `./ThirdParty/clay` is replaced with the unzipped content, the project can be built without the need to handle the submodules.

## Build and Run Demo Application
- To build (outputs to `/build` directory):
    - `cmake -S . -B build`
    - `cmake --build ./build/`
- To run:
    - `./build/Debug/ClayEngineDemo.exe`







