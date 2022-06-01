#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;
#include <stdlib.h>
#include <iomanip>

class Node {
    public:
        friend ostream& operator<<(ostream &os, const Node &node);
        bool operator==(const Node &node) const;
        Node(int x, int y, bool isWall);
        ~Node();
        void setG(int g);
        void setH(int h);
        void setX(const int x);
        void setY(const int y);
        void setIsWall(bool isWall);
        void setParent(Node *parent);
        int getX() const;
        int getY() const;
        int getGCost() const;
        int getHCost() const;
        int getFCost() const;
        bool isWall() const;        
        Node *getParent() const;
    private:
        int x;
        int y;
        bool wall;
        //the distance from the start node
        int g;
        //the distance from the target(end) node
        int h;
        Node *parent;
};

#endif