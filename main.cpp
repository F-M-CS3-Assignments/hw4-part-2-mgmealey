#include "bdc.h"

#include <vector>
#include <cassert>
#include <iostream>
#include <set>

// uncomment for part 2
#include <random>

//turns vector into string to be outputted
//from my part 1 program
string vec_to_string(const vector<int>& v){
	string output;
	output = output + "[";
	for (int i =  0; i < v.size() - 1; ++i){
		output = output + to_string(v[i]) + ", ";
	}
	output = output + to_string(v[v.size() - 1]) + "]";

	return output;
}

// //sorts the vector
// //from my part 1 program
// vector<int> sort(vector<int> input){

// 	vector<int> sorted_vec;
// 	int start = 0;

// 	while (!input.empty()){
// 		//first find smallest number in sequence
// 		int min_idx = 0;
// 		int min = input[0];

// 		for(time_t i = 0; i < input.size(); ++i){
// 			if (input[i] < min){
// 				min = input[i];
// 				min_idx = i;
// 			}
// 		}
		
// 		//add min number to new sorted vector and then remove it from the original vector
// 		sorted_vec.push_back(min);
// 		input.erase(input.begin() + min_idx);

// 	}
// 	return sorted_vec;
// }

//finds vector of max length within a vector of vectors
vector<int> max(const vector<vector<int>>& input){
	vector<int> longest_vec = input[0];
	int max_length = longest_vec.size();

	for (int i = 0; i < input.size(); i++){
		if (input[i].size() > max_length){
			longest_vec = input[i];
			max_length = input[i].size();
		}
	}

	return longest_vec;
}


//will return a vector containing all divisors of the int at a certain index of a vector
vector<int> find_dividends(vector<int>& input, int index){

	vector<int> dividends;

	if (index == 0){
		return dividends;
	}
	//only look at the indexes before the index in question
	for (int i = 0; i < index; i++){
		if (input[index] % input[i] == 0){
			dividends.push_back(input[i]);
		}
	}
	
	return dividends;
}

vector<int> longest_vector(const vector<vector<int>>& candidates){
	
	int max_length = candidates[0].size();
	int idx_longest = 0;

	for (int i = 0; i < candidates.size(); ++i){
		if(candidates[i].size() > max_length){
			max_length = candidates[i].size();
			idx_longest = i;
		}
	}
	return candidates[idx_longest];
}

vector<int> bdc_helper(vector<int>& input){

	if (input.empty()) {
        return {};  // Return an empty vector if input is empty
    }

	//this vector is for the longest conglomorate including each index in input
	//this is our dp chart
	//one column for input[i], one for the longest vector including input[i]
	vector<vector<int>> conglomorates(input.size());

	//base case
	conglomorates[0].push_back(input[0]);

	//for each input[i] add each possible conglomarate including that number to a list
	for(int i = 1; i < input.size(); i++){
		vector<int> dividends = find_dividends(input, i);

		vector<vector<int>> div_congs;

		//for each previous number that i is divisible by, add it to the vector
		//and push to conglomorates
		for (int j = 0; j < dividends.size(); j++){
			int divisor_idx = -1;

			// Find the index of the divisor in the input array
			for (int k = 0; k < i; ++k) {
				if (input[k] == dividends[j]) {
					divisor_idx = k;
					break;
				}
            }

			//if it has a divisor
			if (divisor_idx != -1){
				div_congs.push_back(conglomorates[divisor_idx]);
			}
		}

		//add i to the longest conglomorate made of its divisors
		if (!div_congs.empty()){
			vector<int> max_div_cong = max(div_congs);
			max_div_cong.push_back(input[i]);
			conglomorates[i] = max_div_cong;
		} else {
			conglomorates[i] = {input[i]};
		}
	}
	return max(conglomorates);
}
	

vector<int> biggest_divisible_conglomerate(vector<int>& input){
	sort(input.begin(), input.end());
	return bdc_helper(input);
}

int main() {

	// Test 1 (example from assignment description)
	vector<int> values = {28, 22, 7, 2, 8, 14, 24, 56};
	vector<int> ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	set<int> answerSet(ans.begin(), ans.end());
	set<int> soln = {56, 14, 7, 28};
	bool first = (answerSet == soln);
	soln = {56, 28, 14, 2};
	bool second = (answerSet == soln);
	assert(first || second);

	// Test 2
	values = {10, 5, 3, 15, 20};
	ans = biggest_divisible_conglomerate(values);
	cout << "input: " << vec_to_string(values) << endl;
	cout << "output: " << vec_to_string(ans) << endl << endl;
	soln = {20, 5, 10};
	set<int> answerSet2(ans.begin(), ans.end());
	assert(answerSet2 == soln);


	// The random number test creates a massive 28,000 value input vector.  
	// Solving the problem with such a large input is not feasible using recursion, 
	// but with dynamic programming it should take just a few seconds.  
	
	vector<int> random_values;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dist(1, 40000);
	while (random_values.size() < 28000) {
		random_values.push_back(dist(gen));
	}

	cout << "\nCalculating answer for input of size: " << random_values.size() << "..." << endl;
	time_t start = time(0);
	ans = biggest_divisible_conglomerate(random_values);
	time_t end = time(0);
	cout << "\x1B[32m" << "\tDone!  The answer is: " << vec_to_string(ans) << "\033[0m" << endl;
	time_t duration = end - start;
	cout << "It took " << duration << " seconds.  Wow!" << endl;\
	
	
	return 0;
}
