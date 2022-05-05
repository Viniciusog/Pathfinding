#include "Node.h"
using namespace std;
#include <iostream>
#include "Matrix.h"
#include "Grid.h"

int main() {

    Matrix<int> matrix(5,5);
    for (int i = 0; i < matrix.getLines(); i++) {
        for (int j = 0; j < matrix.getColumns(); j++) {
            matrix.add(i*5, j, i);
        }
    }

    matrix.print();

    /* int lines = 5;
    int columns = 5;

    Grid g(20, 200, 200);
    g.initGrid();
    g.print();

    //const sf::Time TimePerFrame = sf::Time::seconds(1.f/60.f);

    const unsigned int FPS = 1;

    sf::RenderWindow window(sf::VideoMode(200, 200), "Path finding!");
    window.setFramerateLimit(FPS);

    while (window.isOpen())
    {
        sf::Event event;
        
        while (window.pollEvent(event))
        {   
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    cout << "BOTÃO PRECIONADO" << endl;
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                        cout << "Window x" << window.getPosition().x << endl;
                        cout << "Window y" << window.getPosition().y << endl;
                        cout << "BOTÃO DIREITA" << endl;
                        cout << "X: " << sf::Mouse::getPosition().x<< endl;
                        cout << "Y: " << sf::Mouse::getPosition().y << endl;
                        cout << "X util: " << (sf::Mouse::getPosition(window).x) << endl;
                        cout << "Y util: " << (sf::Mouse::getPosition(window).y) << endl;

                        int column = sf::Mouse::getPosition(window).x / g.getUnitSize();
                        int line = sf::Mouse::getPosition(window).y / g.getUnitSize();
                        cout << "line: " << line << endl;
                        cout << "column: " << column << endl;

                        g.setWall(column, line);

                    } 
                    break;
            }           

        }

        g.drawTo(window);

        window.display();
        window.clear();
    }

    /*
    Grid g(60, 600);
    g.initGrid();
    g.print();
    */ 

    /*
    Matrix<int> matrix(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.add(i*j, i, j);
        }
    }

    matrix.print();
    cout << endl;

    lines = 8;
    columns = 8;

    matrix.realocate(lines, columns);
    for (int i = 0; i < lines; i++) {
        for (int j = 0; j < columns; j++) {
            matrix.add(i * j, i, j);
        }
    }

    matrix.print();
    */ 
}