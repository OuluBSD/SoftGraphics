# AGENTS.md — SoftGraphics Architecture & Extension Guide

## Overview

`SoftGraphics` provides a virtual graphics device abstraction layer and CPU software renderer for Ultimate++. It supports pipeline creation, typed Python shader compilation, resource binding, and command buffer submission.

## Dependencies

- Foundation: `BazaarCore` (supplies `Core`, `Core/TextParsing`)
- Math: `UppGeometry` (supplies `Geometry`, `Draw/Extensions`, `plugin/Eigen`)
- Scripting & VM: `SoftScript` (supplies `ByteVM`, `ByteVM/Python`)

## Directory Layout

- `uppsrc/SoftGraphics/`:
  - `SoftGraphics.h`: Master types, enumeration descriptors (`BufferDesc`, `TextureDesc`, `ShaderDesc`, `GraphicsPipelineDesc`).
  - `Device.h`, `Device.cpp`: Abstract `Device` interface and `DeviceCPU` software implementation.
  - `Instance.h`, `Instance.cpp`: `Instance` factory functions (`sgCreateInstance`, `sgCreateDevice`).
  - `Buffer.h`, `Buffer.cpp`: GPU buffer abstractions (`BufferCPU`).
  - `Texture.h`, `Texture.cpp`: 1D/2D/3D texture maps and format layouts.
  - `Shader.h`, `Shader.cpp`: Vertex, Fragment, and Compute shader objects.
  - `Pipeline.h`, `Pipeline.cpp`: Pipeline state objects.
  - `Framebuffer.h`, `Framebuffer.cpp`: Color and depth render targets.
  - `CommandBuffer.h`, `CommandBuffer.cpp`: Render pass recording and dispatch commands.
  - `ShaderIR.h`, `ShaderIR.cpp`: Intermediate representation of AST shaders.
  - `ShaderTranspiler.h`, `ShaderTranspiler.cpp`: Typed Python to bytecode/IR transpilation.
  - `CpuBackend.h`, `CpuBackend.cpp`: Software rasterizer and pixel evaluation loop.
- `tests/SoftGraphicsTests/`:
  - Automated headless test harness covering device creation, buffer updates, texture initialization, command buffer queues, and shader descriptions.

## Build Verification

Run with `UppBuilder`:
```bash
uppbuilder tests/SoftGraphicsTests --bazaarcore <path-to-BazaarCore> --uppgeometry <path-to-UppGeometry> --softscript <path-to-SoftScript> -v
./bin/SoftGraphicsTests
```
CI runs across 4 platforms (Ubuntu GCC, Ubuntu Clang, macOS Clang, Windows MSVC).
