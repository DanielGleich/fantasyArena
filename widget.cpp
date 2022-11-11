#include "widget.h"

Widget *Widget::widget = nullptr;

Widget::Widget()
{
    QLabel *title               = new QLabel( "<p align='center'><span style='font-size:60pt; "
                                              "font-family:Impact; color:white;'>"
                                              "Fantasy Arena</span></p>" );
    QVBoxLayout *layout         = new QVBoxLayout;
    QHBoxLayout *controllLayout = new QHBoxLayout;
    QPushButton *pbExit         = new QPushButton( "Be&enden" );
    QPushButton *pbLoadGame    = new QPushButton( "Spielen" );

    setStyleSheet("background-color:#060a61;");
    pbExit->setStyleSheet("background-color:#020426; color:white;");
    pbLoadGame->setStyleSheet("background-color:#020426; color:white;font-weight:bold;font-size:20pt;");

    setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter,this->size(),qApp->desktop()->availableGeometry(this)));

    controllLayout->addStretch();
    controllLayout->addWidget( pbExit );

    layout->addWidget( title );
    layout->addStretch();
    layout->addWidget( pbLoadGame );
    layout->addStretch();
    layout->addLayout( controllLayout );

    setLayout( layout );
    setWindowTitle( "FantasyArena" );

    connect( pbExit,      &QPushButton::clicked, this, &Widget::exitGame );
    connect( pbLoadGame, &QPushButton::clicked, this, &Widget::loadGame );
}

Widget::~Widget()
{}

void Widget::closeEvent( QCloseEvent * )// event )
{
    emit tryToExit();
}

Widget *Widget::get()
{
    if ( !widget )
        widget = new Widget;

    return widget;
}
