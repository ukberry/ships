
#include "shipsviews.h"


ShipView::ShipView() {
	std::cout << "Calling ShipView constructor\n";
	this->LoadObject("data/shipper.obj");

}

ShipView::~ShipView() {

}

