#pragma once
#include "pixels.h"

class pix_set
{
private:
	vector<pixels> p_set;
public:
	pix_set(int w, int h, pixels inp);
	void add_rotations();
	int size();
	pixels get_el(int nr);
	void del_copies();
};

