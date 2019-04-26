#pragma once

struct RENDERDOC_API_1_3_0;

namespace renderdoc
{
extern RENDERDOC_API_1_3_0* renderDocApi;

/// Initializes the RenderDoc API, returns true on success
bool init();

/// Starts RenderDoc frame capture
void startCapture();

/// Stops RenderDoc frame capture
void stopCapture();

/// Trigger one or multiple (successive) frame captures, as if the user had pressed the capture hotkey
void triggerCapture(unsigned amount = 1);

/// Returns true if the current frame is being captured
bool isFrameCapturing();

/// Returns true if the RenderDoc API is present and usable
bool isApiInitialized();

/// Returns the raw API pointer for custom use
RENDERDOC_API_1_3_0* getApi();
}
