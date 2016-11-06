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

		void SetMtl(const std::string& mtl) { mMtl_ = mtl; }
		std::string GetMtl()const { return mMtl_; }

		void SetModelName(const std::string& name) { mModelName_ = name; }
		std::string GetModelName()const { return mModelName_; }

		const std::vector<Mesh>& GetAllMesh()const { return mMeshVector_; }
		size_t MeshSize() const { return mMeshVector_.size(); }
	private:
		std::string mModelName_;
		std::string mMtl_;
		std::vector<Mesh> mMeshVector_;
	};
}