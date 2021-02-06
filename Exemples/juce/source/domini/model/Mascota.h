#pragma once
#include <string>

namespace domini
{
	namespace model
	{
		class Mascota
		{
		public:
			Mascota(const std::string& i_nom);

		private:
			std::string m_nom;
		};
	}
}