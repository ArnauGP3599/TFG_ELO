#pragma once
class Property
{
public:
	Property(const char* i_name);

	inline void setName(const char* i_name) {
		m_name = i_name;
	}
	inline const char* getName() {
		return m_name;
	}
private:
	const char* m_name;
};

