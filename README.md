# RenderDoc Loader

Platform-independent RenderDoc API loader

```C++
#include <renderdoc/loader.hh>

void main() {
  if (renderdoc::init())
    log << "RenderDoc detected!";

  renderdoc::startCapture();
  // Render something..
  renderdoc::stopCapture();
}

```

The included CMake file provides the `rdocloader` target. Currently supported platforms are Windows and Linux.
