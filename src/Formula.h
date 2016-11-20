/*
 *  Formula.h
 *
 *  Victor Jiao (c) 2016
 *
 */

#ifndef _FORMULA_H_
#define _FORMULA_H_ 

#include <algorithm>
#include <map>
#include <string>
#include <vector>

#include "Data.h"

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
	void addIngredient(string d, int c);

	/**
	 * addTool
	 *
	 * adds a tool to the required / optional tool list
	 * 
	 * @param tl tool name
	 */
	void addTool(string tl);
};

/**
 * initFormulas
 *
 * initializes the list of formulas to use
 * 
 * @param formulas the reference to the list of formulas in Map to fill out.
 */
void initFormulas(map<string, Formula> &formulas);

#endif