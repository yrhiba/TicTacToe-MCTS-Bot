#ifndef MCTS_H
# define MCTS_H

#include "header.hpp"
#include "node.hpp"

struct MCTS
{
	MCTS()
	{
	}

	int search(int number_of_iterations, vector<vector<int>> &state)
	{
		// Define root
		Node *root = new Node(state);

		for (int i = 0; i < number_of_iterations; i++)
		{
			Node *it = root;

			while (it->is_fully_expanded())
				it = it->select();

			auto x = get_value_and_terminated(it->state, it->action_taken);
			int value = get_opponet_value(x.first);

			if (x.second == false) // not terminated yet
			{
				it = it->expand();
				value = it->simulate();
			}

			it->backpropagate(value);
		}
		//
		vector<float> porb = vector<float>(actions_size, 0);
		int sum = 0;
		for (auto i : root->childns)
		{
			porb[i->action_taken] += i->visit_count;
			sum += i->visit_count;
		}
		//
		int ansAct = 0;
		float ansProb = -INF;
		for (int i = 0; i < actions_size; i++)
		{
			porb[i] /= (sum * 1.0f);
			if (porb[i] > ansProb)
			{
				ansProb = porb[i];
				ansAct = i;
			}
		}
		//
		return (ansAct);
	}
};

#endif
