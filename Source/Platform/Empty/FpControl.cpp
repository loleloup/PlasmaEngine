// MIT Licensed (see LICENSE.md).
#include "Precompiled.hpp"
#include "Common/FpControl.hpp"

namespace Plasma
{
uint FpuControlSystem::DefaultMask = 0;
bool FpuControlSystem::Active = false;

ScopeFpuExceptionsEnabler::ScopeFpuExceptionsEnabler()
{
}

ScopeFpuExceptionsEnabler::~ScopeFpuExceptionsEnabler()
{
}

ScopeFpuExceptionsDisabler::ScopeFpuExceptionsDisabler()
{
}

ScopeFpuExceptionsDisabler::~ScopeFpuExceptionsDisabler()
{
}

} // namespace Plasma
