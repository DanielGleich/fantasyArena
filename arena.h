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
  QRectF                          rect;
  Card                            *card          = nullptr;
  static QList< CardPosition*>    allCards;
  static CardPosition*            selectedCard;
  QPointF                         *originPosition;

public:
  CardPosition( QRectF value );
  ~CardPosition();
  QRectF                getRect() const                   {return rect;}
  void                  setRect( QRectF value )           {rect = value;}
  Card                  *getCard() const                  {return card;}
  void                  setCard( Card *value )            {card = value;}
  void                  setSelected()                     {selectedCard = this;}
  static void           setSelected(CardPosition* card)   {selectedCard = card;}
  static CardPosition*  getSelectedCard()                 {return selectedCard;}
  void                  resetPosition();
};

class MonsterPosition
{
  private:
    QRectF                            rect;
    Monster                           *monster       = nullptr;
    static QList<MonsterPosition*>    allMonsters;
    static MonsterPosition*           selectedMonster;

public:
  MonsterPosition( QRectF value );
  ~MonsterPosition();
  QRectF                  getRect() const                {return rect;}
  void                    setRect( const QRectF& value ) {rect = value;}
  Monster                 *getMonster() const            {return monster;}
  void                    setMonster( Monster *value )   {monster = value;}
  void                    setSelected()                  {selectedMonster = this;}
  static void             setSelected(MonsterPosition* m){selectedMonster = m;}
  static MonsterPosition* getSelectedMonster()           {return selectedMonster;}
};

class Arena : public QWidget
{
    Q_OBJECT

  private:
    static Arena               *arena;
  QList< CardPosition * >    handCardRects;
  QList< MonsterPosition * > activeMonsterRects;
  QSize                      *cardSize;
  QPoint                     *clickPosition;
  QPushButton                *pbNextTurn;
  bool                       dragActive = false;
  Arena( QWidget *parent = nullptr );
  void paintHandCards(QPainter &p);
  void paintMonsterCards(QPainter &p);
  void paintBackground(QPainter &p);
  void paintPlayerInfo(QPainter &p);
  ~Arena();

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
  void resizeEvent( QResizeEvent *event );
  void closeEvent( QCloseEvent *event );

signals:
  void tryToClose();
public slots:
  void nextTurn();

};

#endif // ARENA_H


/*!
 * \class Arena
 * \brief Singleton-Klasse: Anzeige des Spielfeldes, in welchem die Kämpfe stattfinden.
 *
 * \var Arena* Arena::arena
 * \brief Ein Zeiger auf das Singleton-Objekt.
 *
 * \var QList< QRectF * > Arena::handCardRects
 * \brief Die Koordinaten der gezeichneten Rechtecke für die Handkarten.
 *
 * Diese werden benötigt, um Mausklicks abzufangen und einer Karte zuordnen zu können.
 *
 * \fn void Arena::drawPlayerhandCards( QPainter& painter )
 * \brief Die Handkarten des Spielers werden gezeichnet.
 *
 * Hier werden auch die Koordinaten der Rechtecke der Karten neu gesetzt (siehe Arena::handCardRects).
 *
 * \fn void Arena::drawRangeSymbolOfHandCard( QPainter& painter, Card *handCard )
 * \brief Das Symbol für die Reichweite der übergebenen Karte wird gezeichnet.
 *
 * Als Symbole stehen zur Verfügung:
 * - Bogen: Fernkampf
 * - Schwert: Nahkampf
 * - Stern: Eine fertigkeit auf den Spieleravatar selbst
 *
 * \fn void Arena::drawNameOfHandCard( QPainter &painter, Card *handCard )
 * \brief Der Name der übergebenen Handkarte wird geschrieben
 *
 * \param Card* handCard Ein Zeiger auf die zu beschreibende Karte
 *
 * \fn void Arena::drawSkillOfHandCard( QPainter &painter, Card *handCard )
 * \brief Der Skillname der übergebenen Handkarte wird geschrieben
 *
 * Sollte die Handkarte kein Skill haben (noSkill), wird nichts gemacht.
 *
 * \param Card* handCard Ein Zeiger auf die zu beschreibende Karte
 */
