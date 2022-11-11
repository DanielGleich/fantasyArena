#include "controller.h"

Controller *Controller::controller = nullptr;

Controller::Controller( QObject *parent ) : QObject( parent )
{
    settings = new QSettings( "settings.txt", QSettings::IniFormat, this );
    game     = Game::get();
    widget   = Widget::get();
    arena    = Arena::get();
    loadWindowGeometry();
    widget->show();
    arena->hide();

    connect( widget, &Widget::exitGame,  this, &Controller::exit );
    connect( widget, &Widget::loadGame,  this, &Controller::loadGame );
    connect( arena,  &Arena::tryToClose, this, &Controller::closeArena );
}

Controller::~Controller()
{}

void Controller::saveWindowGeometry()
{
    settings->setValue( "geometryWidget", widget->geometry() );
    settings->setValue( "geometryArena",  arena->geometry() );
}

void Controller::loadWindowGeometry()
{
    widget->setGeometry( settings->value( "geometryWidget", QRect( 0, 0, 800, 600 ) ).toRect() );
    arena->setGeometry( settings->value( "geometryArena", QRect( 0, 0, 800, 600 ) ).toRect() );
    arena->setFixedSize( ARENA_WIDTH, ARENA_HEIGHT );
}

void Controller::exit()
{
    saveWindowGeometry();
    settings->sync();
    qApp->quit();
}

void Controller::loadGame()
{
    widget->hide();
    arena->show();
}

void Controller::closeArena()
{
    widget->show();
    arena->hide();
}

Controller *Controller::get()
{
    if ( !controller )
        controller = new Controller;

    return controller;
}
