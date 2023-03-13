#include "pix_set.h"

pix_set::pix_set(int w, int h, pixels inp)
{
	for (int i = 0; i < inp.height() - h + 1; i++)
	{
		for (int j = 0; j < inp.width() - w + 1; j++)
			p_set.push_back(inp.get_fragment(j, i, w, h));
	}
}

void pix_set::add_rotations()
{
	vector<pixels> new_set;
	for (auto el : p_set)
	{
		for (int i = 0; i < 4; i++)
		{
			new_set.push_back(el);
			el = el.rotate();
		}
	}
	p_set = new_set;
}

int pix_set::size()
{
	return p_set.size();
}

pixels pix_set::get_el(int nr)
{
	return p_set[nr];
}

void pix_set::del_copies()
{
	for (int i = 0; i < p_set.size() - 1; i++)
	{
		for (int j = i + 1; j < p_set.size(); j++)
		{
			if (p_set[j].the_same(p_set[i]))
			{
				p_set.erase(p_set.begin() + j);
				j--;
			}
		}
	}
}