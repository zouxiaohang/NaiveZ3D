#pragma once

#include <vector>
#include <map>
#include <string>

#include "Mesh.h"

namespace NaiveZ3D
{
	class Model
	{
	public:
		void AddMesh(Mesh&& mesh)
		{
			mMeshVector_.emplace_back(std::move(mesh));
		}

		void SetMtl(const std::string& mtl) { mMtl_ = mtl; }
		std::string GetMtl()const { return mMtl_; }

		void SetModelName(const std::string& name) { mModelName_ = name; }
		std::string GetModelName()const { return mModelName_; }

		const std::vector<Mesh>& GetAllMesh()const { return mMeshVector_; }
		size_t MeshSize() const { return mMeshVector_.size(); }

		void SetVertexBuffer(const std::vector<Vector3>& vb) { mVertexBuffer_ = vb; }
		const std::vector<Vector3>& GetVertexBuffer() const { return mVertexBuffer_; }

		void SetNormalBuffer(const std::vector<Normal>& nb) { mNormalBuffer_ = nb; }
		const std::vector<Normal>& GetNormalBuffer() const { return mNormalBuffer_; }

		void SetTextureCoordBuffer(const std::vector<TextureCoord>& tb) { mTextureCoordBuffer_ = tb; }
		const std::vector<TextureCoord>& GetTextureCoordBuffer()const { return mTextureCoordBuffer_; }

		bool UseTex()const { return !mTextureCoordBuffer_.empty() && 1; }

	private:
		std::string mModelName_;
		std::string mMtl_;
		std::vector<Mesh> mMeshVector_;

		std::vector<Vector3> mVertexBuffer_;			//全局数据
		std::vector<Normal> mNormalBuffer_;				//全局数据
		std::vector<TextureCoord> mTextureCoordBuffer_;	//全局数据
	};
}