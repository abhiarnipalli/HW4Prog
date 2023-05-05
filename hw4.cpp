//
// Created by Abhlash Arnipalli on 5/2/23.
//

#include <vector>
#include <utility>
using namespace std;

pair< vector<float>, vector<int>>  WWWWW(vector<float> w, vector<float> p , int s, int t)
{
    int j = w.size() - 1;
    vector<vector<float>> dp(j + 1, vector<float>(j + 1, 0.0));
    vector<vector<int>> path(j + 1, vector<int>(j + 1, 0));

    // Fill in the base cases for the DP matrix
    for (int i = 0; i <= s; i++) {
        dp[i][0] = 0.0;
        path[i][0] = 0;
    }
    for (int i = s + 1; i <= t; i++) {
        dp[i][0] = w[i - 1];
        path[i][0] = i - 1;
    }
    for (int i = t + 1; i <= j; i++) {
        dp[i][0] = w[t];
        path[i][0] = t;
    }

    // Use Floyd Warshall to fill in the DP matrix
    for (int k = 0; k <= j; k++) {
        for (int i = 1; i <= j; i++) {
            for (int l = s; l < i; l++) {
                float value = p[i] * (w[i] + dp[l][k]) + (1.0 - p[i]) * dp[i][0];
                if (value > dp[i][k + 1]) {
                    dp[i][k + 1] = value;
                    path[i][k + 1] = l;
                }
            }
            if (dp[i][k + 1] < dp[i][k]) {
                dp[i][k + 1] = dp[i][k];
                path[i][k + 1] = path[i][k];
            }
        }
    }

    // Calculate the expected amount of money won
    vector<float> money_Won(j + 1, 0.0);
    for (int k = 0; k <= j; k++) {
        for (int i = s; i <= t; i++) {
            if (dp[i][k] > money_Won[k]) {
                money_Won[k] = dp[i][k];
            }
        }
    }

    // Calculate the quit/not-quit decision for each question
    vector<int> decision(j + 1, 0);
    int curr = j;
    for (int k = j; k >= 1; k--) {
        if (path[curr][k] < s) {
            break;
        }
        if (path[curr][k] < t || curr == t) {
            decision[curr - 1] = 1;
        }
        curr = path[curr][k];
    }

    return make_pair(money_Won, decision);
}











//BONUS1
pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_1(vector<float> w, vector<float> p, int s, int t)
{
    int n = w.size();
    vector<vector<float>> a(2, vector<float>(n));
    vector<vector<int>> b(2, vector<int>(n - 1));

    // Compute a[0]
    a[0][0] = s * w[0];
    for (int i = 1; i < n; i++) {
        a[0][i] = a[0][i - 1] + w[i] * pow(p[i - 1], i) * (1 - p[i - 1]);
    }

    // Compute b[0]
    for (int i = 0; i < n - 1; i++) {
        if (a[0][i] >= t) {
            b[0][i] = 0;
        } else {
            b[0][i] = 1;
        }
    }

    // Compute a[1] and b[1]
    float plifeline = 0.5 + p[0] / 2.0;
    if (plifeline > 0.999) {
        plifeline = 0.999;
    }
    a[1][0] = s * w[0] * plifeline + (1 - plifeline) * a[0][0];
    for (int i = 1; i < n; i++) {
        float prevprob = (i == 1) ? plifeline : pow(p[i - 2], i - 1) * (1 - p[i - 2]);
        float currprob = pow(p[i - 1], i);
        float probused = currprob * (1 - prevprob);
        float newprob = plifeline + (1 - plifeline) * currprob / prevprob / 2.0;
        if (newprob > 0.999) {
            newprob = 0.999;
        }
        float expmoneyused = w[i] * newprob + (1 - newprob) * a[0][i];
        float expmoneynotused = w[i] * plifeline + (1 - plifeline) * a[0][i];
        if (expmoneyused > expmoneynotused) {
            a[1][i] = expmoneyused;
            b[1][i - 1] = 2;
        } else {
            a[1][i] = expmoneynotused;
            b[1][i - 1] = 1;
        }
    }
    return make_pair(a, b);
}






//BONUS2
pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float> w, vector<float> p, int s, int t)
{
    int n = w.size();

    // Initialize the arrays
    vector<vector<float>> a(4, vector<float>(n+1));
    vector<vector<int>> b(4, vector<int>(n));

    // Set the initial values
    a[0][0] = s;
    for (int i = 1; i <= n; i++) {
        a[0][i] = a[0][i-1] + w[i-1];
    }

    // Loop over the questions
    for (int i = 1; i <= n; i++) {

        // No lifeline available
        a[1][i] = max(a[0][i-1], a[1][i-1] + w[i-1]*p[i-1]);
        b[1][i-1] = (a[1][i] == a[0][i]) ? 0 : 1;

        // Get easier lifeline available
        float pe = min(0.999f, p[i-1]*0.5f + 0.5f);
        a[2][i] = max(a[0][i-1], a[2][i-1] + w[i-1]*pe);
        b[2][i-1] = (a[2][i] == a[0][i]) ? 0 : ((a[2][i] == a[1][i]) ? 1 : 2);

        // Get through lifeline available
        float pt = 1.0f;
        if (i > 1) {
            pt = max(0.0f, 1.0f - (i-2)*0.1f);
        }
        a[3][i] = max(a[0][i-1], a[3][i-1] + w[i-1]*pt - (i-1)*10.0f);
        b[3][i-1] = (a[3][i] == a[0][i]) ? 0 : ((a[3][i] == a[1][i]) ? 1 : ((a[3][i] == a[2][i]) ? 2 : 3));
    }

    return make_pair(a, b);
}