#pragma once

#include <vector>

#include "../../Math/Include/Vector.h"
#include "../../Utils/Include/Constant.h"

namespace NaiveZ3D
{
	class Mesh
	{
	public:
		Mesh(const std::string& mtl, std::vector<Vector3>&& vertexBuffer, std::vector<UINT32>&& indiceBuffer);
		~Mesh()
		{
			mVertexBuffer_.clear();
			mIndiceBuffer_.clear();
		}

		std::vector<Vector3> GetVertexBuffer() const{ return mVertexBuffer_; }
		std::vector<UINT32> GetIndiceBuffer() const{ return mIndiceBuffer_; }

		size_t VertexBufferSize() const { return mVertexBuffer_.size(); }
		size_t IndiceBufferSize() const { return mIndiceBuffer_.size(); }

		bool IsValid() const { return VertexBufferSize() != 0; }

	private:
		std::string mMtlName_;
		std::vector<Vector3> mVertexBuffer_;
		std::vector<UINT32> mIndiceBuffer_;
	};
}