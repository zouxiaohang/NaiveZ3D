#pragma once

#include <vector>

#include "../../Math/Include/Vector.h"
#include "../../Utils/Include/Constant.h"
#include "Face.h"

namespace NaiveZ3D
{
	class Model;

	class Mesh
	{
	public:
		void SetName(const std::string& name) { mName_ = name; }
		std::string GetName()const { return mName_; }

		void SetMtl(const std::string& mtl) { mMtlName_ = mtl; }
		std::string GetMtl()const { return mMtlName_; }

		//void SetVertexBuffer(const std::vector<Vector3>& vb) { mVertexBuffer_ = vb; }
		//void AddVertex(const Vector3& v) { mVertexBuffer_.push_back(v); }
		//const std::vector<Vector3>& GetVertexBuffer() const{ return mVertexBuffer_; }
		//size_t VertexBufferSize() const { return mVertexBuffer_.size(); }

		//void SetNormalBuffer(const std::vector<Normal>& nb) { mNormalBuffer_ = nb; }
		//void AddNormal(const Normal& n) { mNormalBuffer_.push_back(n); }
		//const std::vector<Normal>& GetNormalBuffer() const{ return mNormalBuffer_; }
		//size_t NormalBufferSize() const { return mNormalBuffer_.size(); }

		//void SetTextureCoordBuffer(const std::vector<TextureCoord>& tb) { mTextureCoordBuffer_ = tb; }
		//void AddTextureCoord(const TextureCoord& tc) { mTextureCoordBuffer_.push_back(tc); }
		//const std::vector<TextureCoord>& GetTextureCoordBuffer()const { return mTextureCoordBuffer_; }
		//size_t TextureCoordBufferSize() const { return mTextureCoordBuffer_.size(); }

		void SetFaceBuffer(const std::vector<Face>& fb) { mFaceBuffer_ = fb; }
		void AddFace(const Face& f) { mFaceBuffer_.push_back(f); }
		const std::vector<Face>& GetFaceBuffer()const { return mFaceBuffer_; }
		size_t FaceBufferSize() const { return mFaceBuffer_.size(); }

		//下面三个函数是将Mesh内的数据变换为Opengl绘制所需的数据
		const std::vector<unsigned int>& GenIndiceBuffer(const Model&)const;
		const std::vector<Vector3>& GenVertexBuffer(const Model&)const;
		const std::vector<TextureCoord>& GenTexCoordBuffer(const Model&)const;

	private:
		//由于使用了纹理，因此一次性生成全部数据，并缓存
		void BuildDataUseTex(const Model& model)const;

	private:
		std::string mName_;
		std::string mMtlName_;
		std::vector<Face> mFaceBuffer_;

		//std::vector<Vector3> mVertexBuffer_;
		//std::vector<Normal> mNormalBuffer_;
		//std::vector<TextureCoord> mTextureCoordBuffer_;

		mutable std::vector<Vector3> mVertexCache_;//缓存
		mutable std::vector<unsigned int> mIndiceCache_;//缓存
		mutable std::vector<TextureCoord> mTextureCoordCache_;//缓存
		mutable std::vector<Vector3> mNormalCache_;//缓存
	};
}