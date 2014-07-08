
#include "shipsviews.h"


ShipView::ShipView() {
	std::cout << "Calling ShipView constructor\n";
	this->LoadObject("shipper.obj");

}

ShipView::~ShipView() {

}

