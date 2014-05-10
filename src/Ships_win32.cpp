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

#include <windows.h>
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int iShow) {
	return ShipsController::GetInstance()->Run();
}
