// 326627635 | adi.peisach@gmail.com

#ifndef TREE_ITERATORS_GUI_SCREEN_HPP
#define TREE_ITERATORS_GUI_SCREEN_HPP
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGuiApplication>
#include <QScreen>
#include <QTextEdit>
#include "Tree.cpp"
#include "Constants.hpp"
#include "Complex.cpp"

using std::string;

template <typename T>
QString toQString(T value) {
    string valueString = std::to_string(value);
    return QString::fromStdString(valueString);
}

template <>
inline QString toQString<double>(double value) {
    string valueString = std::to_string(value);
    while (valueString.back() == '0') valueString.pop_back();
    return QString::fromStdString(valueString);
}

template <>
inline QString toQString<string>(string value) {
    return QString::fromStdString(value);
}

template <>
inline QString toQString<Complex>(Complex value) {
    string str = value.toString();
    return QString::fromStdString(str);
}

template<typename T, unsigned int D>
class Screen {
    QApplication* app;
    QMainWindow* mainWindow;
    Tree<T, D>* tree;
    QGraphicsView* view;
    QGraphicsScene* scene;
    int screenWidth;
    int screenHeight;

    QPushButton* bfsButton;
    QPushButton* dfsButton;
    QPushButton* preOrderButton;
    QPushButton* inOrderButton;
    QPushButton* postOrderButton;
    QPushButton* heapButton;
    QTextEdit* textBox;

public:
    Screen(Tree<T,D>& tree) {
        // Initialize the GUI
        int argc = 1;
        char a = 'x';
        char* pa = &a;
        char* argv[1] = {pa};
        app = new QApplication(argc, argv);

        // Create the main window
        mainWindow = new QMainWindow();
        mainWindow->setWindowTitle("Tree Iterator Visualization | ★ Adi Peisach ★");
        mainWindow->showMaximized();
        scene = new QGraphicsScene(mainWindow);
        view = new QGraphicsView(scene, mainWindow);
        view->setRenderHint(QPainter::Antialiasing);
        mainWindow->setCentralWidget(view);
        QScreen *screen = QGuiApplication::primaryScreen();
        QRect screenGeometry = screen->geometry();

        screenWidth = screenGeometry.width()*0.75;
        screenHeight = screenGeometry.height();

        // Set the tree and display it
        this->tree = &tree;
        displayTree();

        // Create buttons and text box
        textBox = new QTextEdit(mainWindow);
        textBox->setGeometry(QRect(QPoint(600, 0), QSize(screenWidth-600, 30)));
        textBox->setText("");
        textBox->show();

        bfsButton = new QPushButton("BFS", mainWindow);
        bfsButton->move(0,0);
        bfsButton->show();
        QObject::connect(bfsButton, &QPushButton::clicked, [&]() {
            string text = "";
            for (auto node = tree.beginBFS(); node != tree.endBFS(); ++node) {
                text.append(toQString(**node).toStdString() + " ");
            }
            textBox->setText(QString::fromStdString(text));
        });

        dfsButton = new QPushButton("DFS", mainWindow);
        dfsButton->move(100,0);
        dfsButton->show();
        QObject::connect(dfsButton, &QPushButton::clicked, [&]() {
            string text = "";
            for (auto node = tree.beginDFS(); node != tree.endDFS(); ++node) {
                text.append(toQString(**node).toStdString() + " ");
            }
            textBox->setText(QString::fromStdString(text));
        });

        preOrderButton = new QPushButton("Pre-Order", mainWindow);
        preOrderButton->move(200,0);
        preOrderButton->show();
        QObject::connect(preOrderButton, &QPushButton::clicked, [&]() {
            string text = "";
            for (auto node = tree.beginPreOrder(); node != tree.endPreOrder(); ++node) {
                text.append(toQString(**node).toStdString() + " ");
            }
            textBox->setText(QString::fromStdString(text));
        });

        inOrderButton = new QPushButton("In-Order", mainWindow);
        inOrderButton->move(300,0);
        inOrderButton->show();
        QObject::connect(inOrderButton, &QPushButton::clicked, [&]() {
            string text = "";
            for (auto node = tree.beginInOrder(); node != tree.endInOrder(); ++node) {
                text.append(toQString(**node).toStdString() + " ");
            }
            textBox->setText(QString::fromStdString(text));
        });

        postOrderButton = new QPushButton("Post-Order", mainWindow);
        postOrderButton->move(400,0);
        postOrderButton->show();
        QObject::connect(postOrderButton, &QPushButton::clicked, [&]() {
            string text = "";
            for (auto node = tree.beginPostOrder(); node != tree.endPostOrder(); ++node) {
                text.append(toQString(**node).toStdString() + " ");
            }
            textBox->setText(QString::fromStdString(text));
        });

        heapButton = new QPushButton("Heap", mainWindow);
        heapButton->move(500,0);
        heapButton->show();
        QObject::connect(heapButton, &QPushButton::clicked, [&]() {
            if (D != 2) {
                textBox->setText("Heap is only supported for binary trees.");
                return;
            }
            string text = "";
            for (auto node = tree.beginHeap(); node != tree.endHeap(); ++node) {
                text.append(toQString(**node).toStdString() + " ");
            }
            textBox->setText(QString::fromStdString(text));
            displayTree();
        });

        app->exec();
    }

private:
    void displayTree();
    void displayNode(typename Node<T>::Node* node, int x, int y, int leftBorder, int rightBorder);
    QPointF drawNode(typename Node<T>::Node* node, int x, int y);

};

