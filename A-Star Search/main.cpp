#include <iostream>
#include "Board.h" //This file appears to have disappeared
#include <queue>
#include<vector>
#include<set>
#include <algorithm>
#include <memory>

using namespace std;

struct less_than_dist
{
    inline bool operator() (const Board& b1, const Board& b2)
    {
        return (b1.dist < b2.dist);
    }
};

int main()
{
    string filename = "test.txt";
    Board puzzle(filename);
    Board puzzle2 = puzzle.twin();
    priority_queue<std::shared_ptr<Board>, vector<shared_ptr<Board> >, Mcompare> q1;
    priority_queue<std::shared_ptr<Board>, vector<shared_ptr<Board> >, Mcompare> q2;

    auto snode1 = puzzle;
    auto snode2 = puzzle2;
    auto prev1 = snode1;
    auto prev2 = snode2;

    int numtimes = 0;

    while( snode1.manhattan() != 0 && snode2.manhattan() != 0 && numtimes < 10000000) {
        shared_ptr<Board> newparent1 = std::make_shared<Board>(snode1);
        shared_ptr<Board> newparent2 = std::make_shared<Board>(snode2);
        auto n1 = snode1.Neighbors();
        int d1 = snode1.dist; //trying to make the heuristic work right maybe
        auto n2 = snode2.Neighbors();
        int d2 = snode2.dist;
        for(auto n: n1){
            if(!(*n == prev1)){
            (*n).setDist(d1+1);
            (*n).setParent(newparent1);
            q1.push(n);
            }
        }
        for(auto n: n2){
            if(!(*n == prev2)){
            (*n).setDist(d2+1);
            (*n).setParent(newparent2);
            q2.push(n);
            }
        }
        prev1 = snode1;
        prev2 = snode2;
        snode1 = *q1.top();
        q1.pop();
        snode2 = *q2.top();
        q2.pop();
        numtimes++;
    }
    cout << snode1 << endl;
    auto curr = snode1.parent;
    while(curr != nullptr){
        cout << *curr << endl;
        cout << (*curr).dist << endl << endl;
        curr = (*curr).parent;
    }
}
