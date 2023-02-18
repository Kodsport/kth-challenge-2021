#include <bits/stdc++.h>
#include "validate.h"

using namespace std;


void check_case(){
    int n,m;

    judge_in >> n >> m;

    int judge_answer, author_answer;

    if(!(author_out >> author_answer)){
        wrong_answer("Could not read contestants output\n");
    }
    if(!(judge_ans >> judge_answer)){
        judge_error("Could not read judge output\n");
    }

    if(author_answer == -1){
        if(judge_answer != -1){
            wrong_answer("Contestant printed '-1' even though an answer existed.");
        }
        return;
    }

    vector<vector<int> > graph(n, vector<int>());
    set<int> sums;
    for(int c1 = 0; c1 < m; c1++){
        int a,b;
        if(c1 == 0){
            a = author_answer;
            if(!(author_out >> b)){
                wrong_answer("Could not read %d:th line of output", c1+1);
            }
        }
        else{
            if(!(author_out >> a >> b)){
                wrong_answer("Could not read %d:th line of output", c1+1);
            }
        }
        if(a < 1 || a > n || b < 1 || b > n){
            wrong_answer("Numbers out of bounds on %d:th line: %d %d", c1+1, a, b);
        }
        if(a == b){
            wrong_answer("Self-loop on %d:th line", c1+1);
        }

        if(sums.find(a+b) != sums.end()){
            wrong_answer("Error on line %d: already seen sum %d", c1+1, a+b);
        }
        sums.insert(a+b);
        a--;
        b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Check that the graph is connected
    set<int> seen;
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()){
        int a = Q.front();
        Q.pop();
        for(int c1 = 0; c1 < graph[a].size(); c1++){
            int b = graph[a][c1];
            if(seen.find(b) == seen.end()){
                Q.push(b);
                seen.insert(b);
            }
        }
    }
    if(seen.size() < n){
        wrong_answer("Graph was not connected.");
    }
    if(judge_answer == -1){
        judge_error("Judge said '-1' but contestant found a solution.");
    }

}

int main(int argc, char **argv) {
  init_io(argc, argv);
  check_case();

  /* Check for trailing output. */
  string trash;
  if (author_out >> trash) {
      wrong_answer("Trailing output\n");
  }

  accept();
  return 0;
}
