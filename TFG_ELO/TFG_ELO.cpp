#include <iostream>
#include "Precompiled.h"
#include "Simulation.h"

int main()
{
    shared_ptr<Simulation> sim = make_shared<Simulation>();
    sim->init();
}


