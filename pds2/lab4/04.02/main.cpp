#include "fleet.h"
#include <string>
#include <vector>

int main() {

    int number_of_planes = 8;

	Fleet *fleet = new Fleet();
	std::vector<Aeroplane*> plane_fleet = fleet->instantiate_fleet(number_of_planes);
	fleet->print_fleet_data(plane_fleet);
	
	delete fleet;

	for (int i = 0; i < number_of_planes; i++) {
		if (plane_fleet[i] != nullptr){
			delete plane_fleet[i];
		}
	}
}
