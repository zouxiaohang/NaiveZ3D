#pragma once

namespace NaiveZ3D
{
	struct GLColor
	{
		GLColor(float r, float g, float b, float a = 1.0)
			:red(r),
			green(g),
			blue(b),
			alpha(a)
		{}

		float red;
		float green;
		float blue;
		float alpha;
	};
}