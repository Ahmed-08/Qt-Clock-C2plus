#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QTime>
#include <QString>

class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = nullptr);
    ~Clock();
protected:
    void paintEvent(QPaintEvent *event);

    QTime   time;
    QString strTime;

public slots:
    void update();
};
#endif // CLOCK_H
