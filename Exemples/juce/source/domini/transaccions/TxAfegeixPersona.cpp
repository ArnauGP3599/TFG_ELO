#include "TxAfegeixPersona.h"
#include "domini/Excepcions.h"
#include "dades/BaseDeDades.h"

namespace domini
{

	TxAfegirPersona::TxAfegirPersona(const std::string& i_nom)
	{
		m_nom = i_nom;
	}

	void TxAfegirPersona::Executar()
	{
		if (dades::BaseDeDades::ExisteixPersona(m_nom))
		{
			throw PersonaJaExisteix();
		}
		else
		{
			model::Persona* novaPersona = dades::BaseDeDades::CreaPersona(m_nom);
		}
	}
}

