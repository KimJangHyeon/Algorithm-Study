#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <functional>
#include <iostream>

using namespace std;


bool find_path(pair<int, int> start, pair<int, int> target, const vector<string> place) {
    
    if (place[start.first][start.second] == 'X') {
        return false;
    }
    
    int drow = target.first - start.first;
    int dcol = target.second - start.second;

    if (drow == 0 && dcol == 0) {
        return true;
    } 
    
    if (drow > 0 && 
        find_path(make_pair(start.first + 1, start.second), target, place)) {
        return true;
    } else if (drow < 0 &&
        find_path(make_pair(start.first - 1, start.second), target, place)) {
        return true;
    } else if (dcol > 0 &&
        find_path(make_pair(start.first, start.second + 1), target, place)) {
        return true;
    } else if (dcol < 0 &&
        find_path(make_pair(start.first, start.second - 1), target, place)) {
        return true;
    }
    return false;
}


vector<int> solution(vector<vector<string>> places) {
    int distance = 2;
    vector<int> answer;

    for (vector<string> place : places) {
        vector<pair<int, int>> person;
        bool is_safe = true;

        for (int row = 0; row < place.size(); ++row) {
            for (int col = 0; col < place[0].size(); ++col) {
                if (place[row][col] == 'P') {
                    person.push_back(make_pair(row, col));
                } 
            }
        }
        int delta_row, delta_col;
        int tmp_distance;
        sort(person.begin(), person.end());
        for (int i = 0; i < person.size() - 1; ++i) {
            for (int j = i + 1; j < person.size(); ++j) {
                delta_row = person[j].first - person[i].first;
                delta_col = person[j].second - person[i].second;
                tmp_distance = abs(delta_row) + abs(delta_col);
                
                // Obvious Case
                if (tmp_distance == 1) {
                    is_safe = false;
                    break;
                }
                if (tmp_distance <= distance 
                    && find_path(person[i], person[j], place)) {
                    is_safe = false;
                    break;
                }
                
            }
            if (!is_safe) {
                break;
            }
        }

        if (is_safe) {
            answer.push_back(1);
        } else {
            answer.push_back(0);
        }
    }
    
    return answer;
}