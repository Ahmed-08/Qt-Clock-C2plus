#include "clock.h"

Clock::Clock(QWidget *parent)
    : QWidget(parent)
{
    // устанавливаем таймер на одну секунду
    QTimer *timer = new QTimer(this);

    // каждую секунду будет вызываться слот update
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    // устанавливаем заголовок виджета
    this->setWindowTitle(tr("Clock"));
    this->resize(500, 500);
}

// QTimer, созданный динамически в конструкторе,
// в деструкторе удалять не обязательно,
// так как он наследуется от этого виджета
// и удалится при удалении виджета
Clock::~Clock()
{}

// при вызове update происходит перерисовка
void Clock::update()
{
    this->time      = QTime::currentTime();
    this->strTime   = time.toString("hh:mm:ss");

    // устанавливаем время в заголовке виджета
    this->setWindowTitle(strTime);
    QWidget::update();
}

// событие рисования
void Clock::paintEvent(QPaintEvent*)
{
    // класс для рисования
    QPainter painter;

    painter.begin(this);

        // сглаживание
        painter.setRenderHint(QPainter::Antialiasing);

        // переносим центр системы координат на середину
        painter.translate(this->width() / 2, this->height() / 2);

        // размещение часов
        int R = 0.7 * qMin(this->width() / 2, height() / 2);
        for(int i = 0; i < 60; ++i)
        {
            if(i % 5 == 0){
                painter.setPen(Qt::red);
                painter.drawLine(0, R, 0, R - 10);
            }else{
                painter.setPen(Qt::black);
                painter.drawLine(0, R, 0, R - 4);
            }
            painter.rotate(6.0);
        }

        // убираем перо
        // рисование будет кистью - QBrush
        painter.setPen(Qt::NoPen);

        // отрисовка часавой стрелки
        painter.save();
            QPolygon pol;
            pol << QPoint(-0.05 * R, 0) << QPoint(0.05 * R, 0) << QPoint(-0, 0.4 * R);
            painter.setBrush(QColor(45, 138, 64));
            painter.rotate(30 * (time.hour() + time.minute() / 60) + 180);
            painter.drawPolygon(pol);
        painter.restore();

        // отрисовка минутной стрелки
        painter.save();
            QPolygon pol2;
            pol2 << QPoint(-0.04 * R, 0) << QPoint(0.04 * R, 0) << QPoint(-0, 0.7 * R);
            painter.setBrush(QColor(0, 127, 127, 191));
            painter.rotate(6.0 * (time.minute() + time.second() / 60) + 180);
            painter.drawPolygon(pol2);
        painter.restore();

        // отрисовка секундной стрелки
        painter.save();
            QPolygon pol3;
            pol3 << QPoint(-0.03 * R, 0) << QPoint(0.03 * R, 0) << QPoint(-0, 0.9 * R);
            painter.setBrush(QColor(202, 0, 0, 191));
            painter.rotate(6.0 * time.second() + 180);
            painter.drawPolygon(pol3);
        painter.restore();

    painter.end();
}



