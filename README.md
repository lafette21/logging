# logging
A C++ logging wrapper library to ease the third-party logger switch.

## Install

For the installation of this library you will need [Conan](https://conan.io/)

1. Clone the repository

    Via HTTPS:
    `git clone https://github.com/laFette21/logging.git`

    Via SSH:
    `git clone git@github.com:laFette21/logging.git`

2. Change directory to the root of the repository

    `cd /path/to/logging`

3. Export the library via Conan

    `conan export .`

After this process you should be able to use `logging` within a conanfile.txt.

## Example

conanfile.txt
```
[requires]
logging/0.1.2

[generators]
cmake
```

For the C++ usage please observe the `main.cc` file under `logging/src`.
