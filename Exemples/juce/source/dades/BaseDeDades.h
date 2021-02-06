#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "domini/model/Persona.h"
#include "domini/model/Mascota.h"


namespace dades
{

	class BaseDeDades
	{
	public:
		static bool ExisteixPersona(std::string i_nom);
		static domini::model::Persona* ObtePersona(std::string i_nom);

		static domini::model::Mascota* CreaMascota(std::string i_nom);
		static domini::model::Persona* CreaPersona(std::string i_nom);

	private:
		static void InicialitzaDadesFalses();

		static bool s_dadesInicialitzades;
		static std::unordered_map<std::string, std::unique_ptr<domini::model::Persona>> s_persones;
		static std::unordered_map<std::string, std::unique_ptr<domini::model::Mascota>> s_mascotes;
	};
}