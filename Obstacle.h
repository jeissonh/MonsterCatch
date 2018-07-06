#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QGraphicsSvgItem>

/**
 * @brief An obstacle that stops the player's progression to reach the goals of the game
 */
class Obstacle : public QGraphicsSvgItem
{
	Q_OBJECT
	Q_DISABLE_COPY(Obstacle)

  public:
	/// Constructor
	explicit Obstacle(QGraphicsItem* parent = nullptr);
	/// Set the initial position of this item
	void setInitialPos();
	/// Called when this item is clicked or tapped by the user
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif // OBSTACLE_H
