#pragma once

#include <map>
#include <string>
#include <tuple>

#include "Material.h"

namespace NaiveZ3D
{
	using MaterialCache = std::map<std::string, Material>;
	using ImageDataCache = std::map<std::string, std::tuple<unsigned char*, GLint, GLint>>;

	class MaterialMgr
	{
	public:
		static MaterialMgr& Instance();
		void Init();

		void LoadMtl(const std::string& mtlName);
		Material& GetMaterial(const std::string& mtl);

		bool HasImageData(const std::string&)const;
		const std::tuple<unsigned char*, GLint, GLint>& GetImageData(const std::string&)const;
		void AddImageData(const std::string&, unsigned char*, GLint, GLint);

	private:
		MaterialMgr()
			:mInited_(false)
		{}
		MaterialMgr(const MaterialMgr&);
		~MaterialMgr() { ClearImageDataCache(); }

		void AddMaterial(Material &&m);
		void ClearImageDataCache();

	private:
		bool mInited_;
		MaterialCache mMaterialCache_;
		ImageDataCache mImageDataCache_;
	};
}