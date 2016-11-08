#include "Include\Mesh.h"

namespace NaiveZ3D
{
	std::vector<unsigned int> Mesh::GetIndiceBuffer()const
	{
		if (!mIndiceCache_.empty())
		{
			return mIndiceCache_;
		}
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

		mIndiceCache_ = move(indice);
		return mIndiceCache_;
	}
	std::vector<Vector3> Mesh::GetVeretxBuffer()const
	{
		if (!mVertexCache_.empty())
		{
			return mVertexCache_;
		}
		std::vector<Vector3> vertex(mFaceBuffer_.size() * mFaceBuffer_[0].mVertexIndex_.size());
		int index = 0;
		for (const auto& face : mFaceBuffer_)
		{
			for (auto i : face.mVertexIndex_)
			{
				vertex[index++] = mVertexBuffer_[i];
			}
		}
		mVertexCache_ = move(vertex);
		return mVertexCache_;
	}
	std::vector<TextureCoord> Mesh::GetTexCoordBuffer() const
	{
		if (!mTextureCoordCache_.empty())
		{
			return mTextureCoordCache_;
		}
		std::vector<TextureCoord> tex(mFaceBuffer_.size() * mFaceBuffer_[0].mTextureIndex_.size());
		int index = 0;
		for (const auto& face : mFaceBuffer_)
		{
			for (auto i : face.mTextureIndex_)
			{
				tex[index++] = mTextureCoordBuffer_[i];
			}
		}
		mTextureCoordCache_ = move(tex);
		return mTextureCoordCache_;
	}
}