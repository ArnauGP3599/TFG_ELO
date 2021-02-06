#pragma once
#include <exception>

namespace dades
{
	class PersonaNoExisteix : public std::exception {};
}