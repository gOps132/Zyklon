#ifndef __TIMESTEP_H__
#define __TIMESTEP_H__

namespace Zyklon
{

class Timestep
{
public:	
	Timestep(float p_time = 0.0f) 
		: m_time(p_time) 
	{};

	operator float() { return m_time; }
	
	float getSeconds() { return m_time; }
	float getMilliseconds() { return m_time * 1000.0f; }

private:
	float m_time;
};

} // namespace Zyklon

#endif // __TIMESTEP_H__