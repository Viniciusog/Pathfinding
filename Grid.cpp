#include "Grid.h"

Grid::Grid(int unitSize, int screenWidth, int screenHeight) 
    : Matrix(screenHeight / unitSize, screenWidth / unitSize) {
    
    this->start = nullptr;
    this->end = nullptr;

    int lines = screenHeight / unitSize;
    int columns = screenWidth / unitSize;
    this->unitSize = unitSize;
    this->setEndPoint(nullptr);
    setWidth(screenWidth);
    setHeight(screenHeight);
}

Grid::~Grid() {
    cout << "Grid destructor" << endl;
}

void Grid::setUnitSize(int unitSize) {
    this->unitSize = unitSize;
}

void Grid::setWidth(int width) {
    this->width = width;
}

void Grid::setHeight(int height) {
    this->height = height;
}

void Grid::setStartPoint(Node *start) {
    // when click is out of the screen
    if (start != nullptr) {
        start->setG(0);
        start->setH(27);
    }
    this->start = start;
}

void Grid::setEndPoint(Node *end) {
    this->end = end;
}

int Grid::getWidth() const {
    return this->width;
}

Node *Grid::getStartPoint() const {
    return this->start;
}

Node *Grid::getEndPoint() const {
    return this->end;
}

int Grid::getHeight() const {
    return this->height;
}

int Grid::getUnitSize() const {
    return this->unitSize;
}

bool Grid::isEndNode(Node *node) const {
    if (this->getEndPoint() != nullptr) {
        return *this->getEndPoint() == *node;
    }
    return false;
}

bool Grid::isStartNode(Node *node) const {
    if (this->getStartPoint() != nullptr) {
        return *this->getStartPoint() == *node;
    }
    return false;
}

/**
 * @details Generate matrix of nodes
 */
void Grid::initGrid() {
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            Node *node = new Node(j*unitSize, i*unitSize, false);
            add(node, i, j);
        }
    }
}

void Grid::saveInFile() const {
    ofstream file("saida.txt");
    file.clear();
    ValidElement<Node*> value;
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            value = at(i, j);
            int isWall = value.getElement()->isWall();
            /* if is the last column */
            if (j == getColumns() - 1) {
               file << isWall;  
            } else {
               file << isWall << ",";
            } 
        }   
        file << endl;
    }
    cout << "saved in file" << endl;
}

/* void Grid::readFromFile() {
    ifstream myFile("lab.txt");
    std::string myLine;
    int indexChar;
    int indexStart = 0;
    while (myFile.good()) {
        getline(myFile, myLine);
        indexChar = myLine.find(",");
        while (indexChar != std::string::npos) {
            string substring = myLine.substr(indexStart, indexChar);
            cout << "Substring: " << substring << endl;
            // the next start is after ,
            indexStart = indexChar + 1;
        }
    }
    

    for (int i = 0; i < this->getLines(); i++) {
        for (int j = 0; j < this->getColumns(); j++) {
            Node *node = at(i, j);
            node->setIsWall(true);
        }
    }
} */

/**
 * @details Draw lines and nodes to the window
 */
void Grid::drawTo(vector<Node *> path, sf::RenderWindow &window) {
    /* DRAW NODES */
    sf::RectangleShape rect;
    rect.setSize({(float) unitSize, (float) unitSize});
    
  
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            //just get the element because we know the line and col are valid
            Node *node = at(i, j).getElement();
            rect.setPosition({(float)node->getX(), (float)node->getY()});
            
            if (node->isWall()) { 
                rect.setFillColor(sf::Color::Black);          
            } else if (isEndNode(node)) {
                rect.setFillColor(sf::Color::Cyan);
            } else if (isStartNode(node)) {
                rect.setFillColor(sf::Color::Magenta);
            } else {
                rect.setFillColor(sf::Color::Green);
            } 
            window.draw(rect);
        }
    } 
    
    for (int i = 0; i < path.size(); i++) {
        rect.setPosition({(float)path.at(i)->getX(), (float)path.at(i)->getY()});
        rect.setFillColor(sf::Color::Blue);     
        window.draw(rect);
    }

    /* DRAW LINES */
    sf::RectangleShape horizontalLine;
    for (int i = 0; i < getLines(); i++) {
        horizontalLine.setSize({(float) getWidth(), 1.0});
        horizontalLine.setPosition(0, i*unitSize);
        window.draw(horizontalLine);
    }

    sf::RectangleShape verticalLine;
    for(int i = 0; i < getColumns(); i++) {
        verticalLine.setSize({1.0,(float) getHeight()});
        verticalLine.setPosition({(float)i*unitSize, 0.0});
        window.draw(verticalLine);
    }

    //last vertical line
    verticalLine.setPosition({(float) window.getSize().x - 1, 1.0});
    window.draw(verticalLine);

    //last horizontal line
    horizontalLine.setPosition({0, (float) window.getSize().y - 1});
    window.draw(horizontalLine);
}

