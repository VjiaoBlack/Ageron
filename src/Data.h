/*
 *  Data.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <vector>
#include <map>
#include <string>

#ifndef _DATA_HXX_
#define _DATA_HXX_

// AHLH: Average Human Labor Hours

using namespace std;

class DataAttr {
public:
	string name;
};

class BuildingAttr : DataAttr {
public:
	string name;
	int width;
	int height;
	int area;
	int AHLH;

	BuildingAttr(string name, int width, int height, 
				 int area, int AHLH)
		: name(name)
		, width(width)
		, height(height)
		, area(area)
		, AHLH(AHLH) {}
	BuildingAttr() : BuildingAttr("", 0, 0, 0, 0) {}

	vector<pair<string, int>> materials;
};

void initBuildingAttrs(map<string, BuildingAttr*> &attrs);

class SceneryAttr : DataAttr {
public:
	string name;
	int width;
	int height;
	vector<pair<string, int> > resources; 
	int AHLH;

	SceneryAttr(string n, int w, int h, int lh) 
		: name(n)
		, width(w)
		, height(h)
		, AHLH(lh) {}

	void addResource(string s, int a) {
		resources.push_back(make_pair(s, a));
	}
};

void initSceneryAttrs(map<string, SceneryAttr*> &attrs);

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

void initJobAttrs(map<string, JobAttr*> &attrs);

class MaterialAttr : DataAttr {
public:
	string name;
	double value;

	MaterialAttr(string name, double value)
		: name(name)
		, value(value) {}
	MaterialAttr() : MaterialAttr("", 0) {}
};

void initMaterialAttrs(map<string, MaterialAttr*> &attrs);

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

void initFoodAttrs(map<string, FoodAttr*> &attrs);

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

void initToolAttrs(map<string, ToolAttr*> &attrs);

#endif