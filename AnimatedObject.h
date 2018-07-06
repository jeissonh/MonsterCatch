#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H

#include <QGraphicsSvgItem>

class QTimer;

/**
 * @brief An item that moves within the screen
 */
class AnimatedObject : public QGraphicsSvgItem
{
	Q_OBJECT
	Q_DISABLE_COPY(AnimatedObject)

  protected:
	/// To produce the move-up animation
	QTimer* timer;

  public:
	/// Constructor
	explicit AnimatedObject(QGraphicsItem* parent = nullptr);
	/// Destructor
	~AnimatedObject();
	/// Stops the timer, removes this object from the scene, and destroys it
	void destroy(bool removeFromScene = true, bool deleteObject = true);
};

#endif // ANIMATEDOBJECT_H
