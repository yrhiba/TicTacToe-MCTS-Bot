#ifndef HEADER_H
# define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <sys/time.h>
#include <unistd.h>
using namespace std;
//
# define INF 1e9
// Decide hoes start first human or IA.
# define HUMAN true
# define IA false
# define STARTFIRST IA
// States
# define XWIN -10
# define OWIN 10
# define TIE 0
# define STILL -2

int rows = 3;
int cols = 3;
int actions_size = rows * cols;


/* tic tac toe */
vector<vector<int>> get_initial_state();
vector<vector<int>> get_next_state(vector<vector<int>> state, int action, int player);
vector<int> get_valid_actions(vector<vector<int>> &state);
bool check_win(vector<vector<int>> &state, int action);
pair<int, bool> get_value_and_terminated(vector<vector<int>> &state, int action);
int get_opponet(int player);
int get_opponet_value(int value);
void print(vector<vector<int>> &state);
vector<vector<int>> change_perspective(vector<vector<int>> &state, int player);

#endif
