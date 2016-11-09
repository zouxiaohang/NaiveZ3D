#pragma once

#include <vector>

#include "Mesh.h"

namespace NaiveZ3D
{
	class Model
	{
	public:
		void AddMesh(Mesh& mesh)
		{
			mMeshVector_.push_back(mesh);
			
			//mVertexBuffer_.insert(mVertexBuffer_.end(), mesh.GetVertexBuffer().begin(), mesh.GetVertexBuffer().end());
			//mTextureCoordBuffer_.insert(mTextureCoordBuffer_.begin(), mesh.GetTextureCoordBuffer().begin(), mesh.GetTextureCoordBuffer().end());
			//mNormalBuffer_.insert(mNormalBuffer_.begin(), mesh.GetNormalBuffer().begin(), mesh.GetNormalBuffer().end());
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

	private:
		std::string mModelName_;
		std::string mMtl_;
		std::vector<Mesh> mMeshVector_;

		std::vector<Vector3> mVertexBuffer_;			//全局数据
		std::vector<Normal> mNormalBuffer_;				//全局数据
		std::vector<TextureCoord> mTextureCoordBuffer_;	//全局数据
	};
}