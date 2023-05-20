#include <QtWidgets>
const int LENGTH_ROAD = 600;
const int COUNT_CARS = 3;
class Road {
public:
    Road(double newLength, int newWidth);
    double Length;
    int Width;
};

Road::Road(double newLength, int newWidth) {

    Length = newLength;
    Width = newWidth;
}

class Car {
public:
    Car(int newP, double newV, Road* ptrRoad);
    Road* _road;
    double X;
    int P;
    double V;
    void move();

};

Car::Car(int newP, double newV, Road* ptrRoad) {
    _road = ptrRoad;
    X = 0;
    P = newP;
    V = newV;

}
void Car::move() {
    X += V;
    if (X > _road->Length) {
        X = 0;
    }
}



class MainWindow : public QMainWindow {
public:
    MainWindow(Car* ptrCars[]);
    void updateCars();
    void openButtonClick();
    void openButtonClick1();
    void openButtonClick2();
private:
    void paintEvent(QPaintEvent*);

    Car** _cars;
    int timerInterval;
    QTimer* timer;
    QPushButton* openButton;
    QPushButton* openButton1;
    QPushButton* openButton2;
    QString filePath;
    QString filePath1;
    QString filePath2;
};

MainWindow::MainWindow(Car* ptrCars[]) {
    _cars = ptrCars;
    setFixedSize(1100, LENGTH_ROAD);
    setWindowTitle("Racing Labels v9.4");
    timer = new QTimer(this);
    timer->setInterval(100);
    timer->start();

    openButton = new QPushButton("Open", this);
    openButton->setGeometry(10, 10, 50, 30);

    openButton1 = new QPushButton("Open", this);
    openButton1->setGeometry(100, 10, 50, 30);

    openButton2 = new QPushButton("Open", this);
    openButton2->setGeometry(190, 10, 50, 30);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateCars);

    connect(openButton, &QPushButton::clicked, this, &MainWindow::openButtonClick);
    connect(openButton1, &QPushButton::clicked, this, &MainWindow::openButtonClick1);
    connect(openButton2, &QPushButton::clicked, this, &MainWindow::openButtonClick2);
}

void MainWindow::openButtonClick() {
    filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Images Files (*.png *.jpg *.gif)");
    update();
}

void MainWindow::openButtonClick1() {
    filePath1 = QFileDialog::getOpenFileName(this, "Open Image", "", "Images Files (*.png *.jpg *.gif)");
    update();
}

void MainWindow::openButtonClick2() {
    filePath2 = QFileDialog::getOpenFileName(this, "Open Image", "", "Images Files (*.png *.jpg *.gif)");
    update();
}

void MainWindow::updateCars() {
    for (int i = 0; i < COUNT_CARS;i++) {
        _cars[i]->move();
    }
    update();
}
void MainWindow::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    QPen redPen4(Qt::red, 4, Qt::SolidLine);
    QBrush greenBrush(Qt::green, Qt::SolidPattern);
    QBrush redBrush(Qt::red, Qt::SolidPattern);
    QBrush yellowBrush(Qt::yellow, Qt::SolidPattern);
    painter.setPen(redPen4);
    painter.setBrush(greenBrush);


    QPixmap pixmap;
    //pixmap.load("1.png");
    pixmap.load(filePath);
    painter.drawPixmap(_cars[0]->X, 100, pixmap);


    //pixmap.load("2.png");
    pixmap.load(filePath1);
    painter.drawPixmap(_cars[1]->X, 200, pixmap);
    //pixmap.load("3.png");
    pixmap.load(filePath2);
    painter.drawPixmap(_cars[2]->X, 300, pixmap);
}
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Road road(LENGTH_ROAD, 3);

    Car* cars[COUNT_CARS];
    for (int i = 0; i < COUNT_CARS; i++) {
        cars[i] = new Car(i, 2 * (i + 1), &road);
    }

    MainWindow mainWin(cars);
    mainWin.show();
    return app.exec();

}
