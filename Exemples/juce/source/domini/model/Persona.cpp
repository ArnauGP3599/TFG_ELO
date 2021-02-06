#include "Persona.h"

namespace domini
{
	namespace model
	{
		Persona::Persona(std::string i_nom, std::unordered_set<Mascota*> i_mascotes)
		{
			m_nom = i_nom;
			m_mascotes = i_mascotes;
		}

		Persona::Persona(std::string i_nom)
		{
			m_nom = i_nom;
		}

		Persona::Persona()
		{

		}

		void Persona::SetNom(std::string i_nom)
		{
			m_nom = i_nom;
		}

		std::string Persona::GetNom() const
		{
			return m_nom;
		}
		void Persona::AfegeixMascota(Mascota* i_mascota)
		{
			m_mascotes.emplace(i_mascota);
		}
	}
}