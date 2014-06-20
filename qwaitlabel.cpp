#include "qwaitlabel.h"

QWaitLabel::QWaitLabel(QWidget *parent) : QLabel(parent)
{
    setMinimumHeight(25);

    outlineColor = Qt::black;
    fillColor = Qt::transparent;

    dir = FLY_IN;

    indicatorSize = 15;
    currentIndicator = 0;
    indicator = CIRCLE;

    // 5 indicators, 3 steps
    // =  15 positions
    scaleFactor = width()/14;
    // hide from screen
    startPos = -1 * scaleFactor;
    // go out of screen
    endPos = 16 * scaleFactor;
    // wait at middle
    waitPos = 9 * scaleFactor;

    // initialize with default start position
    for(int c=0; c<5; c++)
        indicators.push_back(startPos);

    connect(&timer, SIGNAL(timeout()), this, SLOT(updatePixmap()));
    updatePixmap();
    timer.start(MID);
}

QWaitLabel::~QWaitLabel(){}

void QWaitLabel::setIndicatorType(QWaitLabel::Indicator indicator)
{
    this->indicator = indicator;
}

void QWaitLabel::setSpeed(QWaitLabel::Speed speed)
{
    timer.setInterval(speed);
}

void QWaitLabel::setFillColor(QColor color)
{
    fillColor = color;
}

void QWaitLabel::setOutlineColor(QColor color)
{
    outlineColor = color;
}

void QWaitLabel::resizeEvent(QResizeEvent *resizeEvent)
{
    QLabel::resizeEvent(resizeEvent);

    // get new scale factor by segmenting
    int newScaleFactor = width()/14;

    // reset indicator positions
    for(unsigned int d=0; d<5; d++)
    {
        indicators[d] /= scaleFactor;
        indicators[d] *= newScaleFactor;
    }

    // recalculate target positions
    scaleFactor = newScaleFactor;
    startPos = -1 * scaleFactor;
    endPos = 16 * scaleFactor;
    waitPos = 9 * scaleFactor;
}

void QWaitLabel::updatePixmap()
{
    QPixmap pixmap(size());
    pixmap.fill(Qt::transparent);

    QPainter p(&pixmap);
    p.setPen(outlineColor);
    p.setBrush(fillColor);
    p.setRenderHints(QPainter::Antialiasing
                     |QPainter::SmoothPixmapTransform
                     |QPainter::HighQualityAntialiasing
                     );

    if(dir == FLY_IN)
    {
        // move indicator to the right
        indicators[currentIndicator]++;

        // if it reaches the center
        if(indicators[currentIndicator] == waitPos)
        {
            // move to next indicator
            currentIndicator++;
            // indent center position to the left
            waitPos -= scaleFactor;
        }

        // when all indicators are moved to the center
        if(currentIndicator == 5)
        {
            // wait
            dir = FLY_WAIT;
            // and get back to the first indicator
            currentIndicator = 0;
        }
    }
    else if(dir == FLY_WAIT)
    {
        // damn Qt has no easy sleep function
#ifdef Q_OS_LINUX
        usleep(10000);
#else
        Sleep(1);
#endif
        dir = FLY_OUT;
    }
    else if(dir == FLY_OUT)
    {
        // move the indicators
        indicators[currentIndicator]++;

        // when it reaches the screen end
        if(indicators[currentIndicator] == endPos)
        {
            // get back to next indicator
            currentIndicator++;
        }

        // when all indicators are moved to the center
        if(currentIndicator == 5)
        {
            // reset movement direction
            dir = FLY_IN;
            currentIndicator = 0;
            waitPos = 9 * scaleFactor;

            // reinitialize indicator data
            for(unsigned int d=0; d<5; d++)
                indicators[d] = -1 * scaleFactor;
        }
    }

    // get some brush and colors
    for(unsigned int d=0; d<5; d++)
        if(indicator == CIRCLE)
            p.drawEllipse(indicators[d], height()/2, indicatorSize, indicatorSize);
        else if(indicator == RECT)
            p.drawRect(indicators[d], height()/2, indicatorSize, indicatorSize);

    // whew! set the image
    setPixmap(pixmap);
}
