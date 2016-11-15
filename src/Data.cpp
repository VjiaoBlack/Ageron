/**
 * Data.cpp
 *
 * Victor Jiao (c) 2016
 */

#include "Data.h"

using namespace std;

void initBuildingAttrs(Renderer& r, map<string, BuildingAttr*> &attrs) {
	BuildingAttr* tent = new BuildingAttr("tent", 2, 3, 3, 2);
	tent->materials.push_back(make_pair("wood", 2));
	tent->materials.push_back(make_pair("leather", 3));

	BuildingAttr* lean_to = new BuildingAttr("lean-to", 3, 3, 4, 10);
	lean_to->materials.push_back(make_pair("wood", 6));
	lean_to->materials.push_back(make_pair("hay", 10));

	BuildingAttr* hut = new BuildingAttr("hut", 4, 3, 7, 30);
	hut->materials.push_back(make_pair("wood", 20));

	attrs["tent"] = tent;
	attrs["lean-to"] = lean_to;
	attrs["hut"] = hut;
}

void initSceneryAttrs(Renderer& r, map<string, SceneryAttr*> &attrs) {
	SceneryAttr* tree = new SceneryAttr("tree", 5, 8, 3);
	tree->addResource("wood", 10);
	tree->texture = r.loadSurface("res/tileset/tree.png");

	SceneryAttr* berry_bush = new SceneryAttr("berry_bush", 2, 2, 1);
	berry_bush->addResource("berry", 10);
	berry_bush->texture = r.loadSurface("res/tileset/berry_bush.png");

	SceneryAttr* dead_tree = new SceneryAttr("dead_tree", 4, 7, 2);
	dead_tree->addResource("wood", 2);
	dead_tree->texture = r.loadSurface("res/tileset/dead_tree.png");

	SceneryAttr* flower = new SceneryAttr("flower", 1, 2, 0);
	flower->texture = r.loadSurface("res/tileset/flower.png");

	attrs["tree"] = tree;
	attrs["berry_bush"] = berry_bush;
	attrs["dead_tree"] = dead_tree;
	attrs["flower"] = flower;
}

void initJobAttrs(Renderer& r, map<string, JobAttr*> &attrs) {
	JobAttr* gatherer = new JobAttr("gatherer", 6);
	gatherer->bonuses.push_back(make_pair("foraging", 2.0));
	gatherer->bonuses.push_back(make_pair("scavenging", 3.0));

	JobAttr* farmer = new JobAttr("farmer", 10);
	farmer->bonuses.push_back(make_pair("farming", 1.5));
	farmer->bonuses.push_back(make_pair("labor", 1.2));

	JobAttr* hunter = new JobAttr("hunter", 40);
	hunter->bonuses.push_back(make_pair("hunting", 4));
	hunter->bonuses.push_back(make_pair("spear", 3));

	JobAttr* craftsman = new JobAttr("craftsman", 25);
	craftsman->bonuses.push_back(make_pair("construction", 1.5));
	craftsman->bonuses.push_back(make_pair("crafts", 3));

	JobAttr* woodcutter = new JobAttr("woodcutter", 15);
	woodcutter->bonuses.push_back(make_pair("woodcutting", 2));
	woodcutter->bonuses.push_back(make_pair("axe", 3));

	attrs["gatherer"] = gatherer;
	attrs["farmer"] = farmer;
	attrs["hunter"] = hunter;
	attrs["craftsman"] = craftsman;
	attrs["woodcutter"] = woodcutter;
}

void initMaterialAttrs(Renderer& r, map<string, MaterialAttr*> &attrs) {
	MaterialAttr* hay = new MaterialAttr("hay", .5);
	MaterialAttr* wood = new MaterialAttr("wood", 1);
	MaterialAttr* stone = new MaterialAttr("stone", .5);
	MaterialAttr* pole = new MaterialAttr("pole", 1);
	MaterialAttr* crafts = new MaterialAttr("crafts", 10);
	MaterialAttr* spearhead = new MaterialAttr("spearhead", 1);
	MaterialAttr* clay = new MaterialAttr("clay", .3);
	MaterialAttr* water = new MaterialAttr("water", .3);
	MaterialAttr* grain = new MaterialAttr("grain", 3);
	MaterialAttr* flour = new MaterialAttr("flour", 15);
	MaterialAttr* leather = new MaterialAttr("leather", 20);

	attrs["hay"] = hay;
	attrs["wood"] = wood;
	attrs["stone"] = stone;
	attrs["pole"] = pole;
	attrs["crafts"] = crafts;
	attrs["spearhead"] = spearhead;
	attrs["clay"] = clay;
	attrs["water"] = water;
	attrs["grain"] = grain;
	attrs["flour"] = flour;
	attrs["leather"] = leather;
}

void initFoodAttrs(Renderer& r, map<string, FoodAttr*> &attrs) {
	FoodAttr* meat = new FoodAttr("meat", 8);
	FoodAttr* cooked_meat = new FoodAttr("cooked_meat", 15);
	FoodAttr* berries = new FoodAttr("berries", 3);
	FoodAttr* fruits = new FoodAttr("fruits", 3);
	FoodAttr* bread = new FoodAttr("bread", 10);

	attrs["meat"] = meat;
	attrs["cooked_meat"] = cooked_meat;
	attrs["berries"] = berries;
	attrs["fruits"] = fruits;
	attrs["bread"] = bread;

}

void initToolAttrs(Renderer& r, map<string, ToolAttr*> &attrs) {
	ToolAttr* pot = new ToolAttr("pot", 40);
	ToolAttr* spear = new ToolAttr("spear", 50);
	ToolAttr* axe = new ToolAttr("axe", 30);
	ToolAttr* basket = new ToolAttr("basket", 30);
	ToolAttr* hoe = new ToolAttr("hoe", 20);

	attrs["pot"] = pot;
	attrs["spear"] = spear;
	attrs["axe"] = axe;
	attrs["basket"] = basket;
	attrs["hoe"] = hoe;
}
