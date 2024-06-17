#ifndef NODE_H
#define NODE_H

#include "header.hpp"

struct Node
{
	vector<vector<int>> state;
	Node *parent;
	int action_taken;
	vector<Node *> childns;
	vector<int> expandable_moves;

	int visit_count;
	int value_sum;

	Node(vector<vector<int>> &_state, Node *_parent = nullptr, int _action_take = -1)
	{
		state = _state;
		parent = _parent;
		action_taken = _action_take;
		expandable_moves = get_valid_actions(state);
		visit_count = 0;
		value_sum = 0;
	}

	bool is_fully_expanded()
	{
		return (expandable_moves.empty() && childns.size() > 0);
	}

	float get_ucb(Node *child)
	{
		float qv = 1 - ((((child->value_sum * 1.0f) / child->visit_count) + 1) / 2.0f);
		return qv + (1.41f * (sqrt(visit_count) / (child->visit_count * 1.0f)));
	}

	Node *select()
	{
		Node *ans = nullptr;
		float ucb = -INF;
		for (auto i : childns)
		{
			float curUcb = this->get_ucb(i);
			if (curUcb > ucb)
			{
				ucb = curUcb;
				ans = i;
			}
		}
		return (ans);
	}

	Node *expand()
	{
		int r = rand() % expandable_moves.size();
		int action = expandable_moves[r];
		swap(expandable_moves[r], expandable_moves[expandable_moves.size() - 1]);
		expandable_moves.pop_back();
		//
		vector<vector<int>> childState = get_next_state(state, action, 1);
		vector<vector<int>> childStateP = change_perspective(childState, -1);
		childns.push_back(new Node(childStateP, this, action));
		return (childns.back());
	}

	int simulate()
	{
		auto x = get_value_and_terminated(state, action_taken);
		int value = x.first;
		bool isterminal = x.second;
		value = get_opponet_value(value);
		if (isterminal) return (value);
		//
		vector<vector<int>> cps = state;
		vector<int> va = get_valid_actions(cps);
		int cplayer = 1;
		while (true)
		{
			int r = rand() % va.size();
			int act = va[r];
			swap(va[r], va[va.size() - 1]);
			va.pop_back();
			//
			cps = get_next_state(cps, act, cplayer);
			x = get_value_and_terminated(cps, act);
			if (x.second)
			{
				if (cplayer == -1) x.first *= -1;
				return x.first;
			}
			cplayer *= -1;
		}
		return (0);
	}

	void backpropagate(int value)
	{
		value_sum += value;
		visit_count += 1;

		value *= -1;
		if (parent) parent->backpropagate(value);
	}
};

#endif
