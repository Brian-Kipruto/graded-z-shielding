# Graded-Z Shielding: AI-Driven Virtual Design Tool

MSc thesis project — University of Nairobi, Institute of Nuclear Science & Technology.

A hybrid Monte Carlo + Machine Learning framework for rapid performance prediction
of flexible Graded-Z radiation shielding composites.

## Status

🚧 In development — Phase I: Geant4 simulation framework

## Build

Requires:
- Geant4 11.2.1 (with Qt and multithreading support)
- CMake 3.16+
- C++17 compiler

```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
./graded-z
```

## Project Structure
include/    Header files (.hh)
src/        Implementation files (.cc)
macros/     Geant4 macro files
data/       Simulation outputs (gitignored)
analysis/   Python ML and plotting scripts
docs/       Design notes and documentation

## Author

Brian Kipruto Kosgei — FNS6/48630/2025
MSc Nuclear Science & Technology

## License

[To be decided]