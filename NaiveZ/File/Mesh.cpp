#include "Include\Mesh.h"

namespace NaiveZ3D
{
	Mesh::Mesh(const std::string& mtl, std::vector<Vector3>&& vertexBuffer, std::vector<UINT32>&& indiceBuffer)
		:mMtlName_(mtl),
		mVertexBuffer_(vertexBuffer),
		mIndiceBuffer_(indiceBuffer)
	{}
}