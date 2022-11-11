#ifndef ARENA_H
#define ARENA_H

#include <QObject>
#include <QtWidgets>
#include "card.h"
#include "config.h"
#include "game.h"

class CardPosition
{
private:
    static QList<CardPosition*>     allCards;
    static CardPosition*            selectedCard;
    Card                            *card;
    QRectF                          rect;
    QPointF                         *originPosition;

public:
    CardPosition(QRectF value , Card *card);
    ~CardPosition();
    QRectF                getRect() const                   {return rect;}
    void                  setRect( QRectF value )           {rect = value;}
    Card                  *getCard() const                  {return card;}
    void                  setCard( Card *value )            {card = value;}
    void                  setSelected()                     {selectedCard = this;}
    static void           setSelected(CardPosition* card)   {selectedCard = card;}
    static CardPosition*  getSelectedCard()                 {return selectedCard;}
    void                  resetPosition();
    void                  remove();
};

class MonsterPosition
{
private:
    QRectF                            rect;
    Monster                           *monster       = nullptr;
    static QList<MonsterPosition*>    allMonsters;
    static MonsterPosition*           selectedMonster;

public:
    MonsterPosition( QRectF value, Monster* monster );
    ~MonsterPosition();
    QRectF                  getRect() const                {return rect;}
    void                    setRect( const QRectF& value ) {rect = value;}
    Monster                 *getMonster() const            {return monster;}
    void                    setMonster( Monster *value )   {monster = value;}
    void                    setSelected()                  {selectedMonster = this;}
    static void             setSelected(MonsterPosition* m){selectedMonster = m;}
    static MonsterPosition* getSelectedMonster()           {return selectedMonster;}
    void                    remove();
};

class Arena : public QWidget
{
    Q_OBJECT

private:
    static Arena               *arena;
    QList< CardPosition * >    *handCardRects;
    QList< MonsterPosition * > *activeMonsterRects;
    QSize                      *cardSize;
    QPoint                     *clickPosition;
    QPushButton                *pbNextTurn;
    bool                       dragActive = false;
    bool                       playerSelected = false;

    Arena( QWidget *parent = nullptr );
    ~Arena();
    void paintBackground(QPainter &p);
    void paintMonsterCards(QPainter &p);
    void paintHandCards(QPainter &p);
    void paintPlayerInfo(QPainter &p);

    void initPlayerCardsPositions();
    void initMonsterPositions();

public:
    static Arena *get();
    void refresh();
    void syncHandCardRects();
    void syncMonsterRects();

protected:
    void paintEvent( QPaintEvent * );
    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    void mouseMoveEvent( QMouseEvent *event );
    void closeEvent( QCloseEvent *event );

public slots:
    void nextTurn();

signals:
    void tryToClose();

};

#endif // ARENA_H
