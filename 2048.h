#include<bits/stdc++.h>
using namespace std;

static const double SCORE_LOST_PENALTY = 200000.0;
static const double SCORE_MONOTONICITY_POWER = 4.0;
static const double SCORE_MONOTONICITY_WEIGHT = 47.0;
static const double SCORE_SUM_POWER = 3.5;
static const double SCORE_SUM_WEIGHT = 11.0;
static const double SCORE_MERGES_WEIGHT = 700.0;
static const double SCORE_EMPTY_WEIGHT = 270.0;
static const double CPROB_THRESH_BASE = 0.0001;
static const int MAX_DEPTH = 3;
static const double inf = 1e16;

int p_pow[20];
double heuristic_score[66536];
int moveState[66536];

void PreCalHeuristicScore();
void calPow2();
int gen(int lo, int hi);  // generate a number randomly between lo and hi
int *random_gen(int f[][4]); // generate a number 1 or 2 in an empty cell of the current state.
bool checkTwoStatesEqual(int state_A[][4], int state_B[][4]);
void printDirection(int move); // 0: L, 1: R, 2: U, 3: D
void printState(int state[][4]);
int count_empty(int state[][4]); // Count the number of empty cells of the current state.
array<int, 4> Processs(array<int,4> arr, int &score);
double eval(array<int, 4> arr); // Calculate the heuristic score of a row.
double eval_grid(int f[][4]);  // Calculate the heuristic score of the current state.

void calPow2() {
	p_pow[0] = 1;
	for (int i = 1; i < 20; i++) {
		p_pow[i] = p_pow[i - 1] * 2;
	}
}

int gen(int lo, int hi) {
	int gen_num = rand() % (hi - lo + 1) + lo;
	return gen_num;
}

int *random_gen(int f[][4]) {
	vector<int> list0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (!f[i][j])
				list0.push_back(i * 4 + j);
		}

	int id = gen(0, (int)list0.size() - 1);
	int x = list0[id];
	int num = gen(1, 2);

	list0.clear();

	f[x / 4][x % 4] = num;

	return reinterpret_cast<int *>(f);
}

bool checkTwoStatesEqual(int state_A[][4], int state_B[][4]) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (state_A[i][j] != state_B[i][j])
				return false;
		}

	return true;
}

void printDirection(int move) {
	if (!move) cout << "L\n";
	else if (move == 1) cout << "R\n";
	else if (move == 2) cout << "U\n";
	else cout << "D\n";
}

void printState(int state[][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			if (state[i][j] == 0) cout << 0 << ' ';
			else cout << p_pow[state[i][j]] << ' ';
		cout << '\n';
	}

	cout << '\n';
}

int count_empty(int state[][4]) {
	int cnt = 0;

	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			if (!state[i][j])
				cnt++;
		}

	return cnt;
}

void PreCalMove() {
	for (int state = 0; state < 66536; state++) {
		int arr[] = { state & 15, (state >> 4) & 15, (state >> 8) & 15, (state >> 12) & 15};
		// int arr[] = { (state >> 12) & 15, (state >> 8) & 15, (state >> 4) & 15, state & 15};
		bool canMerge = false;
		for (int i = 3; i >= 0; i--) {
			if (!arr[i]) continue;
			int j = i;
			if (!canMerge) {
				while (j < 3 && !arr[j + 1]) {
					swap(arr[j], arr[j + 1]);
					j++;
				}
				canMerge = true;
			} else {
				while (j < 3 && !arr[j + 1]) {
					swap(arr[j], arr[j + 1]);
					j++;
				}
				if (arr[j + 1] == arr[j]) {
					arr[j] = 0;
					arr[j + 1]++;
					canMerge = false;
				}
			}
		}	

		int ret = 0;
		ret |= arr[0];
		ret |= (arr[1] << 4);
		ret |= (arr[2] << 8);
		ret |= (arr[3] << 12);

		moveState[state] = ret;
	}
}

array<int, 4> Processs(array<int,4> arr, int &score) {
	int curState = 0;
	curState |= arr[0];
	curState |= (arr[1] << 4);
	curState |= (arr[2] << 8);
	curState |= (arr[3] << 12);

	int newState = moveState[curState];
	array<int,4> res;
	res[0] = newState & 15;
	res[1] = (newState >> 4) & 15;
	res[2] = (newState >> 8) & 15;
	res[3] = (newState >> 12) & 15;
	return res;
}

void PreCalHeuristicScore() {
	for (int state = 0; state < 66536; state++) {
		int arr[] = { state & 15, (state >> 4) & 15, (state >> 8) & 15, (state >> 12) & 15 };
		double sum = 0;
		int empty = 0, merges = 0, prev = 0, cnt = 0;

		int mx = 0;

		for (int i = 0; i < 4; i++) {
			int rank = arr[i];

			mx = max(rank, mx);

			sum += pow(rank, SCORE_SUM_POWER);

			if (!rank) {
				empty++;
			} else {
				if (prev == rank) {
					cnt++;
				} else if (cnt > 0) {
					merges += (1 + cnt);
					cnt = 0;
				}
				prev = rank;
			}
		}
		if (cnt) {
			merges += (1 + cnt);
		}

	    double monotonicity_left = 0;
	    double monotonicity_right = 0;
	    for (int i = 1; i < 4; ++i) {
	        if (arr[i - 1] > arr[i]) {
	            monotonicity_left += pow(arr[i - 1], SCORE_MONOTONICITY_POWER) - pow(arr[i], SCORE_MONOTONICITY_POWER);
	        } else {
	            monotonicity_right += pow(arr[i], SCORE_MONOTONICITY_POWER) - pow(arr[i - 1], SCORE_MONOTONICITY_POWER);
	        }
	    }

	    heuristic_score[state] = SCORE_LOST_PENALTY + SCORE_EMPTY_WEIGHT * empty +
	        SCORE_MERGES_WEIGHT * merges -
	        SCORE_MONOTONICITY_WEIGHT * min(monotonicity_left, monotonicity_right) -
	        SCORE_SUM_WEIGHT * sum;				
	}
}

double eval(array<int,4> arr) {
	int state = 0;
	state |= arr[0];
	state |= (arr[1] << 4);
	state |= (arr[2] << 8);
	state |= (arr[3] << 12);
	return heuristic_score[state];
}

double eval_grid(int f[][4]) {
	double total_heur = 0;

	for (int i = 0; i < 4; i++) {
		total_heur += eval({f[i][0], f[i][1], f[i][2], f[i][3]});
		total_heur += eval({f[0][i], f[1][i], f[2][i], f[3][i]});
	}

	return total_heur;
}