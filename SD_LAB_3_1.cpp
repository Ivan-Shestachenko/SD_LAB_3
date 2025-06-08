#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// Функция для определения, был ли король на этой позиции ранее
bool visitedBefore(const vector<pair<int, int>> &visitedPositions, int x, int y)
{
    for (const auto &pos : visitedPositions)
    {
        if (pos.first == x && pos.second == y)
        {
            return true;
        }
    }
    return false;
}

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

    int x = 0; // Начальная позиция короля
    int y = 0;
    vector<pair<int, int>> visitedPositions;
    visitedPositions.push_back({x, y}); 

    auto start = high_resolution_clock::now(); // Время начала обработки ходов

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

        if (visitedBefore(visitedPositions, x, y))
        {
            visitedTwice = true;
            break;
        }
        else
        {
            visitedPositions.push_back({x, y});
        }
    }

    auto stop = high_resolution_clock::now(); // Время окончания
    auto duration = duration_cast<microseconds>(stop - start);

    if (visitedTwice)
    {
        cout << "The King visited the same field twice." << endl;
    }
    else
    {
        cout << "The King DON'T visited the same field twice." << endl;
    }

    cout << "Time: " << duration.count() << "ms" << endl;

    return 0;
}
