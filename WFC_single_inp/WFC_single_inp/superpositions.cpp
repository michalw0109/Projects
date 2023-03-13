#include "superpositions.h"

superpositions::superpositions(int w, int h, int nr_choices, int sec_size, int per)
{
	section_size = sec_size;
	max_performace = per;
	for (int i = 0; i < h; i++)
	{
		vector<vector<int>> temp;
		vector<bool> temp2;
		for (int j = 0; j < w; j++)
		{
			vector<int> states;
			for (int k = 0; k < nr_choices; k++)
			{
				states.push_back(k);
			}
			shuffle(states);
			temp.push_back(states);

			temp2.push_back(false);
		}
		arr.push_back(temp);
		collapsed.push_back(temp2);
	}
}

void superpositions::set_seed()
{
	arr[rand() % (arr.size())][rand() % (arr[0].size())].resize(1);
}


vector<pair<int, int>> superpositions::get_lowest_uncollapsed()
{
	int min = INT32_MAX;
	vector < pair<int, int>> coords;
	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = 0; j < arr[0].size(); j++)
		{
			if (collapsed[i][j])
				continue;
			if (min == 0)
			{
				coords.clear();
				return coords;
			}

			if (arr[i][j].size() < min)
			{
				coords.clear();
				coords.push_back({ j, i });
				min = arr[i][j].size();
				continue;
			}

			if (arr[i][j].size() == min)
			{
				coords.push_back({ j, i });
			}
		}
	}
	return coords;
}

vector<int> superpositions::get_outcomes(int x, int y)
{
	return arr[y][x];
}

void superpositions::set_outcomes(int x, int y, vector<int> v)
{
	arr[y][y] = v;
	collapsed[y][x] = false;
}

void superpositions::collapse(int x, int y, int choice)
{
	arr[y][x].clear();
	arr[y][x].push_back(choice);
	collapsed[y][x] = true;
}

superpositions superpositions::breadh_propagation(pix_set &s, int x, int y, bool& broke, int performace)
{
	vector<pair<int, int>> temp_v;
	return breadh_propagation(s, x, y, broke, performace, temp_v);
}

superpositions superpositions::breadh_propagation(pix_set &s, int x, int y, bool &broke, int performace, vector<pair<int, int>> &queue)
{
	superpositions temp(*this);
	if (broke)
		return temp;
	if(performace > max_performace)
		return temp;

	for (int i = y - section_size + 1; i < y + section_size; i++)
	{
		for (int j = x - section_size + 1; j < x + section_size; j++)
		{
			
			if (i < 0 || j < 0 || i >= temp.arr.size() || j >= temp.arr[0].size())
				continue;
			if (temp.collapsed[i][j])
				continue;
			/*vector<int> temp_v;
			for (auto propagated : temp.arr[i][j])
			{
				bool match = false;
				for (auto propagates : temp.arr[y][x])
				{
					bool diff = false;
					for (int k = i; k < i + section_size; k++)
					{
						for (int l = j; l < j + section_size; l++)
						{
							
							if (k < y || l < x || k >= y + section_size || l >= x + section_size)
								continue;
							if (!(s.get_el(propagated).get_pixel(l - j, k - i) == s.get_el(propagates).get_pixel(l - x, k - y)))
							{
								diff = true;
								break;
							}
						}
						if (diff)
							break;
					}
					if (!diff)
					{
						match = true;
						break;
					}
						
				}
				if (match)
					temp_v.push_back(propagated);
			}*/
			//cout << "spropagowano  " << i << "  " << j << endl;
			vector<int> temp_v;
			if (temp_v.size() == 0)
			{
				broke = true;
				temp.arr[i][j] = temp_v;
				return temp;
			}
			if (temp_v != temp.arr[i][j])
			{
				
				temp.arr[i][j] = temp_v;
				
				if (broke)
					return temp;

				pair<int, int> temp_pair = { j, i };
				bool found = false;
				for (auto el : queue)
				{
					if (el == temp_pair)
					{
						found = true;
						break;
					}
				}
				if (!found)
					queue.push_back({ j, i });
			}
		}
	}
	
	vector <pair<int, int>> new_queue;
	for (auto el : queue)
		temp = temp.breadh_propagation(s, el.first, el.second, broke, performace + 1, new_queue);

	return temp;
}


superpositions superpositions::depth_propagation(pix_set &s, int x, int y, bool& broke, int performace, rules &r)
{
	superpositions temp(*this);
	if (broke)
		return temp;
	if (performace > max_performace)
		return temp;

	for (int i = y - section_size + 1; i < y + section_size; i++)
	{
		for (int j = x - section_size + 1; j < x + section_size; j++)
		{
			if (i < 0 || j < 0 || i >= temp.arr.size() || j >= temp.arr[0].size())
				continue;
			if (temp.collapsed[i][j])
				continue;

			set<int> rules_set;
			for (auto el : temp.arr[y][x])
			{
				for (auto el2 : r.r[el][i - y + section_size - 1][j - x + section_size - 1])
				{
					rules_set.insert(el2);
				}
			}

			vector<int> temp_v;
			for (auto el : temp.arr[i][j])
			{
				if (rules_set.find(el) != rules_set.end())
					temp_v.push_back(el);
			}

			if (temp_v.size() == 0)
			{
				broke = true;
				temp.arr[i][j] = temp_v;
				return temp;
			}
			if (temp_v != temp.arr[i][j])
			{
				temp.arr[i][j] = temp_v;
				temp = temp.depth_propagation(s, j, i, broke, performace + 1, r);
				if (broke)
					return temp;

			}
		}
	}

	return temp;
}

bool superpositions::all_collapsed()
{
	for (int i = 0; i < collapsed.size(); i++)
	{
		for (int j = 0; j < collapsed[0].size(); j++)
		{
			if (!collapsed[i][j])
				return false;
		}
	}
	return true;
}






