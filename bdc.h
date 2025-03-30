#ifndef BDC_H
#define BDC_H

#include <vector>
#include <string>

using namespace std;

// Although pass by reference would probably be more efficient
// for one or both of these methods, it is not a substantial difference
// since the vectors used in this program are not very large.
string vec_to_string(const vector<int>& v);

vector<int> sort(vector<int> input);

vector<int> max(const vector<vector<int>>& input);

vector<int> find_dividends(vector<int>& input, int index);

vector<int> bdc_helper(vector<int>& input);

vector<int> biggest_divisible_conglomerate(vector<int>& input);

#endif