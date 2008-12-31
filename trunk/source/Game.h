
class Game
{
public:
	Game(void);
	~Game(void);
	
	void refresh();

private:
	void init();
	void start();
	void loadLevel();
	void loose();
	void win();
	void displayCurrentScore();
	void displayBestScore();
	void displayWinLost();
	void end(int win);
};
