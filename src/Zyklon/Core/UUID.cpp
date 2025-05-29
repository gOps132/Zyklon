#include <zyklon_pch.h>

#include "UUID.h"

namespace Zyklon 
{
	static std::random_device s_random_device;
	static std::mt19937_64 s_engine(s_random_device());
	static std::uniform_int_distribution<uint64_t> s_uniform_distribution;

	UUID::UUID() 
		: m_UUID(s_uniform_distribution(s_engine))
	{
		
	}

	UUID::UUID(uint64_t p_uuid)
		: m_UUID(p_uuid)
	{

	}
} // namespace Zyklon