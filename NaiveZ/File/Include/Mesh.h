#pragma once

#include <vector>

#include "../../Math/Include/Vector.h"
#include "../../Utils/Include/Constant.h"
#include "Face.h"

namespace NaiveZ3D
{
	class Mesh
	{
	public:
		//Mesh(const std::string& mtl, std::vector<Vector3>&& vertexBuffer, std::vector<UINT32>&& indiceBuffer);
		//~Mesh()
		//{
		//	mVertexBuffer_.clear();
		//	mIndiceBuffer_.clear();
		//	mTextureCoordBuffer_.clear();
		//}
		void SetName(const std::string& name) { mName_ = name; }
		std::string GetName()const { return mName_; }

		void SetMtl(const std::string& mtl) { mMtlName_ = mtl; }
		std::string GetMtl()const { return mMtlName_; }

		void SetVertexBuffer(const std::vector<Vector3>& vb) { mVertexBuffer_ = vb; }
		void AddVertex(const Vector3& v) { mVertexBuffer_.push_back(v); }
		std::vector<Vector3> GetVertexBuffer() const{ return mVertexBuffer_; }
		size_t VertexBufferSize() const { return mVertexBuffer_.size(); }

		void SetNormalBuffer(const std::vector<Normal>& nb) { mNormalBuffer_ = nb; }
		void AddNormal(const Normal& n) { mNormalBuffer_.push_back(n); }
		std::vector<Normal> GetNormalBuffer() const{ return mNormalBuffer_; }
		size_t NormalBufferSize() const { return mNormalBuffer_.size(); }

		void SetTextureCoordBuffer(const std::vector<TextureCoord>& tb) { mTextureCoordBuffer_ = tb; }
		void AddTextureCoord(const TextureCoord& tc) { mTextureCoordBuffer_.push_back(tc); }
		std::vector<TextureCoord> GetTextureCoordBuffer()const { return mTextureCoordBuffer_; }
		size_t TextureCoordBufferSize() const { return mTextureCoordBuffer_.size(); }

		void SetFaceBuffer(const std::vector<Face>& fb) { mFaceBuffer_ = fb; }
		void AddFace(const Face& f) { mFaceBuffer_.push_back(f); }
		std::vector<Face> GetFaceBuffer()const { return mFaceBuffer_; }
		size_t FaceBufferSize() const { return mFaceBuffer_.size(); }

		std::vector<unsigned int> GetIndiceBuffer()const;

		bool IsValid() const { return VertexBufferSize() != 0; }

	private:
		std::string mName_;
		std::string mMtlName_;
		std::vector<Vector3> mVertexBuffer_;
		std::vector<Normal> mNormalBuffer_;
		std::vector<Face> mFaceBuffer_;
		std::vector<TextureCoord> mTextureCoordBuffer_;
	};
}