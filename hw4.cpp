

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
using namespace std;



pair< vector<float>, vector<int> > WWWWW(vector<float> w, vector<float> p , int s, int t)
{
    int j = w.size() ;
    vector<float> winnings(j + 1);
    vector<int> quit(j + 1);
    for(int i = 0; i < quit.size(); i++){
        quit[i] = 1;
    }

    for (int k = j; k >= 0; k--) {
        float q;
        if (k <= 5){
            q = 0;
        }
        else if (k <= 10){
            q = w[5];
        }
        else {
            q = w[10];
        }

        cout << "Values: " << k << " - " << w[k] << " - " << p[k] << " - " << winnings[k + 1] << " - " << q << endl;
        float win_by_quitting = w[k - 1]; // calculate win by quitting
        float win_by_answering = p[k] * winnings[k + 1] + (1 - p[k]) * q; // calculate win by answering

        if (k == j){
            winnings[k] = win_by_quitting;
        }
        else if (win_by_quitting > win_by_answering) {
            winnings[k] = win_by_quitting;
            quit[k] = 0;
        }
        else {
            winnings[k] = win_by_answering;

        }
    }

    if (winnings[0] == 0) {
        winnings.erase(winnings.begin());
        quit.erase(quit.begin());
    }

    return {winnings, quit};
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