#pragma once
#include <string>
#include "Transaccio.h"

namespace domini
{
	class TxAfegirPersona: public Transaccio
	{
	public:
		TxAfegirPersona(const std::string& i_nom);
		//Pot llen�ar:
		//domini::PersonaJaExisteix
		void Executar() override;

	private:
		std::string m_nom;
	};
}