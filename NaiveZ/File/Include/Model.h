#pragma once

#include <vector>

#include "Mesh.h"

namespace NaiveZ3D
{
	class Model
	{
	public:
		void AddMesh(const Mesh& mesh)
		{
			mMeshVector_.push_back(mesh);
		}

		size_t MeshSize() const { return mMeshVector_.size(); }
	private:
		std::vector<Mesh> mMeshVector_;
	};
}