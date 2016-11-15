/*
 *  Formula.cpp
 *
 *  Victor Jiao (c) 2016
 *
 */

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "Data.h"

using namespace std;

/**
 * Formula
 *
 * Each formula is a relationship between different materials
 * I.e. you can use wood to make poles
 */
class Formula {
public:
	string target;
	int amt;
	vector<string> tools;
	vector<pair<string, int> > recipe;

	int AHLH; // Average Human Labor Hours

	Formula(string t, int c, string tl, int ahlh)
		: target(t)
		, amt(c)
		, AHLH(ahlh) {
		if (tl.size() > 0) {
			tools.push_back(tl);
		}
	}

	Formula(string t, int c, int ahlh) : Formula(t, c, "", ahlh) {}
	Formula(string t, int c) : Formula(t, c, "", 0) {}
	Formula(string t) : Formula(t, 1, "", 0) {}

	/**
	 * addIngredient
	 *
	 * adds an ingredient to the ingredient list
	 * 
	 * @param d ingredient name
	 * @param c ingredient amount
	 */
	void addIngredient(string d, int c) {
		for (auto it = recipe.begin(); it != recipe.end(); it++) {
			if (it->first == d) {
				it->second += c;

				return;
			}
		}

		recipe.push_back(make_pair(d, c));
	}

	/**
	 * addTool
	 *
	 * adds a tool to the required / optional tool list
	 * 
	 * @param tl tool name
	 */
	void addTool(string tl) {
		tools.push_back(tl);
	}
};

/**
 * initFormulas
 *
 * initializes the list of formulas to use
 * 
 * @param formulas the reference to the list of formulas in Map to fill out.
 */
void initFormulas(map<string, Formula> &formulas) {
	Formula pole("pole", 5, 3);
		pole.addIngredient("wood", 1);

	Formula crafts("crafts", 5, 20);
		crafts.addIngredient("wood", 1);
		crafts.addTool("stone");
		crafts.addTool("spearhead");

	Formula spearhead("spearhead", 2, 3);
		spearhead.addIngredient("stone", 2);

	Formula flour("flour", 1, 3);
		flour.addIngredient("grain", 5);

	Formula cooked_meat("cooked_meat", 1, 2);
		cooked_meat.addIngredient("meat", 1);
		cooked_meat.addIngredient("wood", 1);

	Formula bread("bread", 1, 5);
		bread.addIngredient("flour", 1);
		bread.addIngredient("water", 1);
		bread.addTool("pot");
		bread.addTool("stone");

	Formula pot("pot", 1, 3);
		pot.addIngredient("clay", 3);
		pot.addTool("stone");

	Formula spear("spear", 1, 2);
		spear.addIngredient("pole", 1);
		spear.addIngredient("spearhead", 1);

	Formula axe("axe", 1, 2);
		axe.addIngredient("pole", 1);
		axe.addIngredient("stone", 1);
		axe.addTool("stone");	

	Formula basket("basket", 1, 15);
		basket.addIngredient("hay", 20);

	Formula hoe("hoe", 1, 2);
		hoe.addIngredient("stone", 1);
		hoe.addIngredient("pole", 1);
}