void Grid::drawFindingPath(vector<Node *> openList, vector<Node *> closedList, sf::RenderWindow &window) {
    sf::RectangleShape rect;
    rect.setSize({(float) this->getColumns() * unitSize, (float) this->getLines() * unitSize});
    rect.setFillColor(sf::Color::Green);
    window.draw(rect);

    rect.setSize({(float) unitSize, (float) unitSize});

    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            //just get the element because we know the line and col are valid
            Node *node = at(i, j).getElement();
            rect.setPosition({(float)node->getX(), (float)node->getY()});
            
            if (node->isWall()) { 
                // cout <<  "É parede! " << endl;
                rect.setFillColor(sf::Color::Black); 
                window.draw(rect);         
            } else if (isEndNode(node)) {
                rect.setFillColor(sf::Color::Cyan);
                window.draw(rect);   
            } else if (isStartNode(node)) {
                rect.setFillColor(sf::Color::Magenta);
                window.draw(rect);   
            }          
        }
    } 

    for (int i = 0; i < openList.size(); i++) {
        Node *node = openList.at(i);
        if (*node == *getStartPoint() || *node == *getEndPoint()) {
            continue;
        }
        rect.setPosition({(float)node->getX(), (float)node->getY()});
        rect.setFillColor(sf::Color::Red);
        window.draw(rect);
    }

    for (int i = 0; i < closedList.size(); i++) {
        Node *node = closedList.at(i);
        if (*node == *getStartPoint() || *node == *getEndPoint()) {
            continue;
        }
        rect.setPosition({(float)node->getX(), (float)node->getY()});
        rect.setFillColor(sf::Color::Yellow);
        window.draw(rect);
    }

    /* DRAW LINES */
    sf::RectangleShape horizontalLine;
    for (int i = 0; i < getLines(); i++) {
        horizontalLine.setSize({(float) getWidth(), 1.0});
        horizontalLine.setPosition(0, i*unitSize);
        window.draw(horizontalLine);
    }

    sf::RectangleShape verticalLine;
    for(int i = 0; i < getColumns(); i++) {
        verticalLine.setSize({1.0,(float) getHeight()});
        verticalLine.setPosition({(float)i*unitSize, 0.0});
        window.draw(verticalLine);
    }

    //last vertical line
    verticalLine.setPosition({(float) window.getSize().x - 1, 1.0});
    window.draw(verticalLine);

    //last horizontal line
    horizontalLine.setPosition({0, (float) window.getSize().y - 1});
    window.draw(horizontalLine);

    window.display();
    window.clear();
}

void Grid::setWall(int line, int column) {
    ValidElement<Node *> obj = at(line, column);
    /* only sets the node as wall it is valid  */
    Node *node = obj.getElement();

    if (obj.isValid() && !isEndNode(node) && !isStartNode(node)) {
        node->setIsWall(true);
    }
}

void Grid::setWalkable(int line, int column) {
    ValidElement<Node *> obj = at(line, column);

    if (obj.isValid()) {
        Node *node = obj.getElement();
        node->setIsWall(false);
    }
}

void Grid::print() const {
    Node *node;
    cout << "lines: " << getLines() << " Columns: " << getColumns() << endl;
    for (int i = 0; i < getLines(); i++) {
        for (int j = 0; j < getColumns(); j++) {
            node = at(i, j).getElement();
            cout << "X:" << node->getX() << ",Y:" << node->getY();
            cout << " | ";
        }
        cout << endl;
    }
}

/*
explanation
if unitSize = 60
[x=0][x=60][x=120]...
if x = 65
int columnPosition = x/unitSize = 65/60 = 1
*/
Node *Grid::getNodeFromWorldPoint(int x, int y) const {
    int column = x / unitSize;
    int line = y / unitSize;
    ValidElement<Node *> obj = at(line, column);
    return obj.isValid() ? obj.getElement() : nullptr;
}