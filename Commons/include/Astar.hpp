//
// Created by veyrie_f on 3/17/16.
//

#ifndef CPP_ARCADE_ASTAR_HPP
#define CPP_ARCADE_ASTAR_HPP

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>

class Astar
{
private:
    class node
    {
    private:
        // current position
        int xPos;
        int yPos;
        // total distance already travelled to reach the node
        int level;
        // priority=level+remaining distance estimate
        int priority;  // smaller: higher priority

    public:
        // Determine priority (in the priority queue)
        bool operator<(const node & b) const
        {
            return getPriority() > b.getPriority();
        }

        node(int xp, int yp, int d, int p)
        {
            xPos = xp;
            yPos = yp;
            level = d;
            priority = p;
        }

        int getxPos() const
        {
            return xPos;
        }
        int getyPos() const
        {
            return yPos;
        }
        int getLevel() const
        {
            return level;
        }
        int getPriority() const
        {
            return priority;
        }

        void updatePriority(const int & xDest, const int & yDest)
        {
            priority = level + estimate(xDest, yDest) * 10; //A*
        }

        // give better priority to going strait instead of diagonally
        void nextLevel(const int &) // i: direction
        {
            level += 10;
        }

        // Estimation function for the remaining distance to the goal.
        const int & estimate(const int & xDest, const int & yDest)
        {
            xd = xDest - xPos;
            yd = yDest - yPos;

            // Euclidian Distance
            d = static_cast<int>(sqrt(xd * xd + yd * yd));

            // Manhattan distance
            //d=abs(xd)+abs(yd);

            // Chebyshev distance
            //d=max(abs(xd), abs(yd));

            return d;
        }

    private:
        int xd;
        int yd;
        int d;
    };

public:
    Astar(char _map[31][51])
    {
        for (int y = 0; y < 31; y++)
        {
            for (int x = 0; x < 51; x++)
            {
                map[x][y] = _map[y][x];
            }
        }
    }
    virtual ~Astar()
    {}

public:
    // A-star algorithm.
    // The route returned is a string of direction digits.
    std::string const pathFind(int xStart, int yStart, int xFinish, int yFinish)
    {
        std::priority_queue<node> pq[2]; // list of open (not-yet-tried) nodes
        int pqi; // pq index
        node* n0;
        node* m0;
        int i;
        int j;
        int x;
        int y;
        int xdx, ydy;
        char c;

        pqi = 0;

        // reset the node maps
        for (y = 0; y < m; y++)
        {
            for ( x = 0; x < n; x++)
            {
                closed_nodes_map[x][y] = 0;
                open_nodes_map[x][y] = 0;
            }
        }

        // create the start node and push into list of open nodes
        n0 = new node(xStart, yStart, 0, 0);
        n0->updatePriority(xFinish, yFinish);
        pq[pqi].push(*n0);
        // Used to be x and y (oob)
        open_nodes_map[xStart][yStart] = n0->getPriority(); // mark it on the open nodes map

        // A* search
        while (!pq[pqi].empty())
        {
            // get the current node w/ the highest priority
            // from the list of open nodes
            n0 = new node(pq[pqi].top().getxPos(), pq[pqi].top().getyPos(),
                          pq[pqi].top().getLevel(), pq[pqi].top().getPriority());

            x=n0->getxPos();
            y=n0->getyPos();

            pq[pqi].pop(); // remove the node from the open list
            open_nodes_map[x][y]=0;
            // mark it on the closed nodes map
            closed_nodes_map[x][y]=1;

            // quit searching when the goal state is reached
            //if((*n0).estimate(xFinish, yFinish) == 0)
            std::string path = "";

            if (x == xFinish && y == yFinish)
            {
                // generate the path from finish to start
                // by following the directions
                while (!(x == xStart && y == yStart))
                {
                    j = dir_map[x][y];
                    c = '0' + (j + dir / 2) % dir;
                    path = c + path;
                    x += dx[j];
                    y += dy[j];
                }

                // garbage collection
                delete n0;
                // empty the leftover nodes
                while (!pq[pqi].empty())
                {
                    pq[pqi].pop();
                }
                return path;
            }

            // generate moves (child nodes) in all possible directions
            for (i = 0; i < dir; i++)
            {
                xdx = x + dx[i];
                ydy=y+dy[i];

                if (!(xdx < 0 || xdx > n - 1 || ydy < 0 || ydy > m - 1 || map[xdx][ydy]=='X'// 1
                     || closed_nodes_map[xdx][ydy] == 1))
                {
                    // generate a child node
                    m0=new node(xdx, ydy, n0->getLevel(), n0->getPriority());
                    m0->nextLevel(i);
                    m0->updatePriority(xFinish, yFinish);

                    // if it is not in the open list then add into that
                    if (open_nodes_map[xdx][ydy]==0)
                    {
                        open_nodes_map[xdx][ydy] = m0->getPriority();
                        pq[pqi].push(*m0);
                        // mark its parent node direction
                        dir_map[xdx][ydy] = (i + dir / 2) % dir;
                    }
                    else if (open_nodes_map[xdx][ydy]>m0->getPriority())
                    {
                        // update the priority info
                        open_nodes_map[xdx][ydy] = m0->getPriority();
                        // update the parent direction info
                        dir_map[xdx][ydy] = (i + dir / 2) % dir;

                        // replace the node
                        // by emptying one pq to the other one
                        // except the node to be replaced will be ignored
                        // and the new node will be pushed in instead
                        while (!(pq[pqi].top().getxPos()==xdx &&
                                pq[pqi].top().getyPos()==ydy))
                        {
                            pq[1 - pqi].push(pq[pqi].top());
                            pq[pqi].pop();
                        }
                        pq[pqi].pop(); // remove the wanted node

                        // empty the larger size pq to the smaller one
                        if (pq[pqi].size() > pq[1-pqi].size())
                        {
                            pqi = 1 - pqi;
                        }
                        while (!pq[pqi].empty())
                        {
                            pq[1 - pqi].push(pq[pqi].top());
                            pq[pqi].pop();
                        }
                        pqi = 1 - pqi;
                        pq[pqi].push(*m0); // add the better node instead
                    }
                    else
                    {
                        delete m0;
                    }
                }
            }
            delete n0;
        }
        return ""; // no route found
    }

private:
    const int n = 51; // Horizontal
    const int m = 31; // Vertical
    char map[51][31];
    int closed_nodes_map[51][31];
    int open_nodes_map[51][31];
    int dir_map[51][31];
    const int dir = 4;
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, 1, 0, -1};

};

#endif //CPP_ARCADE_ASTAR_HPP
