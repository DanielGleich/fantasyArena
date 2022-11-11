#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QWidget>
#include "config.h"

/*********************************************\
|*                                           *|
|*  Widget                                   *|
|*                                           *|
\*********************************************/
class Widget : public QWidget
{
    Q_OBJECT
private:
    static Widget *widget;
    Widget();
    ~Widget();

protected:
    void closeEvent( QCloseEvent *event );

public:
    static Widget *get();

signals:
    void exitGame();
    void loadGame();
    void tryToExit();
};

#endif // WIDGET_H
