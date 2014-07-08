/*
 ============================================================================
 Name        : Ships.cpp
 Author      : Sam Berry <berry.sam@gmail.com>
 Version     : 0.1
 Copyright   : © Sam Berry 2013. All Rights Reserved.
 Description : Physics based space shooter.
 ============================================================================
 */

#include "ships.h"

#ifndef DATADIR
#error "No data directory passed to compiler!"
#endif

/*
 * All we need to do here is get a ShipsController class and run it!
 */
int main(void) {
	return ShipsController::GetInstance()->Run();
}
