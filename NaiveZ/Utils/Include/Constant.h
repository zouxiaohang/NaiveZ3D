#pragma once

#include <cstdint>

#include "../../Core/GLRender/Include/GLColor.h"

namespace NaiveZ3D
{
	using UINT32 = uint32_t;

	namespace Color
	{
		const GLColor Black = GLColor(0.0, 0.0, 0.0);
		const GLColor White = GLColor(1.0, 1.0, 1.0);
		const GLColor Red = GLColor(1.0, 0.0, 0.0);
		const GLColor Green = GLColor(0.0, 1.0, 0.0);
		const GLColor Blue = GLColor(0.0, 0.0, 1.0);
	}
}