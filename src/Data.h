/**
 * Data.h
 *
 * Victor Jiao (c) 2016
 */

#ifndef _DATA_HXX_
#define _DATA_HXX_

#include <map>
#include <string>
#include <vector>

#include "Renderer.h"



using namespace std;

/**
 * DataAttr
 *
 * The parent class for object-attribute storage classes
 */
class DataAttr {
public:
	string name;
};

/**
 * BuildingAttr
 *
 * Stores attributes of all building types
 *
 * @param area   measures space inside building
 */
class BuildingAttr : DataAttr {
public:
	string name;	
	int width;
	int height;		
	int area;		
	int AHLH;		// Average Human Labor Hours
	SDL_Texture* texture = NULL;

	BuildingAttr(string name, int width, int height, 
				 int area, int AHLH)
		: name(name)
		, width(width)
		, height(height)
		, area(area)
		, AHLH(AHLH) {}
	BuildingAttr() : BuildingAttr("", 0, 0, 0, 0) {}

	/** the list of building materials */
	vector<pair<string, int>> materials;
};

/**
 * initBuildingAttrs
 * 
 * Initializes data for all buildings
 * 
 * @param r     The current renderer in use by Game
 * @param attrs The Game's map that will store the data
 */
void initBuildingAttrs(Renderer& r, map<string, BuildingAttr*> &attrs);

/**
 * SceneryAttr
 *
 * Stores all of the scenery item attributes
 *
 * @param resources	  the resources stored in this scenery
 */
class SceneryAttr : DataAttr {
public:
	string name;
	int width;
	int height;
	vector<pair<string, int> > resources; 
	int AHLH;
	SDL_Texture* texture = NULL;

	SceneryAttr(string n, int w, int h, int lh) 
		: name(n)
		, width(w)
		, height(h)
		, AHLH(lh) {}

	void addResource(string s, int a) {
		resources.push_back(make_pair(s, a));
	}
};

/**
 * initScenery
 * 
 * Initializes data for all scenery items
 * 
 * @param r     The current renderer in use by Game
 * @param attrs The Game's map that will store the data
 */
void initSceneryAttrs(Renderer& r, map<string, SceneryAttr*> &attrs);

/**
 * JobAttr
 *
 * Stores attributes and effects of different jobs
 */
class JobAttr : DataAttr {
public:
	string name;
	int training_time;
	vector<pair<string, double>> bonuses;

	JobAttr(string name, int training_time)
		: name(name) 
		, training_time(training_time) {}
	JobAttr() : JobAttr("", 0) {}
};

/**
 * initJobAttrs
 * 
 * Initializes data for all job types
 * 
 * @param r     The current renderer in use by Game
 * @param attrs The Game's map that will store the data
 */
void initJobAttrs(Renderer& r, map<string, JobAttr*> &attrs);

/**
 * MaterialAttr
 *
 * Stores attributes of materials
 */
class MaterialAttr : DataAttr {
public:
	string name;
	double value;

	MaterialAttr(string name, double value)
		: name(name)
		, value(value) {}
	MaterialAttr() : MaterialAttr("", 0) {}
};

/**
 * initMaterialAttrs
 * 
 * Initializes data for all materials
 * 
 * @param r     The current renderer in use by Game
 * @param attrs The Game's map that will store the data
 */
void initMaterialAttrs(Renderer& r, map<string, MaterialAttr*> &attrs);

/**
 * FoodAttr
 *
 * stores attributes about food
 */
class FoodAttr : DataAttr {
public:
	string name;
	int restoration;
	int value;

	FoodAttr(string name, int restoration)
		: name(name)
		, restoration(restoration) {}
	FoodAttr() : FoodAttr("", 0) {}
};

/**
 * initFoodAttrs
 * 
 * Initializes data for all food items
 * 
 * @param r     The current renderer in use by Game
 * @param attrs The Game's map that will store the data
 */
void initFoodAttrs(Renderer& r, map<string, FoodAttr*> &attrs);

/**
 * ToolAttr
 *
 * stores attributes about tools
 */
class ToolAttr : DataAttr {
public:
	string name;
	int value;
	vector<pair<string, double>> bonuses;

	ToolAttr(string name, int value) 
		: name(name)
		, value(value) {}
	ToolAttr() : ToolAttr("", 0) {}
};

/**
 * initToolAttrs
 * 
 * Initializes data for all tools
 * 
 * @param r     The current renderer in use by Game
 * @param attrs The Game's map that will store the data
 */
void initToolAttrs(Renderer& r, map<string, ToolAttr*> &attrs);

#endif
