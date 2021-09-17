#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>
#include<windows.h>
#define BOX 219

using namespace std;

const int N = 32;
char lab[N][N];

void show()
{
    cout << endl << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (char)lab[i][j];
        }
        cout << endl;
    }
}

void init()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            lab[i][j] = 0;
            if (i == 0 || i == N - 1) lab[i][j] = BOX;
        }
        lab[i][0] = BOX;
        lab[i][N - 1] = BOX;
    }
}


int rndEven(int s, int k)
{
    vector<int> v;
    for (int i = s; i < k; i++)
    {
        if (i % 2 == 0) v.push_back(i);
    }
    random_shuffle(v.begin(), v.end());
    return v[0];
}

int rndOdd(int s, int k)
{
    vector<int> v;
    for (int i = s; i < k; i++)
    {
        if (i % 2 == 1) v.push_back(i);
    }
    random_shuffle(v.begin(), v.end());
    return v[0];
}

void divide(int xp, int yp, int xk, int yk)
{

    int sciana;
    int przejscie;
    if (xk - xp >= yk - yp)
    {
        if (xk - xp > 3)
        {
            sciana = rndEven(xp + 1, xk - 1);

            for (int i = yp; i < yk; i++)
                lab[i][sciana] = BOX;
            przejscie = rndOdd(yp, yk);
            lab[przejscie][sciana] = ' ';

            divide(xp, yp, sciana, yk);
            divide(sciana, yp, xk, yk);
        }
    }
    else if (xk - xp < yk - yp)
    {
        if (yk - yp > 3)
        {
            sciana = rndEven(yp + 1, yk - 1);
            for (int i = xp; i < xk; i++)
                lab[sciana][i] = BOX;
            przejscie = rndOdd(xp, xk);
            lab[sciana][przejscie] = ' ';

            divide(xp, yp, xk, sciana);
            divide(xp, sciana, xk, yk);
        }

    }
}

int main()
{
    srand(time(NULL));

    init();
    divide(1, 1, N - 1, N - 1);
    show();



}