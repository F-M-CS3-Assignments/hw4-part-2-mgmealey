#ifndef BDC_H
#define BDC_H

#include <vector>
#include <string>

using namespace std;

// Although pass by reference would probably be more efficient
// for one or both of these methods, it is not a substantial difference
// since the vectors used in this program are not very large.
string vec_to_string(const vector<int>& v);

int find_next_dividend(const vector<int>& input, int start);

vector<int> sub_vec(vector<int> vec, int start);

vector<int> longest_vector(const vector<vector<int>>& candidates);

vector<int> combine(vector<int>& l, vector<int>& r);

vector<int> bdc_helper(vector<int>& input);

vector<int> biggest_divisible_conglomerate(vector<int>& input);

#endif