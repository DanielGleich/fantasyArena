#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>
#include <QtCore>

const bool DEBUG                            = true;

const int     PLAYERID                      = 1;
const QString file                          = "../../../fantasyArena.db";
const QString fileTest                      = "fantasyArena.db";

const int HANDSIZE                          = 5;
const int ENERGY                            = 2;

const int ARENAWIDTH                        = 1000;
const int ARENAHEIGHT                       = 700;

const int PADDING                           = 20;
const int SPACING                           = 7;

const int CARD_SPACE                        = 10; // Spalte zwischen 2 Karten
const int CARD_HEIGHT                       = 184;
const int CARD_WIDTH                        = 184;
const int RANGE_ICON_SIZE                   = 20;

const int MONSTER_SPACE                     = 14;
const int MONSTER_HEIGHT                    = 184;
const int MONSTER_WIDTH                     = 240;
const int MONSTER_SIDE_PADDING              = ( ARENAWIDTH-3*MONSTER_WIDTH-2*MONSTER_SPACE )/2;// 126;
const int MONSTER_LP_HEIGHT                 = MONSTER_HEIGHT-50;

const QColor MONSTER_LP_COLOR               = Qt::red;
const QColor CARD_BACKGROUND_COLOR          = QColor( 165, 205, 205 );
const QColor SELECTED_CARD_BACKGROUND_COLOR = QColor( 179, 222, 222 );
const QColor MONSTER_COLOR                  = QColor( 155, 202, 215 );
const QColor SELECTED_MONSTER_COLOR         = QColor( 169, 217, 230 );

const QRectF MONSTER_SKILLNAME              = QRectF( 0, 50, 240, 20 );
const QRectF END_TURN_BUTTON                = QRectF( 800, 600, 120, 50 );
const QRectF PLAYER                         = QRectF( 150, 500, 800, 160 );
const QRect  PLAYER_LP                      = QRect( 150, 500, 300, 60 );
const QRect  PLAYER_ENERGY                  = QRect( 150, 600, 300, 60 );
const QRect  PLAYER_DEFENSE                 = QRect( 650, 500, 300, 60 );
const int    PLAYER_LP_FONT                 = 45;
const int    PLAYER_ENERGY_FONT             = 45;
const int    PLAYER_DEFENSE_FONT            = 45;
const int    END_TURN_BUTTON_FONT           = 16;

const int   ENERGY_BULLET_DIAMETER          = 10;
const int   ENERGY_BULLET_SPACING           = 5;
const QRect CARD_ENERGY( CARD_WIDTH-ENERGY_BULLET_DIAMETER-SPACING,
                        SPACING,
                        5*ENERGY_BULLET_DIAMETER-4*ENERGY_BULLET_SPACING,
                        ENERGY_BULLET_DIAMETER+5*ENERGY_BULLET_DIAMETER+4*ENERGY_BULLET_SPACING );

inline int  min( int a, int b )               { return a<b ? a : b; }
inline int  max( int a, int b )               { return a>b ? a : b; }
inline void sort( int &a, int &b )            { int temp = a; a = min( temp, b ); b = max( temp, b ); }
inline int  random( int min, int max )        { sort( min, max ); return qrand()%( max-min+1 )+min; }
inline int  lpLoss( int attack, int defense ) { return attack>defense ? attack-defense : 0; }

#endif // CONFIG_H

/*!
 * \var const int PADDING
 * \brief Allgemeiner größerer Abstand
 *
 * Wird benutzt zum Beispiel für den Platz zwischen Karten und dem Außenrand .
 *
 * \var const int SPACING
 * \brief Allgemeiner kleinerer Abstand
 *
 * Wird für Abstände beim Zeichnen in der Klasse Arena verwendet.
 *
 *
 */
