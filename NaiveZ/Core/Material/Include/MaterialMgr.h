#pragma once

#include <map>
#include <string>

#include "Material.h"

namespace NaiveZ3D
{
	using MaterialCache = std::map<std::string, Material>;

	class MaterialMgr
	{
	public:
		static MaterialMgr& Instance();
		void Init();

		void LoadMtl(const std::string& mtlName);
		Material& GetMaterial(const std::string& mtl);

	private:
		MaterialMgr()
			:mInited_(false)
		{}
		MaterialMgr(const MaterialMgr&);

	private:
		bool mInited_;

		MaterialCache mMaterialCache_;
	};
}