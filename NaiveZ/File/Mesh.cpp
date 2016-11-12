#include <set>
#include <string>
using namespace std;

#include "Include\Mesh.h"
#include "Include\Model.h"

namespace
{
	struct record
	{
		int v, t, n;
		record() {}
		string toString() { return to_string(v) + '/' + to_string(t) + '/' + to_string(n); }
	};
}

namespace NaiveZ3D
{
	const std::vector<unsigned int>& Mesh::GenIndiceBuffer(const Model& model)const
	{
		if (!mIndiceCache_.empty())
		{
			return mIndiceCache_;
		}
		std::vector<unsigned int> indice;
		if (!model.UseTex())//音聞喘瞭尖
		{
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
		}
		else
		{
			BuildDataUseTex(model);
		}
		
		return mIndiceCache_;
	}
	const std::vector<Vector3>& Mesh::GenVertexBuffer(const Model& model)const
	{
		if (!model.UseTex())
		{
			return model.GetVertexBuffer();
		}

		if (!mVertexCache_.empty())
		{
			return mVertexCache_;
		}
		BuildDataUseTex(model);
		return mVertexCache_;
	}
	const std::vector<TextureCoord>& Mesh::GenTexCoordBuffer(const Model& model) const
	{
		if (!mTextureCoordCache_.empty())
		{
			return mTextureCoordCache_;
		}
		if (!model.UseTex())
		{
			mTextureCoordCache_.resize(model.GetVertexBuffer().size());
		}
		else
		{
			BuildDataUseTex(model);
		}
		return mTextureCoordCache_;
	}
	const std::vector<Vector3>& Mesh::GenNormalBuffer(const Model &model) const
	{
		if (!mNormalCache_.empty())
		{
			return mNormalCache_;
		}
		if (!model.UseTex())
		{
			mNormalCache_.resize(model.GetVertexBuffer().size());
		}
		else
		{
			BuildDataUseTex(model);
		}
		return mNormalCache_;
	}
	void Mesh::BuildDataUseTex(const Model& model)const
	{
		//create vertex data
		std::vector<int> vi, ti, ni;
		record r;
		auto& buildMap = model.GetBuildMap();
		auto& re = model.GetRecord();
		int index4[6] = { 0,1,2,0,2,3 };

		for (const auto& face : mFaceBuffer_)
		{
			const auto& vb = face.mVertexIndex_;
			const auto& tb = face.mTextureIndex_;
			const auto& nb = face.mNormalIndex_;
			int v, t, n;
			if (vb.size() == 3)
			{
				for (auto i = 0; i != vb.size(); ++i)
				{
					v = vb[i]; t = tb[i]; n = nb[i];
					r.v = v; r.t = t; r.n = n;
					auto rs = r.toString();
					//create indice
					if(!model.HasIndice(rs))
					{
						buildMap[rs] = re;
						mIndiceCache_.push_back(re);
						++re;
						vi.emplace_back(v);
						ti.emplace_back(t);
						ni.emplace_back(n);
					}
					else
					{
						mIndiceCache_.push_back(buildMap[rs]);
					}
				}
			}
			else if (vb.size() == 4)
			{
				//1、2、3
				//1、3、4
				for (auto i : index4)
				{
					v = vb[i]; t = tb[i]; n = nb[i];
					r.v = v; r.t = t; r.n = n;
					auto rs = r.toString();
					//create indice
					if (!model.HasIndice(rs))
					{
						buildMap[rs] = re;
						mIndiceCache_.push_back(re);
						++re;
						vi.emplace_back(v);
						ti.emplace_back(t);
						ni.emplace_back(n);
					}
					else
					{
						mIndiceCache_.push_back(buildMap[rs]);
					}
				}
			}
		}
		mVertexCache_.resize(vi.size());
		mTextureCoordCache_.resize(ti.size());
		mNormalCache_.resize(ni.size());
		const auto& vb = model.GetVertexBuffer();
		const auto& tb = model.GetTextureCoordBuffer();
		const auto& nb = model.GetNormalBuffer();
		for (auto i = 0; i != vi.size(); ++i)
		{
			mVertexCache_[i] = vb[vi[i]];
			mTextureCoordCache_[i] = tb[ti[i]];
			mNormalCache_[i] = nb[ni[i]];
		}
	}
}