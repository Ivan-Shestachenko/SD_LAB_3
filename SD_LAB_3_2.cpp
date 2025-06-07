#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

// Структура для узла списка
struct Node
{
    int x;
    int y;
    Node *next;

    Node(int x, int y) : x(x), y(y), next(nullptr) {}
};

// Функция для определения, был ли король на этой позиции ранее
bool visitedBefore(Node *head, int x, int y)
{
    Node *current = head;
    while (current != nullptr)
    {
        if (current->x == x && current->y == y)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Функция для освобождения памяти, занятой списком
void deleteList(Node *head)
{
    while (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int n;
    cout << "Введите количество ходов (N): ";
    cin >> n;

    vector<string> moves(n);
    cout << "Введите последовательность ходов (u, d, l, r, ul, ur, dl, dr), каждый на новой строке: " << endl;
    for (int i = 0; i < n; ++i)
    {
        cin >> moves[i];
    }

    int x = 0; // Начальная позиция короля
    int y = 0;

    // Начало связанного списка с нулевой позицией
    Node *head = new Node(x, y);

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
            deleteList(head); 
            return 1;
        }

        if (visitedBefore(head, x, y))
        {
            visitedTwice = true;
            break;
        }
        else
        {
            Node *newNode = new Node(x, y);
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    auto stop = high_resolution_clock::now(); 

    auto duration = duration_cast<microseconds>(stop - start);

    if (visitedTwice)
    {
        cout << "Король побывал на одном и том же поле дважды." << endl;
    }
    else
    {
        cout << "Король не был на одном и том же поле дважды." << endl;
    }

    cout << "Время выполнения: " << duration.count() << " мс" << endl;

    deleteList(head);

    return 0;
}
