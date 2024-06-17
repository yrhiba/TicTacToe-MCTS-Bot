#include "header.hpp"
#include "node.hpp"
#include "mcts.hpp"

vector<vector<int>> get_initial_state()
{
	return (vector<vector<int>>(3, vector<int>(3, 0)));
}

vector<vector<int>> get_next_state(vector<vector<int>> state, int action, int player)
{
	state[action / cols][action % cols] = player;
	return state;
}

vector<int> get_valid_actions(vector<vector<int>> &state)
{
	vector<int> va;
	for (int i = 0; i < 9; i++)
	{
		int r = i / cols, c = i % cols;
		if (state[r][c] == 0) va.push_back(i);
	}
	return va;
}

bool check_win(vector<vector<int>> &state, int action)
{
	if (action == -1) return (false);
	int r = action / cols, c = action % cols;
	int player = state[r][c];
	for (int i = 0; i < rows; i++)
	{
		int s = 0;
		for (int j = 0; j < cols; j++) s += state[i][j];
		if (s == player * rows) return (true);
	}
	for (int i = 0; i < cols; i++)
	{
		int s = 0;
		for (int j = 0; j < rows; j++) s += state[j][i];
		if (s == player * cols) return (true);
	}
	int d1 = state[0][0] + state[1][1] + state[2][2];
	int d2 = state[0][2] + state[1][1] + state[2][0];
	return ((d1 == player * rows) || (d2 == player * cols));
}

pair<int, bool> get_value_and_terminated(vector<vector<int>> &state, int action)
{
	if (check_win(state, action))
		return {1, true};
	if (get_valid_actions(state).empty())
		return {0, true};
	return {0, false};
}

int get_opponet(int player)
{
	return -player;
}

int get_opponet_value(int value)
{
	return -value;
}

void print(vector<vector<int>> &state)
{
	cout << "--------------" << endl;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			cout << " " << state[i][j] << " \n"[j+1 == cols];
	cout << "--------------" << endl;
}

vector<vector<int>> change_perspective(vector<vector<int>> &state, int player)
{
	vector<vector<int>> s = state;
	for (auto &v : s)
		for (auto &i : v) i *= player;
	return (s);
}

int main()
{
	srand(time(0));
	MCTS mcts;

	vector<vector<int>> state = get_initial_state();
	int player = 1;

	for (int turn = 1, lastAction = -1; ; turn++)
	{
		print(state);

		if (lastAction != -1)
		{
			auto x = get_value_and_terminated(state, lastAction);
			if (x.second)
			{
				if (x.first == 1) cout << get_opponet(player) << " Win!" << endl;
				if (x.first == 0) cout << "Tie!" << endl;
				break;
			}
		}

		int action;

		if (player == 1) 
		{
			cout << "valid-actions: ";
			auto va = get_valid_actions(state);
			for (int a : va) cout << "(" << a/cols + 1 << ", " << a%cols + 1 << ") ";
			cout << endl;

			cout << "Enter your action: ";

			set<int> st(va.begin(), va.end());
			int r, c; cin >> r >> c;
			r -= 1, c -= 1;
			action = r * cols + c;
			if (st.count(action) == 0)
			{
				cout << "Invalid action, try again." << endl;
				continue;
			}
		}
		else
		{
			vector<vector<int>> cs = change_perspective(state, -1);
			action = mcts.search(10000, cs);
			cout << "IA action: " << action/cols + 1 << " " << action%cols + 1 << endl;
		}

		state = get_next_state(state, action, player);
		player = get_opponet(player);
		lastAction = action;
	}
};
