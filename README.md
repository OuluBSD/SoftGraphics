# SoftGraphics

SoftGraphics is a modern virtual graphics hardware abstraction layer and software rasterizer with typed Python shader support designed for Ultimate++ (U++).

## Features

- **Hardware Abstraction Layer (HAL)**: Unified `Device`, `Instance`, `Buffer`, `Texture`, `Shader`, `Pipeline`, and `CommandBuffer` interfaces.
- **CPU Backend**: Fully deterministic CPU reference software renderer and validation backend (`DeviceCPU`) utilizing `ByteVM` and typed Python shaders.
- **Shader IR & Transpiler**: Compiles Python vertex/fragment shaders into intermediate representation (`ShaderIR`) and executes in software or targets modern graphics APIs.
- **UppBuilder & Portage Integration**: Managed via `UppBuilder` and registered in `UppOverlay` (`MediaGfx/SoftGraphics`).

## Package Structure

- `uppsrc/SoftGraphics`: Core graphics HAL, CPU backend, typed Python shader transpiler, buffer and texture management.
- `tests/SoftGraphicsTests`: Automated headless test harness validating instance creation, CPU device capabilities, buffer allocation, texture creation, command recording, and submission.

## Building & Testing

Build and run tests using `UppBuilder`:

```bash
uppbuilder tests/SoftGraphicsTests --bazaarcore <path-to-BazaarCore> --uppgeometry <path-to-UppGeometry> --softscript <path-to-SoftScript>
./bin/SoftGraphicsTests
```

## CI Matrix

Continuous integration verifies 4 platforms on every push:
- Ubuntu Linux (GCC)
- Ubuntu Linux (Clang)
- macOS (Apple Clang)
- Windows (MSVC 2022 x64)
