#pragma once

#include "boatx/log.h"

namespace boatx::graphics
{
    void CheckGLError();
}

#ifndef BOATX_CONFIG_RELEASE
#define BOATX_CHECK_GL_ERROR boatx::graphics::CheckGLError();
#else
#define BOATX_CHECK_GL_ERROR (void)0
#endif