#include <string>
#include <iostream>
#include <ctime>
#include <algorithm>

struct State
{
    int index_in_shorter, index_in_longer;
    int length;
};

std::ostream& operator<<(std::ostream& cout, State s)
{
    cout << '{' << s.index_in_shorter << ", " << s.index_in_longer << ", " << s.length << '}';
    return cout;
}

State find_longest_substring(std::string const &shorter, std::string const &longer)
{
    std::cout << "shorter: " << shorter << std::endl
	      << "longer: " << longer << std::endl;

    int shorter_size = shorter.size();
    int longer_size = longer.size();

    State states[shorter_size][2];
    State const empty_state = {0, 0, 0};
    State max_substring = empty_state;

    // init row 0;
    for (int i = 0; i < shorter_size; i++)
    {
	State &state = states[i][0];
	state.index_in_shorter = i;
	state.index_in_longer = 0;
	if (shorter[i] == longer[0])
	{
	    state.length = 1;
	    max_substring = state;
	}
	else
	{
	    state.length = 0;
	}
    }

    // init row 1;
    for (int i = 0; i < shorter_size; i++)
	states[i][1].length = 0;

    int state_row_index = 0;

    // For reducing search branch.
    int shorter_index_min = 0;
    int shorter_index_max = shorter_size;

    for (int j = 1; j < longer_size; j++)
    {
	state_row_index = 1 - state_row_index; // Starts with row 1 (second row) when j = 1;

	for (int i = shorter_index_min; i < shorter_index_max; i++)
	{
	    State const &prev_state = i == 0 ? empty_state : states[i - 1][1 - state_row_index];

	    State &current_state = states[i][state_row_index];

	    if (shorter[i] != longer[j])
	    {
		current_state.length = 0;
		continue;
	    }

	    if (prev_state.length == 0)
	    {
		current_state.index_in_shorter = i;
		current_state.index_in_longer = j;
	    }
	    else
	    {
		current_state.index_in_shorter = prev_state.index_in_shorter;
		current_state.index_in_longer = prev_state.index_in_longer;
	    }
	    current_state.length = prev_state.length + 1;

	    if (current_state.length > max_substring.length)
	    {
		max_substring = current_state;
		if (max_substring.length == shorter_size)
		    return max_substring; // Cannot be longer;
	    }
	}
    }
    return max_substring;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
	return -1;
    }

    std::string s1 = argv[1];
    std::string s2 = argv[2];

    std::string const &shorter = s1.size() < s2.size() ? s1 : s2;
    std::string const &longer = s1.size() >= s2.size() ? s1 : s2;

    State max_substring = find_longest_substring(shorter, longer);

    std::cout << "index in shorter: " << max_substring.index_in_shorter << std::endl
	      << "substring length: " << max_substring.length << std::endl
	      << shorter.substr(max_substring.index_in_shorter, max_substring.length)
	      << std::endl;

    return 0;
}
