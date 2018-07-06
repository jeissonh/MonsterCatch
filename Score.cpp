#include <QColor>
#include <QFont>

#include "Score.h"

Score::Score(const QString& legend, int initialScore, QColor color, QGraphicsItem* parent)
	: QGraphicsTextItem(parent)
	, legend(legend)
	, score(initialScore)
{
	setDefaultTextColor(color);
	setFont(QFont("", 24));
	updateScore();
}

Score::~Score()
{
}

void Score::increase(int amount)
{
	score += amount;
	updateScore();
}

void Score::decrease(int amount)
{
	score -= amount;
	updateScore();
}

void Score::updateScore()
{
	setPlainText( QString("%1: %2").arg(legend).arg(score) );
}