template<typename T, unsigned int D>
QPointF Screen<T, D>::drawNode(typename Node<T>::Node* node, int x, int y) {
    int nodeRadius = Constants::NODE_RADIUS;

    QGraphicsEllipseItem* ellipse = scene->addEllipse(x - nodeRadius, y - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
    QBrush brush(Qt::black);
    QPen pen(Qt::black);
    ellipse->setBrush(brush);
    ellipse->setPen(pen);

    // Display node value as text
    QString textString = toQString(node->getValue());
    QGraphicsTextItem* text = scene->addText(textString);
    text->setDefaultTextColor(Qt::white);
    text->setPos(x - nodeRadius / 2, y - nodeRadius / 2);

    return ellipse->rect().center();
}

/**
 * Display the tree in a GUI window
 */
template<typename T, unsigned int D>
Screen<T, D> display(Tree<T, D> &inputTree) {
    return Screen<T, D>(inputTree);
}

template<typename T, unsigned int D>
void Screen<T, D>::displayTree() {
    scene->clear();
    if (tree->getRoot() == nullptr) return;

    // Starting coordinates and spacing
    int rootX = screenWidth / 2;
    int rootY = 10 + Constants::NODE_RADIUS;

    displayNode(tree->getRoot(), rootX, rootY, 0, screenWidth);
}

template<typename T, unsigned int D>
void Screen<T, D>::displayNode(typename Node<T>::Node* node, int x, int y, int leftBorder, int rightBorder) {
    QPointF currCenter = drawNode(node, x, y);

    for (unsigned int i = 0; i < node->numChildren(); i++) {
        Node<T>* child = node->getChild(i);
        int childX = (rightBorder-leftBorder)/(D+1)*(i+1) + leftBorder;
        int childLeftX = (rightBorder-leftBorder)/(D+1)*(i) + leftBorder;
        int childRightX = (rightBorder-leftBorder)/(D+1)*(i+2) + leftBorder;

        QPointF childCenter = drawNode(child, childX, y + Constants::VERTICAL_SPACING);
        scene->addLine(QLineF(currCenter, childCenter));
        displayNode(child,childX,y+Constants::VERTICAL_SPACING,
                    childLeftX+Constants::NODE_RADIUS*2.1,childRightX-Constants::NODE_RADIUS*2.1);
    }

}


#endif //TREE_ITERATORS_GUI_SCREEN_HPP
