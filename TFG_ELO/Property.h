#pragma once
class Property
{
public:
	Property(string i_name);

	inline void setName(string i_name) {
		m_name = i_name;
	}
	inline string getName() {
		return m_name;
	}
private:
	string m_name;
};

