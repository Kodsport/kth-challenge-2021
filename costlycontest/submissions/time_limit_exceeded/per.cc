#include<bits/stdc++.h>
using namespace std;

int main(void) {
    int n, m, k, t;
    scanf("%d%d%d%d", &n, &m, &k, &t);
    vector<int> skills(n), diffs(m);
    for (int &s: skills) scanf("%d", &s);
    for (int &d: diffs) scanf("%d", &d);

    unordered_set<int> poss_diffs;
    poss_diffs.insert(0);
    for (int d: diffs) {
        auto old_diffs = poss_diffs;
        for (int x: old_diffs)
            if (x+d <= t) poss_diffs.insert(x+d);
    }
    vector<int> skill_separators;
    for (int d: poss_diffs)
        if (d) skill_separators.push_back(t / d);
    sort(skill_separators.begin(), skill_separators.end());
    skill_separators.resize(unique(skill_separators.begin(), skill_separators.end()) - skill_separators.begin());
    skill_separators.push_back(1<<30);

    vector<int> best(n+1, n);
    best[n] = 0;
    for (int i = n-1; i >= 0; --i) {
        int min_skill = skills[i];
        auto sep_it = upper_bound(skill_separators.begin(), skill_separators.end(), skills[i]);
        priority_queue<int> winners;
        for (int j = i; j < n; ++j) {
            winners.push(skills[j]);
            min_skill = min(min_skill, skills[j]);
            while (sep_it != skill_separators.begin() && *(sep_it-1) >= min_skill)
                --sep_it;
            while (winners.top() > *sep_it)
                winners.pop();
            best[i] = min(best[i], (int)winners.size() + best[j+1]);
        }
    }
    printf("%d\n", max(k, best[0]));
}
