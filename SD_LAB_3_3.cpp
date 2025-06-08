#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

int main()
{
    int n;
    cout << "Enter the number of moves (N): ";
    cin >> n;

    vector<string> moves(n);
    cout << "Enter the sequence of moves (u(up), d(down), l(left), r(right), ul(up-left), ur(up-right), dl(down-left), dr(down-right)), each on a new line: " << endl;
    for (int i = 0; i < n; ++i)
    {
        cin >> moves[i];
    }

    int x = 0; 
    int y = 0;

    // std::set для хранения посещенных позиций
    set<pair<int, int>> visitedPositions;
    visitedPositions.insert({x, y}); 

    auto start = high_resolution_clock::now(); 

    bool visitedTwice = false;
    for (const string &move : moves)
    {
        if (move == "u")
        {
            y++;
        }
        else if (move == "d")
        {
            y--;
        }
        else if (move == "l")
        {
            x--;
        }
        else if (move == "r")
        {
            x++;
        }
        else if (move == "ul")
        {
            x--;
            y++;
        }
        else if (move == "ur")
        {
            x++;
            y++;
        }
        else if (move == "dl")
        {
            x--;
            y--;
        }
        else if (move == "dr")
        {
            x++;
            y--;
        }
        else
        {
            cout << "Некорректный ход: " << move << endl;
            return 1;
        }

        if (visitedPositions.count({x, y}))
        {
            visitedTwice = true;
            break;
        }
        else
        {
            visitedPositions.insert({x, y});
        }
    }

    auto stop = high_resolution_clock::now(); 

    auto duration = duration_cast<microseconds>(stop - start);

    if (visitedTwice)
    {
        cout << "The king visited the same field twice." << endl;
    }
    else
    {
        cout << "The king DON'T visited the same field twice." << endl;
    }

    cout << "Time: " << duration.count() << " ms" << endl;

    return 0;
}
