#include "Include\Mesh.h"

namespace NaiveZ3D
{
	std::vector<unsigned int> Mesh::GetIndiceBuffer() const
	{
		std::vector<unsigned int> indice;

		for (const auto& face : mFaceBuffer_)
		{
			const auto& ib = face.mVertexIndex_;
			if (ib.size() == 3)
			{
				//1、2、3
				indice.insert(indice.end(), ib.begin(), ib.end());
			}
			else if (ib.size() == 4)
			{
				//1、2、3
				indice.emplace_back(ib[0]);
				indice.emplace_back(ib[1]);
				indice.emplace_back(ib[2]);
				//1、3、4
				indice.emplace_back(ib[0]);
				indice.emplace_back(ib[2]);
				indice.emplace_back(ib[3]);
			}
		}

		return indice;
	}
}