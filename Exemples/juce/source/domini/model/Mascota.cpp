#include "Mascota.h"

namespace domini
{
	namespace model
	{
		Mascota::Mascota(const std::string& i_nom)
		{
			//Aix� no s'hauria de fer aix� �ptimament, per� �s per temes did�ctics
			m_nom = i_nom;
		}
	}
}