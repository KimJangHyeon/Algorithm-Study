#include <iostream>

/*
 * https://www.acmicpc.net/problem/2042
 * 구간 합 구하기
 * N for number of input element
 * M for modification
 * K for get sum of interval
 * I use segment tree for getting sum of interval
 */

using namespace std;

long long find_sum(long long* tree, long long idx, long long left, long long right, long long start, long long end) {
	// neither match
	if (right < start || end < left) {
		return 0;
	}
	// in the interval
	if (start <= left  && right <= end) {
		return tree[idx];
	}
	return find_sum(tree, idx * 2, left, (left + right) / 2, start, end) + find_sum(tree, idx * 2 + 1, (left + right) / 2 + 1, right, start, end);
}

void modify_tree(long long* tree, long long idx, long long left, long long right, long long target, long long diff) {
	tree[idx] += diff;
	if (left == right) {
	} else if (target <= (left + right) / 2) {
		modify_tree(tree, idx * 2, left, (left + right) / 2, target, diff);
	} else {
		modify_tree(tree, idx * 2 + 1, (left + right) / 2 + 1, right, target, diff);
	}
}

int main(void) {
	int N, M, K;
	cin >> N >> M >> K;
	int nearest_size = 1;
	while (nearest_size < N) {
		nearest_size *= 2;
	}
	long long* segment_tree = new long long[2*nearest_size + 1];
	for (int i = 0; i <= 2*nearest_size; ++i) { segment_tree[i] = 0; };

	// fill tree 
	for (int i = 0; i < N; ++i) {
		cin >> segment_tree[nearest_size + i];
	}

	// initialize tree
	int traverse_sz = nearest_size;
	while (traverse_sz > 1) {
		for (int i = traverse_sz; i < 2*traverse_sz; i+=2) {
			segment_tree[i/2] = segment_tree[i] + segment_tree[i + 1];
		}
		traverse_sz /= 2;
	}


	traverse_sz = 1;
	//while (traverse_sz <= nearest_size) {
	//	for (int i = traverse_sz; i < traverse_sz * 2; ++i) {
	//		cout << segment_tree[i] << ' ';
	//	}
	//	cout << '\n';
	//	traverse_sz *= 2;
	//}

	long long a,b,c;
	long long diff;
	for (int ii = 0; ii < M + K; ++ii) {
		cin >> a >> b >> c;
		// Modify
		if (a == 1) {
			diff = c - segment_tree[nearest_size + b - 1];
			modify_tree(segment_tree, 1, 1, nearest_size, b, diff);
			traverse_sz = 1;
			//while (traverse_sz <= nearest_size) {
			//	for (int i = traverse_sz; i < traverse_sz * 2; ++i) {
			//		cout << segment_tree[i] << ' ';
			//	}
			//	cout << '\n';
			//	traverse_sz *= 2;
			//}

			// Search
		} else if (a == 2) {
			cout << find_sum(segment_tree, 1, 1, nearest_size, b, c) << '\n';

		}
	}
	return 0;
}

