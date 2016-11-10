/*
 *  Building.h
 *
 *  Victor Jiao (c) 2016
 *
 */

class Building; 

#ifndef _BUILDING_HXX_
#define _BUILDING_HXX_

#include "Renderer.h"
#include "Data.h"
#include "Map.h"

class Building {
public:
	// this refers to the corresponding SceneryAttr
	BuildingAttr* type;
	int xpos;

	void draw(Renderer& r);

	Building(BuildingAttr* t, int x)
		: type(t)
		, xpos(x) { }
};

#endif


