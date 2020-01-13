///////////////////////////////////////////////////////////////////////////////
/// Authors: Dane Curbow, Chris Peters
/// Copyright 2010-2016, DigiPen Institute of Technology
///////////////////////////////////////////////////////////////////////////////
#pragma once

namespace Plasma
{
// On some platforms such as Emscripten we need to yield back to the operating system / browser.
// This is known as cooperative-multitasking.

// On this platform, do we support drawing to the display
// (rendering / blitting, etc) when not running the main loop.
extern bool SupportsRenderingOutsideMainLoop;

// Yield back to the operating system or browser. This function does nothing on platforms
// that do not need it, however it may have serious build ramifications if used.
void YieldToOs();

// Initailize our main loop (called automatically by Common/Platform initialization).
void InitializeMainLoop();

typedef void(*MainLoopFn)(void* userData);

// Runs a loop in a continuous update until 'StopMainLoop' is called.
// Only one per thread is allowed. This will automatically call 'StopMainLoop' if
// another loop is currently running.
void RunMainLoop(MainLoopFn callback, void* userData);

// Stops a running main loop (may be called even when a loop is not running.
// Note that this may not return to the code that invoked 'RunMainLoop' depending on the platform.
void StopMainLoop();

}// namespace Plasma