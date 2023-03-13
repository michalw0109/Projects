#include "rules.h"

rules::rules(pix_set s, int sec_w)
{
	int x = sec_w;
	int y = sec_w;
	


	for (int n = 0; n < s.size(); n++)
	{
		
		vector<vector<vector<int>>> vec_vec_temp_v;
		for (int i = y - sec_w + 1; i < y + sec_w; i++)
		{
			vector<vector<int>> vec_temp_v;
			for (int j = x - sec_w + 1; j < x + sec_w; j++)
			{
				vector<int> temp_v;
				for (int m = 0; m < s.size(); m++)
				{
					bool match = false;

					bool diff = false;
					for (int k = i; k < i + sec_w; k++)
					{
						for (int l = j; l < j + sec_w; l++)
						{
							//cout << "1" << endl;
							if (k < y || l < x || k >= y + sec_w || l >= x + sec_w)
								continue;
							if (!(s.get_el(m).get_pixel(l - j, k - i) == s.get_el(n).get_pixel(l - x, k - y)))
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
						
					}



					if (match)
						temp_v.push_back(m);
				}
				vec_temp_v.push_back(temp_v);






			}
			vec_vec_temp_v.push_back(vec_temp_v);

		}

		
		r.push_back(vec_vec_temp_v);


	}


	



}
