#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSoundEffect>
#include <QTime>
#include <QTimer>

#include "Game.h"
#include "Obstacle.h"
#include "Player.h"
#include "Score.h"

Game::Game(int &argc, char **argv, int flags)
	: QApplication(argc, argv, flags)
{
}

Game::~Game()
{
	delete this->scene;
	delete this->view;
}

int Game::run()
{
	// Init the random seed
	qsrand(QTime::currentTime().msec());

	// An invisible object that manages all the items
	this->scene = new QGraphicsScene();

	// A visible rectangle of the scene
	this->view = new QGraphicsView(this->scene);
  #if ! defined(Q_OS_ANDROID) && ! defined(Q_OS_IOS)
	this->view->resize(800, 600);
  #endif

	// Set a black color background or add an image as a background
	this->view->setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
//	scene->addItem( new QGraphicsPixmapItem(QPixmap(":/Background.png")) );

	// The scene has infinite size, but we want it has the same size than the view
	// This stops the weird behavior of the autoscroll feature of the view being smaller than the
	// scene, because the scene auto-increases when objects are moved
	this->scene->setSceneRect( this->view->rect() );

	// Disable scrollbars because they are not longer needed
	this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// A label to show the player score
	this->score = new Score(tr("Score"), 0, Qt::blue);
	this->score->setPos(5, 0);
	this->scene->addItem(this->score);

	// Load the graphic resources
	this->svgRenderer = new QSvgRenderer(QString("://assets.svg"), this);

	// Create the player control
	this->player = new Player();
	this->player->setSharedRenderer(svgRenderer);
	this->scene->addItem(this->player);
	this->player->setInitialPos();

	// Launch an enemy periodically
	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Game::launchObstacle);
	timer->start(1500);

	// Play background music
	playBackgroundMusic("FunkGameLoop32m.mp3");

	// Show the view and enter in application's event loop
	this->view->show();
	return exec();
}

void Game::playBackgroundMusic(const QString& audioFilename)
{
	// We add the sound to a playlist
	QMediaPlaylist* playlist = new QMediaPlaylist();
	playlist->addMedia(QUrl("qrc:/" + audioFilename));

	// We add the playlist to a media player object
	QMediaPlayer* mediaPlayer = new QMediaPlayer(this);
	mediaPlayer->setPlaylist(playlist);

	// Play the playlist in an infinite loop
	playlist->setCurrentIndex(1);
	playlist->setPlaybackMode(QMediaPlaylist::Loop);

	// Set 2/3 of the volume and start playing the background music
	mediaPlayer->setVolume(67);
	mediaPlayer->play();
}

void Game::launchObstacle()
{
	Obstacle* obstacle = new Obstacle();
	obstacle->setSharedRenderer(svgRenderer);
	scene->addItem(obstacle);
	obstacle->setInitialPos();
}
