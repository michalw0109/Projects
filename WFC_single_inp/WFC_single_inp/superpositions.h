#pragma once
#include "functions.h"
#include "pix_set.h"
#include "rules.h"

class superpositions
{
private:
	vector<vector<vector<int>>> arr;
	vector<vector<bool>> collapsed;
	int section_size;
	int max_performace;
public:
	superpositions(int w, int h, int nr_choices, int sec_size, int per);
	void set_seed();
	vector<pair<int, int>> get_lowest_uncollapsed();
	vector<int> get_outcomes(int x, int y);
	void set_outcomes(int x, int y, vector<int> v);
	void collapse(int x, int y, int choice);
	superpositions depth_propagation(pix_set &s, int x, int y, bool& broke, int performace, rules &r);
	superpositions breadh_propagation(pix_set &s, int x, int y, bool& broke, int performace);
	superpositions breadh_propagation(pix_set &s, int x, int y, bool &broke, int performace, vector<pair<int,int>> &queue);
	bool all_collapsed();
};

