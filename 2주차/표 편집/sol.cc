#include <string>
#include <vector>
using namespace std;

struct Node{
    struct Node* before;
    struct Node* next;
    int val;
};

string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    Node * tmp;
    Node * iter = NULL;
    Node * HEAD = NULL;
    HEAD = new Node();
    iter = HEAD;
    vector<Node *> delete_log;
    int total_move = 0;
    iter->val = 0;
    for (int i = 1; i < n; ++i) {
        tmp = new Node();
        tmp->val = i;
        iter->next = tmp;
        tmp->before = iter;
        iter = tmp;
    }
    iter->next = NULL;
    iter = HEAD;
    for (int i = 0; i < k; ++i) {
        iter = iter->next;
    }
    ///////


    // RUN
    for (string command : cmd) {
        if (command[0] == 'U') {
            total_move -= stoi(command.substr(2));
        } else if (command[0] == 'D') {
            total_move += stoi(command.substr(2));
        } else {
            // apply changes
            if (total_move < 0) {
                for (int i = 0; i < abs(total_move); ++i) {
                    iter = iter->before;
                }
            } else if (total_move > 0) {
                for (int i = 0; i < total_move; ++i) {
                    iter = iter->next;
                }
            }
            total_move = 0;

            if (command[0] == 'C') {
                if (iter->next == NULL) {
                    tmp = iter->before;
                    iter->before->next = NULL;
                } else {
                    tmp = iter->next;
                    if (iter->before)
                        iter->before->next = iter->next;
                    iter->next->before = iter->before;
                }
                delete_log.push_back(iter);
                iter = tmp;
            } else if (command[0] == 'Z') {
                tmp = delete_log.back();
                delete_log.pop_back();
                if (tmp->before)
                    tmp->before->next = tmp;
                if (tmp->next)
                    tmp->next->before = tmp;
            }
        }
    }

    while (iter->before != NULL) {
        iter = iter->before;
    }
    for (int i = 0; i < n; ++i) {
        answer += "X";
    }
    while (iter != NULL) {
        answer[iter->val] = 'O';
        iter = iter->next;
    }
    return answer;
}
