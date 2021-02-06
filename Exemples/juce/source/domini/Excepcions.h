#pragma once
#include <exception>

namespace domini
{
	class PersonaNoExisteix : public std::exception {};
	class PersonaJaExisteix : public std::exception {};
}