#include <renderdoc/loader.hh>

#ifdef _WIN32
#include <Windows.h>
#elif __linux__
#include <dlfcn.h>
#endif

#include "renderdoc_app.hh"

RENDERDOC_API_1_3_0* renderdoc::renderDocApi = nullptr;

bool renderdoc::init()
{
#ifdef _WIN32
    if (HMODULE mod = GetModuleHandleA("renderdoc.dll"))
    {
        pRENDERDOC_GetAPI RENDERDOC_GetAPI = reinterpret_cast<pRENDERDOC_GetAPI>(GetProcAddress(mod, "RENDERDOC_GetAPI"));
        int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_3_0, reinterpret_cast<void**>(&renderDocApi));

        if (ret != 1)
            renderDocApi = nullptr;
    }
#elif __linux__
    if (void* mod = dlopen("librenderdoc.so", RTLD_NOW | RTLD_NOLOAD))
    {
        pRENDERDOC_GetAPI RENDERDOC_GetAPI = reinterpret_cast<pRENDERDOC_GetAPI>(dlsym(mod, "RENDERDOC_GetAPI"));
        int ret = RENDERDOC_GetAPI(eRENDERDOC_API_Version_1_3_0, reinterpret_cast<void**>(&renderDocApi));

        if (ret != 1)
            renderDocApi = nullptr;
    }
#else
    static_assert(false, "Unimplemented platform");
#endif

    return renderDocApi != nullptr;
}

void renderdoc::startCapture()
{
    if (renderDocApi)
        renderDocApi->StartFrameCapture(nullptr, nullptr);
}

void renderdoc::stopCapture()
{
    if (renderDocApi)
        renderDocApi->EndFrameCapture(nullptr, nullptr);
}

void renderdoc::triggerCapture(unsigned amount)
{
    if (renderDocApi)
    {
        if (amount == 1)
            renderDocApi->TriggerCapture();
        else if (amount > 1)
            renderDocApi->TriggerMultiFrameCapture(amount);
    }
}

bool renderdoc::isFrameCapturing()
{
    if (renderDocApi)
        return renderDocApi->IsFrameCapturing() == 1;

    return false;
}

bool renderdoc::isApiInitialized()
{
    return renderDocApi != nullptr;
}

RENDERDOC_API_1_3_0* renderdoc::getApi()
{
    return renderDocApi;
}
