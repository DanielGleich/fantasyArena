#include "widget.h"

Widget *Widget::widget = nullptr;

Widget::Widget()
{
  QLabel *title               = new QLabel( "<p align='center'><span style='font-size:60pt; "
                                           "font-family:Verdana;'>"
                                           "Fantasy Arena</span></p>" );
  QVBoxLayout *layout         = new QVBoxLayout;
  QHBoxLayout *controllLayout = new QHBoxLayout;
  QPushButton *pbExit         = new QPushButton( "Be&enden" );
  QPushButton *pbLoadGame1    = new QPushButton( "Spiel 1" );

  controllLayout->addStretch();
  controllLayout->addWidget( pbExit );

  layout->addWidget( title );
  layout->addStretch();
  layout->addWidget( pbLoadGame1 );
  layout->addStretch();
  layout->addLayout( controllLayout );

  setLayout( layout );
  setWindowTitle( "FantasyArena" );

  connect( pbExit,      &QPushButton::clicked, this, &Widget::exitGame );
  connect( pbLoadGame1, &QPushButton::clicked, this, &Widget::loadGame );
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
