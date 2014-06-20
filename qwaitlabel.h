#ifndef QWAITANIMATION_H
#define QWAITANIMATION_H

#include <QLabel>
#include <QPainter>
#include <QTimer>
#include <QPaintEvent>

#ifdef Q_OS_LINUX
#include <unistd.h>
#else
#include <Windows.h>
#endif

typedef int Position;

class QWaitLabel: public QLabel
{
    Q_OBJECT

public:
    enum Direction {
        FLY_IN = 0x0,
        FLY_WAIT = 0x1,
        FLY_OUT = 0x2
    };

    enum Indicator {
        CIRCLE = 0x0,
        RECT = 0x1
    };

    enum Speed {
        LOW = 0x10,
        MID = 0x5,
        HIGH = 0x1
    };

    QWaitLabel(QWidget *parent = 0);
    ~QWaitLabel();
    void setIndicatorType(Indicator indicator);
    void setSpeed(Speed speed);
    void setFillColor(QColor color);
    void setOutlineColor(QColor color);

protected:
    void resizeEvent(QResizeEvent *resizeEvent);

private slots:
    void updatePixmap();

private:
    Direction dir;
    int indicatorCount;
    int indicatorSize;
    int scaleFactor;

    Position endPos;
    Position startPos;
    Position waitPos;

    QTimer timer;
    QVector<Position> indicators;
    int currentIndicator;
    Indicator indicator;
    QColor fillColor;
    QColor outlineColor;
};

#endif // QWAITANIMATION_H
