/**
 * Scenery.h
 *
 * Victor Jiao (c) 2016
 */

class Scenery;

#ifndef _SCENERY_HXX_
#define _SCENERY_HXX_

#include "Data.h"
#include "Map.h"
#include "Renderer.h"

class SceneryAttr;

/**
 * Scenery
 *
 * This is the scenery objects
 */
class Scenery {
public:
	/** this refers to the corresponding SceneryAttr */
	SceneryAttr* type;
	int xpos;

	void draw(Renderer& r);

	Scenery(SceneryAttr* t, int x)
		: type(t)
		, xpos(x) { }
};

#endif