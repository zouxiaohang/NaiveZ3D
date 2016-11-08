#pragma once

#include <string>
#include <map>
#include <memory>

#include "../../../Math/Include/Vector.h"
#include "Texture.h"

namespace NaiveZ3D
{
	using TexturePtr = std::unique_ptr<Texture>;

	struct MtlData
	{
		MtlData()
		{
			Clear();
		}
		void Clear()
		{
			useNs_ = false;
			useKa_ = false;
			useKd_ = false;
			useKs_ = false;
			useKe_ = false;
			useNi_ = false;
			used_ = false;
			useillum_ = false;
			newmtl_ = "";
			map_Kd_ = "";
			map_Bump_ = "";
			map_Ke_ = "";
			map_Ks_ = "";
			refl_ = "";
			KdTexPtr_.reset();
			BumpTexPtr_.reset();
			KeTexPtr_.reset();
			KsTexPtr_.reset();
			reflTexPtr_.reset();
		}
		std::string newmtl_;
		float Ns_;	//反射指数exponent
		Vector3 Ka_;//环境反射
		Vector3 Kd_;//漫反射
		Vector3 Ks_;//镜反射
		Vector3 Ke_;
		float Ni_;	//折射值,可在0.001到10之间进行取值。若取值为1.0，光在通过物体的时候不发生弯曲。
		float d_;	//渐隐指数,取值范围为0.0~1.0，取值为1.0表示完全不透明，取值为0.0时表示完全透明
		int illum_;	//材质的光照模型,illum后面可接0~10范围内的数字参数。各个参数代表的光照模型如下所示
					//0 Color on and Ambient off
					//1 Color on and Ambient on
					//2 Highlight on
					//3 Reflection on and Ray trace on
					//4 Transparency: Glass on Reflection : Ray trace on
					//5 Reflection : Fresnel on and Ray trace on
					//6 Transparency : Refraction on Reflection : Fresnel off and Ray trace on
					//7 Transparency : Refraction on Reflection : Fresnel on and Ray trace on
					//8 Reflection on and Ray trace off
					//9 Transparency : Glass on Reflection : Ray trace off
					//10 Casts shadows onto invisible surfaces
		std::string map_Kd_;
		TexturePtr	KdTexPtr_;
		std::string map_Bump_;
		TexturePtr  BumpTexPtr_;
		std::string map_Ke_;
		TexturePtr	KeTexPtr_;
		std::string map_Ks_;
		TexturePtr	KsTexPtr_;
		std::string refl_;
		TexturePtr	reflTexPtr_;

		bool useNs_;
		bool useKa_;
		bool useKd_;
		bool useKs_;
		bool useKe_;
		bool useNi_;
		bool used_;
		bool useillum_;
	};

	class MTL{};

	class Material : public MTL
	{
	public:
		Material(){}
		Material(const std::string& name);

		void AddMtlData(MtlData&& data);

		std::string GetName()const { return mName_; }

	private:
		std::string mName_;//mtl name
		std::map<std::string, MtlData> mMtlDataMap_;
	};
}