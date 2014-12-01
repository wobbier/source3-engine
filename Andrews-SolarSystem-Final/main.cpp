#include "Windows.h"
#include "Source3.h"
#include "SolarSystem.h"

int main() {
	SolarSystem* system = new SolarSystem();
	system->Start();
	return 0;
}