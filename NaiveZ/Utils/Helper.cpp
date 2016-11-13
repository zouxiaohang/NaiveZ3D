#include "Include\Helper.h"

std::vector<std::string> NaiveZ3D::Helper::Split(const std::string & msg, const std::string & delimiter)
{
	std::vector<std::string> ret;
	size_t prev = 0, step = delimiter.size();
	auto curr = msg.find(delimiter);
	while (curr != std::string::npos)
	{
		ret.emplace_back(msg.substr(prev, curr - prev));
		prev = curr + step;
		curr = msg.find(delimiter, prev);
	}
	ret.emplace_back(msg.substr(prev, msg.size() - prev));
	return ret;
}
