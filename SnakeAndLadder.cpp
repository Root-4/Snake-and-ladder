#include <iostream>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;
#define N 100

// Data structure to store a graph edge
struct Edge
{
    int src, dest;
};

// A class to represent a graph object
class Graph
{
public:
    // a vector of vectors to represent an adjacency list
    vector<int> adjList[N + 1];

    // Constructor
    Graph(vector<Edge> const &edges)
    {
        // add edges to the graph
        for (Edge edge : edges)
        {
            // Please note that the graph is directed
            adjList[edge.src].push_back(edge.dest);
        }
    }
};

// A queue node
struct Node
{
    // stores number associated with graph node
    int ver;

    // `min_dist` stores the minimum distance of a node from the starting vertex
    int min_dist;
};

// Perform BFS on graph `g` starting from a given source vertex
int BFS(Graph const &g, int source)
{
    // create a queue for doing BFS
    queue<Node> q;

    // to keep track of whether a vertex is discovered or not
    vector<bool> discovered(N + 1);

    // mark the source vertex as discovered
    discovered[source] = true;

    // assign the minimum distance of the source vertex as 0 and
    // enqueue it
    Node node = {source, 0};
    q.push(node);

    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node
        node = q.front();
        q.pop();

        // Stop BFS if the last node is reached
        if (node.ver == N)
        {
            return node.min_dist;
        }

        // do for every adjacent node of the current node
        for (int u : g.adjList[node.ver])
        {
            if (!discovered[u])
            {
                // mark it as discovered and enqueue it
                discovered[u] = true;

                Node n = {u, node.min_dist + 1};
                q.push(n);
            }
        }
    }
}

int findMinimumMoves(unordered_map<int, int> &ladder, unordered_map<int, int> &snake)
{
    // find all edges involved and store them in a vector
    vector<Edge> edges;
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= 6 && i + j <= N; j++)
        {
            int src = i;

            // update destination if there is any ladder
            // or snake from the current position.
            int dest = (ladder[i + j] || snake[i + j]) ? (ladder[i + j] + snake[i + j]) : (i + j);

            // add an edge from src to dest
            Edge e = {src, dest};
            edges.push_back(e);
        }
    }

    // construct a directed graph
    Graph g(edges);

    // Find the shortest path between 1 and 100 using BFS
    return BFS(g, 0);
}
int playSnakeAndLadder(unordered_map<int, int> &ladder, unordered_map<int, int> &snake)
{
    int player1 = 1, player2 = 1, chance1 = 0, chance2 = 0; // Initial position of players
    int chance = 0;                                         // This value show the change of players if chance is odd then player1 will play
    srand(time(0));                                         // if chance is even then player2 will play
    while (1)
    {

        if ((player1 == 100) || (player2 == 100)) // if any of player's position is 100 return chance;
            return chance;                        // Here chance shows who win the game, if chance is even player1 wins other //wise player2 wins
        int roll = rand() % 6 + 1;                // this will generate random number from 1 to 6.
        if (chance % 2 == 0)
        {
            if (chance1 == 30)
            {
                cout << "Player 1 won by because he reached 30 chances";
                return chance;
            }
            int key = roll + player1; // new position of player1
            bool isLadder = false;    // This is for checking the turn current player if againTurn is ture
            // then the current player will player again.
            if (ladder.find(key) != ladder.end() || snake.find(key) != snake.end())
            {
                if (ladder.find(key) != ladder.end())
                {
                    player1 = ladder[key];
                    isLadder = true;
                }
                else
                    player2 = snake[key];
                // Here player current position will automatically update according to the hashMap.
                // if there is a snake the key value is greater than it mapping value.
                // if there is a ladder then key value is less than it mapping value.
                if (isLadder == true && roll == 6 || isLadder == true)
                    chance = chance;
                else
                    chance = (chance + 1) % 2;
            }
            else if (player1 + roll > 100 && roll != 6)
                chance = (chance + 1) % 2;
            else if (player1 + roll > 100 && roll == 6)
                chance = chance;
            else if (roll == 6)
            {
                player1 = player1 + roll;
                chance = chance;
            }
            else
            {
                player1 = player1 + roll;
                chance = (chance + 1) % 2;
            }
            cout << "Player 2 got " << roll << " on dice and Position of Player 2 is:" << player2 << endl;
            chance1++;
        }

        else
        { // Now similarly for player2
            {
                int key = roll + player2; // new position of player2
                bool isLadder = false;    // This is for checking the turn current player if againTurn is ture
                // then the current player will player again.
                if (chance2 == 30)
                {
                    cout << "Player 2 won by because he reached 30 chances";
                    return chance;
                }
                if (ladder.find(key) != ladder.end() || snake.find(key) != snake.end())
                {
                    if (ladder.find(key) != ladder.end())
                    {
                        player1 = ladder[key];
                        isLadder = true;
                    }
                    else
                        player2 = snake[key];
                    // Here player current position will automatically update according to the hashMap.
                    // if there is snake the key value is greater than it mapping value.
                    // if there is ladder then key value is less than it mapping value.
                    if (isLadder == true && roll == 6 || isLadder == true)
                        chance = chance;
                    else
                        chance = (chance + 1) % 2;
                }
                else if (player2 + roll > 100 && roll != 6)
                    chance = (chance + 1) % 2;
                else if (player2 + roll > 100 && roll == 6)
                    chance = chance;
                else if (roll == 6)
                {
                    player2 = player2 + roll;
                    chance = chance;
                }
                else
                {
                    player2 = player2 + roll;
                    chance = (chance + 1) % 2;
                }
            }
            cout << "Player 2 got " << roll << " on dice and Position of Player 2 is:" << player2 << endl;
            chance2++;
        }
    }
}
int show()
{
    cout << "1:add snake/table" << endl;
    cout << "2:remove snake/table" << endl;
    cout << "3:Find minimum number of moved required" << endl;
    cout << "4:Start the game" << endl;
    cout << "5:Exit" << endl;
    int c;
    cin >> c;
    return c;
}

int main()
{
    // snakes and ladders are represented using a map
    unordered_map<int, int> ladder, snake;
    cout << "-------------------------index-----------------------" << endl;
    int c = show();
    ladder[12] = 32;
    ladder[45] = 70;
    ladder[80] = 95;
    snake[93] = 6;
    snake[85] = 19;
    snake[75] = 27;
    while (c < 5 && c > 0)
    {
        switch (c)
        {
        case 1:
        {
            int start, end;
            cout << "Enter starting and end point of snake or ladder" << endl;

            cin >> start >> end;
            if (start < end)
                ladder[start] = end;
            else
                snake[start] = end;
            break;
        }
        case 2:
        {
            int start;
            cout << "Enter the start of snake or ladder to delete" << endl;
            cin >> start;
            if (ladder.find(start) == ladder.end())
                ladder.erase(start);
            else if (snake.find(start) == snake.end())
                snake.erase(start);
            else
                cout << "No snake and ladder with this starting" << endl;
            break;
        }
        case 3:
        {
            cout << "Minimum moves are " << findMinimumMoves(ladder, snake) << endl;
        }
        break;
        case 4:
        {
            cout << "Game Started" << endl;
            int chance = playSnakeAndLadder(ladder, snake);
            if (chance % 2 == 0)
                cout << "Player 1 WON" << endl;
            else
                cout << "Player 2 WON" << endl;
        }
        break;
        case 5:
            return 0;
        }
        c = show();
    }
    cout << "Wrong input";
    return 0;
}