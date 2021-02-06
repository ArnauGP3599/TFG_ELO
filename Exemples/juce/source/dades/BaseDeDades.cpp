#include "BaseDeDades.h"
#include "Excepcions.h"

namespace dades
{
	std::unordered_map<std::string, std::unique_ptr<domini::model::Persona>> BaseDeDades::s_persones;
	std::unordered_map<std::string, std::unique_ptr<domini::model::Mascota>> BaseDeDades::s_mascotes;
	bool BaseDeDades::s_dadesInicialitzades = false;

	bool BaseDeDades::ExisteixPersona(std::string i_nom)
	{
		InicialitzaDadesFalses();
		return s_persones.find(i_nom) != s_persones.end();
	}

	domini::model::Persona* BaseDeDades::ObtePersona(std::string i_nom)
	{
		InicialitzaDadesFalses();
		auto it = s_persones.find(i_nom);
		if (it == s_persones.end())
		{
			throw PersonaNoExisteix();
		}
		else
		{
			return it->second.get();
		}
	}

	void BaseDeDades::InicialitzaDadesFalses()
	{
		if (s_dadesInicialitzades == true)
		{
			return;
		}
		else
		{
			domini::model::Mascota* nix = CreaMascota("Nix");
			domini::model::Persona* persona = CreaPersona("Manel");
			persona->AfegeixMascota(nix);
			s_dadesInicialitzades = true;
		}
	}

	domini::model::Mascota* BaseDeDades::CreaMascota(std::string i_nom)
	{
		std::unique_ptr<domini::model::Mascota> mascota = std::make_unique<domini::model::Mascota>(i_nom);
		domini::model::Mascota* mascotaRef = mascota.get();
		s_mascotes.emplace(i_nom, std::move(mascota));
		return mascotaRef;
	}

	domini::model::Persona* BaseDeDades::CreaPersona(std::string i_nom)
	{
		std::unique_ptr<domini::model::Persona> persona = std::make_unique<domini::model::Persona>(i_nom);
		domini::model::Persona* personaRef = persona.get();
		s_persones.emplace(i_nom, std::move(persona));
		return personaRef;
	}



}