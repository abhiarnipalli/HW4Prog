//
// Created by Abhlash Arnipalli on 5/2/23.
//
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;

pair< vector<float>, vector<int> >  WWWWW(vector<float> w, vector<float> p , int s, int t){



    int j = w.size() - 1; // number of questions
    vector<vector<float>> dp(j + 1, vector<float>(j + 1)); // dp table
    vector<vector<int>> next(j + 1, vector<int>(j + 1)); // for storing the next optimal decision
    vector<float> E(j + 1); // expected amount of money
    vector<int> quit(j + 1); // 1 if the contestant should quit at question i, 0 otherwise

    // initialize the dp table
    for (int i = 0; i <= j; i++) {
        for (int k = i; k <= j; k++) {
            if (k == 0) {
                dp[i][k] = 1; // base case
            }
            else if (i == 0) {
                dp[i][k] = 0; // base case
            }
            else {
                dp[i][k] = max(dp[i - 1][k - 1] * p[k] + dp[i][k - 1] * (1 - p[k]), w[i]); // recurrence
                next[i][k] = (dp[i - 1][k - 1] * p[k] + dp[i][k - 1] * (1 - p[k]) >= w[i]); // update next
            }
        }
        E[i] = dp[i][j]; // update expected amount of money
    }

    // determine when to quit
    int k = j;
    for (int i = j; i >= 1; i--) {
        if (i >= s && E[i] >= w[t]) { // quit if we are above the safety line
            quit[i] = 1;
            k = i - 1;
        }
        else if (E[i] < w[s]) { // quit if we are below the lower threshold
            quit[i] = 1;
            k = i - 1;
        }
        else { // continue otherwise
            quit[i] = 0;
        }
    }

    // return the results
    return make_pair(E, quit);





}







pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_1(vector<float> w, vector<float> p, int s, int t)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}

pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float> w, vector<float> p, int s, int t)
{
    vector < vector<float> > fres;
    vector < vector<int> > fres2;

    vector <float> res0;
    vector <int> res1;

    res0.push_back(1.0);
    res0.push_back(2.0);
    res1.push_back(1);

    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres.push_back(res0);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);
    fres2.push_back(res1);

    return make_pair(fres, fres2);
}