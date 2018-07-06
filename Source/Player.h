#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedObject.h"

class QPropertyAnimation;
class QSoundEffect;

/**
	@brief A simple rectangle able to react to arrow keys when they are pressed
 */
class Player : public AnimatedObject
{
	Q_OBJECT
	Q_DISABLE_COPY(Player)

	/// Create a position property to animate the movement of this item
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)

  protected:
	/// To generate sounds when the player is activated
	QSoundEffect* collisionSound = nullptr;
	/// Animates the monster moving around the screen
	QPropertyAnimation* moveAnimation = nullptr;

  public:
	/// Constructor
	Player();
	/// Destructor
	~Player();
	/// Centers the player in the center bottom of the scene
	void setInitialPos();
	/// Called if this object has the focus and a key is pressed by user
	virtual void keyPressEvent(QKeyEvent* event) override;
	/// Called when this item is clicked or tapped by the user
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

  protected slots:
	/// Move the player around the scene
	void move();
	/// Detect and react to collisions with other elements
	void detectCollisions();
};

#endif // PLAYER_H
