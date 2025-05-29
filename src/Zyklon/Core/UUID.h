#ifndef __UUID_H__
#define __UUID_H__

namespace Zyklon {
class UUID 
{
public:
	UUID();
	UUID(uint64_t p_uuid);
	UUID(const UUID&) = default;

	operator uint64_t() const { return m_UUID; }
private:
	uint64_t m_UUID;
};
}

// custom std::hash template to handle type zyklon::uuid
namespace std 
{
	template <typename T> struct hash;

	template<>
	struct hash<Zyklon::UUID>
	{
		std::size_t operator()(const Zyklon::UUID& uuid) const
		{
			return (uint64_t)uuid;
		}
	};

}

#endif // __UUID_H__