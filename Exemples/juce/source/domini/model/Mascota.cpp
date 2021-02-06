#include "Mascota.h"

namespace domini
{
	namespace model
	{
		Mascota::Mascota(const std::string& i_nom)
		{
			//Això no s'hauria de fer així òptimament, però és per temes didàctics
			m_nom = i_nom;
		}
	}
}