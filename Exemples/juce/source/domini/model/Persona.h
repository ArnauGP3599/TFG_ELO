#pragma once
#include <unordered_set>
#include <string>
namespace domini
{
	namespace model
	{
		class Mascota;

		class Persona
		{
		public:
			Persona(std::string i_nom, std::unordered_set<Mascota*> i_mascotes);
			Persona(std::string i_nom);
			Persona();

			void SetNom(std::string i_nom);
			std::string GetNom() const;

			void AfegeixMascota(Mascota* i_mascota);

		private:
			std::string m_nom;
			std::unordered_set<Mascota*> m_mascotes;
		};
	}
}