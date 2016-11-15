/**
 * Building.h
 *
 * Victor Jiao (c) 2016
 */

class Building; 

#ifndef _BUILDING_HXX_
#define _BUILDING_HXX_

#include "Data.h"
#include "Map.h"
#include "Renderer.h"

class BuildingAttr; 

class Building {
public:
	/** this refers to the BuildingAttr corresponding to this building type */
	BuildingAttr* type;
	int xpos;

	void draw(Renderer& r);

	Building(BuildingAttr* t, int x)
		: type(t)
		, xpos(x) { }
};

#endif


