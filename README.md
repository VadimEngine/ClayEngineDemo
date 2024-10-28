Demo of Clay using "Clay Engine" library from https://github.com/VadimEngine/ClayEngine

# Instructions
## Build and Verify the Clay Static Library
- `cd ./ThirdParty/Clay`
- `git submodule update --init --recursive`
- `./build-tool.sh -Build all`
- `cmake -S . -B build -DBUILD_TESTS=ON`
- `cmake --build ./build/`

Verify the library build by running its unit test:
- `./build/test/Debug/ClayEngineTest.exe`

## Build and Run Demo Application
- To build (outputs to `/build` directory):
    - `cmake -S . -B build`
    - `cmake --build ./build/`
- To run:
    - `./build/Debug/ClayEngineDemo.exe`







