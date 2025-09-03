# vec
Dynamic vector written in C.

## Features
- Compile-time type-safety is ensured by the type specific code generator macro provided by the library.
- Run-time memory-safety is ensured by carrying out out-of-bounds checks when accessing elements in the vector.
- Macro wrappers for convenience.

## Installation
```bash
git clone https://github.com/broskobandi/vec.git &&
cd vec &&
make &&
sudo make install
```

## Uninstallation
```bash
cd vec &&
make clean &&
sudo make uninstall
```

## Testing
```bash
cd vec &&
make clean &&
make test
```

## Documentation
This requires doxygen to be installed on your system.
```bash
cd vec &&
make doc
```
Open generated doc/html/index.html with your web browser.

## Usage
For detailed usage instructions, please refer to example.c
Add the following compile flags when compiling:
```bash
gcc your_program.c -L/usr/local/lib -lvec
```
