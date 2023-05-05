#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

pair< vector<float>, vector<int> >  WWWWW(vector<float>, vector<float>, int, int);
pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_1(vector<float>, vector<float>, int, int);
pair< vector< vector<float> > , vector< vector<int> > >  WWWWW_2(vector<float>, vector<float>, int, int);

int main()
{
    int j, s, t;
    cin >> j >> s >> t;
    vector<float> w;
    vector<float> p;

    // push back 0 to entry 0, as there is no question 0
    w.push_back(0.0);
    p.push_back(0.0);

    for (int i = 0; i < j ; i++)
    {
        float s;
        cin >> s;
        w.push_back(s);
    }
    for (int i = 0; i < j ; i++)
    {
        float s;
        cin >> s;
        if (s < 0.25)
            s = 0.25;
        if (s > 0.9999)
            s = 0.9999;
        p.push_back(s);
    }

    pair< vector<float>, vector<int> > res_base = WWWWW(w, p, s, t);

    cout << "\nBase case : \n\n";
    for (int i = 0; i < res_base.first.size(); i++)
    {
        float x = round(res_base.first[i] * 1000) / 1000.0;
        cout << x << " ";
    }
    cout << endl;
    for (int i = 0; i < res_base.second.size(); i++)
    {
        cout << res_base.second[i] << " ";
    }
    cout << endl;

//    pair< vector< vector<float> > , vector< vector<int> > > res_extra1 = WWWWW_1(w, p, s, t);
//
//    cout << "\nBonus 1 : \n\n";
//    for (int k = 0; k <= 1; k++)
//    {
//        for (int i = 0; i < res_extra1.first[k].size(); i++)
//        {
//            float x = round(res_extra1.first[k][i] * 1000) / 1000.0;
//            cout << x << " ";
//        }
//        cout << endl;
//    }
//    for (int k = 0; k <= 1; k++)
//    {
//        for (int i = 0; i < res_extra1.second[k].size(); i++)
//        {
//            cout << res_extra1.second[k][i] << " ";
//        }
//    }
//    cout << endl;
//
//    cout << "\nBonus 2 : \n\n";
//    pair< vector< vector<float> > , vector< vector<int> > > res_extra2 = WWWWW_2(w, p, s, t);
//
//    for (int k = 0; k <= 3; k++)
//    {
//        for (int i = 0; i < res_extra2.first[k].size(); i++)
//        {
//            float x = round(res_extra2.first[k][i] * 1000) / 1000.0;
//            cout << x << " ";
//        }
//        cout << endl;
//    }
//    for (int k = 0; k <= 3; k++)
//    {
//        for (int i = 0; i < res_extra2.second[k].size(); i++)
//        {
//            cout << res_extra2.second[k][i] << " ";
//        }
//    }
//    cout << endl;


    return 0;
}
