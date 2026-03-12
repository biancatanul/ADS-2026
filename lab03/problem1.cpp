/*
Problem 1: Dynamic Leaderboard
Description
You are maintaining a live leaderboard for an online game. Players gain and lose points over time. You must efficiently update scores and answer ranking queries.
Operations
You will receive QQQ operations of the following types:
ADD player score
 Add a new player with the given score.
UPDATE player delta
 Increase or decrease the player's score by delta.
REMOVE player
 Remove the player from the leaderboard.
TOP k
 Return the k players with the highest scores.
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include "RBNode.h"
using namespace std;

int main() {
    RBTree tree;
    unordered_map<string, int> scores;

    string operation;
    while (cin >> operation) {
        if (operation == "ADD") {
            string name;
            int score;
            cin >> name >> score;

            scores[name] = score;
            tree.RBInsert(tree.createNode(score));
        } else if (operation == "UPDATE") {
            string name;
            int delta;
            cin >> name >> delta;

            int oldScore = scores[name];
            RBNode *node = tree.search(tree.root, oldScore);
            if (!tree.isNil(node)) {
                tree.del(node);
            }

            int newScore = oldScore + delta;
            scores[name] = newScore;
            tree.RBInsert(tree.createNode(newScore));
        } else if (operation == "REMOVE") {
            string name;
            cin >> name;

            int score = scores[name];

            RBNode *node = tree.search(tree.root, score);
            if (!tree.isNil(node)) {
                tree.del(node);
            }
            scores.erase(name);
        } else if (operation == "TOP") {
            int top_players;
            cin >> top_players;

            RBNode *current = tree.maximum(tree.root);

            for (int i = 0; i < top_players && !tree.isNil(current); i++) {
                for (auto &pair: scores) {
                    if (pair.second == current->key) {
                        cout << pair.first << " " << current->key << endl;
                        break;
                    }
                }
                current = tree.predecessor(current);
            }
        }
    }
}
