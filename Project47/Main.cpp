#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include <SFML/Audio.hpp>
#include <conio.h>
#include <vector>

using namespace sf;
using namespace std;
int ground = 150;
const int H = 17;
const int W = 150;
float offsetX;
float offsetY;
class Enemy;
int coins=0; 



//c-lucky block ,' ' - sky , k- block
String TileMap[H] = {
"000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000",
"0                                                                                                                                                    0",
"0                                                                                    w                                                               0",
"0                   w                                  w                   w                                                                         0",
"0                                      w                                         k   kk  kk   c k k  k   ckk       w                                 0",
"0                                                                                k  k  k k k  k   k k   k   k                                        0",
"0                      c                                                         k  с  k с  k k k kk    k   k             w                          0",
"0                                                                       r        k  k  k k   kk k kk    kkkkc           kckck                        0",
"0                                                                      rr     k  k  k  k k    k k k k   k   k                                Q       0",
"0                                                                     rrr      cc    kk  k    с k k  k k     k             r                         0",
"0               c    kckck                                           rrrr                                          r                         NNNNN   0",
"0                                      t0                           rrrrr                                                                    NNNNN   0",
"0G                                     00              t0          rrrrrr            G                                r                      NNNNN   0",
"0           d    g       d             00              00         rrrrrrr                                         r                          NNNNN   0",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
"PPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPPP",
};
class  Enemy
{
public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float curretFrame;
	bool life;
	void set(Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 16, 16);
		dx = 0.05;
		curretFrame = 0;
		life = true;
	}
	void update(float time)
	{
		rect.left += dx * time;
		Collision();
		curretFrame += time * 0.005;
		if (curretFrame > 2)
		{
			curretFrame -= 2;
		}
		sprite.setTextureRect(IntRect(18 * (int)curretFrame, 0, 16, 16));
		if (!life)
		{
			sprite.setTextureRect(IntRect(58 * (int)curretFrame, 0, 16, 16));
		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((i > 0 && j > 0) && (i < 17 && j < 150))
					if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0') )
					{
						if (dx > 0)
						{
							rect.left = j * 16 - rect.width; 
							dx *= -1;
						}
						else if (dx < 0)
						{
							rect.left = j * 16 + 16;  
							dx *= -1;
						}
						
					}
			}
	}
};
class  Enemy_Fly
{
public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	float curretFrame;
	Clock clockE;
	bool life;
	float timeE;
	bool right = true;
	void set(Texture& image, int x, int y)
	{
		sprite.setTexture(image);
		rect = FloatRect(x, y, 16, 16);
		dx = 0.05;
		curretFrame = 0;
		life = true;
		clockE.restart();
	}
	void update(float time)
	{
		timeE = clockE.getElapsedTime().asMicroseconds();
		/*clockE.restart();*/
		timeE = timeE / 800;
		rect.left += dx * time;

		Collision();
	
		curretFrame += time * 0.005;
		if (curretFrame > 3)
		{
			curretFrame -= 3;
		}
		if (life == true)
		{
			if (right == true)
				sprite.setTextureRect(IntRect(240 + (32 * (int)curretFrame), 0, 16, 24));
			else
				sprite.setTextureRect(IntRect(89 + (32 * (int)curretFrame), 0, 16, 24));
		}
		if (!life)
		{
			sprite.setTextureRect(IntRect(360 , 0, 16, 24));
		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision()
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ((i > 0 && j > 0) && (i < 17 && j < 150))
					
						if (timeE > 5000)
						{
							rect.left = j * 16 - rect.width;
							dx *= -1;
							timeE = 0;
							clockE.restart();
							if (right == true)
								right = false;
							else
								right = true;
						}
					
				if ((i > 0 && j > 0) && (i < 17 && j < 150))
				if ((TileMap[i][j] == 'P') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 'k') || (TileMap[i][j] == 'c'))
				{
						if (dx > 0)
						{
							rect.left = j * 16 - rect.width;
							dx *= -1;
							if (right == true)
								right = false;
							else
								right = true;
						}
						else if (dx < 0)
						{
							rect.left = j * 16 + 16;
							dx *= -1;
							if (right == true)
								right = false;
							else
								right = true;
						}

					}
			}
	}
};

class Player
{
public:
	float dx, dy;
	FloatRect rect;
	bool onGround;
	Sprite sprite;
	float currentFrame;
	bool stor;
	bool life;
	Texture m;
	Music ClaimCoin;
	Player(Texture& image )
	{
		sprite.setTexture(image);
		rect = FloatRect(210, 0, 16, 15);
		dx = dy = 0;
		currentFrame = 0;
		stor = true;
		life = true;
		m.loadFromFile("Mario_Tileset.png");
		ClaimCoin.openFromFile("videoplayback-_2_.ogg");
		ClaimCoin.setVolume(40);
	}
	void Update(float time, vector <Enemy>& q , Sound WinSound , RenderWindow& window , Music& music)
	{
		rect.left += dx * time;
		rect.left += dx * time;
		Collision(0  , q , WinSound , window, music);
		if (!onGround)
		{
			dy = dy + 0.0005 * time;
		}
		rect.top += dy * time;
		onGround = false;
		Collision(1 , q , WinSound, window, music);


		currentFrame += 0.005 * time;
		if (currentFrame > 3)
			currentFrame -= 3;
		if (dx > 0)
		{
			sprite.setTextureRect(IntRect(210 + (30 * (int)currentFrame), 0, 16, 15));
			stor = true;
		}
		if (dx < 0)
		{
			sprite.setTextureRect(IntRect(88 + (30 * (int)currentFrame), 0, 15, 15));
			stor = false;
		}
		if (dy < 0)
		{
			if (stor == true)
			sprite.setTextureRect(IntRect(358, 0, 20, 18));
			else
				sprite.setTextureRect(IntRect(28, 0, 20, 18));
		}
		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

		dx = 0;
	}
	void Collision(int num , vector <Enemy>& q , Sound WinSound , RenderWindow& window , Music& music)
	{

		for (int i = rect.top / 16; i < (rect.top + rect.height) / 16; i++)
			for (int j = rect.left / 16; j < (rect.left + rect.width) / 16; j++)
			{
				if ( (i > 0 ) && (i <17 && j <150) && (j>0))
				{
					if ((TileMap[i][j] == 'P') || (TileMap[i][j] == 'k') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'r') || (TileMap[i][j] == 't'))
					{
						if (dy > 0 && num == 1)
						{
							rect.top = i * 16 - rect.height;  dy = 0;   onGround = true;
						}
						if (dy < 0 && num == 1)
						{
							rect.top = i * 16 + 16;   dy = 0;
						}
						if (dx > 0 && num == 0)
						{
							rect.left = j * 16 - rect.width;
						}
						if (dx < 0 && num == 0)
						{
							rect.left = j * 16 + 16;
						}
					}
					if (TileMap[i][j] == 'N')
					{
						if (coins >= 8)
						{
							music.stop();
							WinSound.play();
							while (true)
							{
								Texture Winpng;
								Winpng.loadFromFile("Win.png");
								Sprite Winpn(Winpng);
								Winpn.setPosition(80, 40);
								window.clear(Color::Black);
								window.draw(Winpn);
								window.display();
								if (WinSound.getStatus() == 0)
								{
									window.close();
									break;
								}
							}
						}
						
						
					}
				if (TileMap[i][j] == 'c') {
					TileMap[i][j] = ' ';
					
					int tmp = rand () % 2 + 1;
					if (tmp == 1)
					{
						SpawnEnemy(j, 13, q);
					}
					if (tmp == 2)
					{
						ClaimCoin.play();
						coins++;
					}
				}
			}		
			}
	}
	void SpawnEnemy(int i, int j , vector <Enemy>& q)
	{
		Enemy* d = new Enemy;
		d->set(m, i * 16,  j* 16);
		q.push_back(*d);
		
	}

	void SetSpriteStart()
	{
		sprite.setTextureRect(IntRect(210, 0, 16, 15));
	}
	void SetAnimZerkal()
	{
		sprite.setTextureRect(IntRect(180, 0, 15, 15));
	}
};
void EnemyFlyDo(Player& p, Enemy_Fly& c, float& time, Music& music, Sound& End)
{
	c.update(time);
	if (p.rect.intersects(c.rect))
	{
		if (c.life == true)
		{
			if (p.dy > 0)
			{
				int t =
				c.dx = 0;
				p.dy = -0.2;
				c.life = false;
				coins++;
				// возрожедения
			}
			else
			{
				p.life = false; //game over
				music.stop();
				End.play();
			}
		}

	}
}
void EnemyDo(Player& p , Enemy& c , float& time ,Music& music , Sound& End)
{
	c.update(time);
	if (p.rect.intersects(c.rect))
	{
		if (c.life == true)
		{
			if (p.dy > 0)
			{
				int t =
					c.dx = 0;
				p.dy = -0.2;
				c.life = false;
				coins++;
				// возрожедения
			}
			else
			{
				p.life = false; //game over
				music.stop();
				End.play();
			}
		}

	}
	}
void menu(RenderWindow& window) {
	Texture menuTexture1, menuTexture2, AboutPic, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("New Game.png");
	menuTexture2.loadFromFile("About.png");
	aboutTexture.loadFromFile("Exit.png");
	AboutPic.loadFromFile("About_pic.png");
	menuBackground.loadFromFile("mario-bros.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), about(aboutTexture), menuBg(menuBackground) , Ab(AboutPic);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(148,128);
	menu2.setPosition(148, 163);
	about.setPosition(143, 192);
	menuBg.setPosition(0, 0);
	//////////////////////////////МЕНЮ///////////////////
	while (isMenu)
	{
		menuNum = 0;
		window.clear(Color(107, 140, 255));
		if (IntRect(148, 128, 124, 38).contains(Mouse::getPosition(window))) {  menuNum = 1; }
		if (IntRect(148, 163, 86, 35).contains(Mouse::getPosition(window))) {  menuNum = 2; }
		if (IntRect(143, 192, 78, 32).contains(Mouse::getPosition(window))) { menuNum = 3; }
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.draw(Ab); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }
		}
		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(about);
		window.display();
	}
}
class Game{
public:
void Start()
{
	RenderWindow window(VideoMode(400, 250), "Super Mario Bros");
	menu(window);
	Texture t;
	Texture m;
	Texture x;
	x.loadFromFile("fly.png");
	Font font;
	Text text;
	font.loadFromFile("Fixedsys.ttf");
	text.setFont(font);
	text.setCharacterSize(24);
	m.loadFromFile("Mario_Tileset.png");
	Sprite map(m);
	Texture E;
	E.loadFromFile("images.png");
	Sprite end(E);
	end.setPosition(80, 30);
	t.loadFromFile("smb_mario_sheet.png");
	Player p(t);
	RectangleShape rectangle;
	float u = 0;
	Enemy_Fly pan;
	pan.set(x, 15 * 16, 7 * 16);
	vector <Enemy> enemys;
	Enemy_Fly pan1;
	pan1.set(x, 72 * 16, 6 * 16);
	Enemy_Fly pan2;
	pan2.set(x, 118 * 16, 7 * 16);
	Enemy_Fly pan3;
	pan3.set(x, 131 * 16, 6 * 16);
	Enemy_Fly pan4;
	pan4.set(x, 67 * 16, 6 * 16);
	Enemy enemy1;
	enemy1.set(m, 48 * 16, 13 * 16);
	Enemy enemy2;
	enemy2.set(m, 23 * 16, 13 * 16);
	Enemy enemy3;
	enemy3.set(m, 53 * 16, 13 * 16);
	Enemy enemy4;
	enemy4.set(m, 79 * 16, 13 * 16);
	enemys.push_back(enemy1);
	enemys.push_back(enemy2);
	enemys.push_back(enemy3);
	enemys.push_back(enemy4);
	SoundBuffer buffer3;
	buffer3.loadFromFile("15-1-Down.ogg");
	Sound End(buffer3);
	SoundBuffer buffer4;
	buffer4.loadFromFile("16-Game-Over.ogg");
	Sound WinSound(buffer4);
	float CurrectFrame = 0;
	Clock clock;

	SoundBuffer buffer;
	buffer.loadFromFile("Jump.ogg");
	Sound Jump(buffer);

	Music music;
	music.openFromFile("Mario_Theme.ogg");
	music.play();
	music.setVolume(15);
	p.SetSpriteStart();
	music.setLoop(true);
	Jump.setVolume(20);
	text.setCharacterSize(13);
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (!_kbhit())
		{
			if (p.onGround)
			{
				if (p.stor)
				{
					p.SetSpriteStart();
				}
				else
					p.SetAnimZerkal();
			}

		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;

		}

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			p.dx = -0.1;

		}

		if (Keyboard::isKeyPressed(Keyboard::Up))

		{
			if (p.onGround)
			{
				p.dy = -0.28;
				p.onGround = false;

				Jump.play();
			}
		}

		p.Update(time, enemys, WinSound, window, music);

		EnemyFlyDo(p, pan, time, music, End);
		EnemyFlyDo(p, pan1, time, music, End);
		EnemyFlyDo(p, pan2, time, music, End);
		EnemyFlyDo(p, pan3, time, music, End);
		EnemyFlyDo(p, pan4, time, music, End);
		for (int i = 0; i < enemys.size(); i++)
			EnemyDo(p, enemys[i], time, music, End);
		if (p.life == true)
		{
			if (p.rect.left > 300)
				offsetX = p.rect.left - 600 / 2;

			offsetY = p.rect.top - 400 / 2;
			window.clear(Color(107, 140, 255));
			for (int i = 0; i < H; i++)
				for (int j = 0; j < W; j++)
				{
					if (TileMap[i][j] == 'P')  map.setTextureRect(IntRect(143 - 16 * 3, 112, 16, 16));

					if (TileMap[i][j] == 'k')  map.setTextureRect(IntRect(143, 112, 16, 16));

					if (TileMap[i][j] == 'c')  map.setTextureRect(IntRect(127, 112, 16, 15));

					if (TileMap[i][j] == 't')  map.setTextureRect(IntRect(0, 47, 32, 95 - 47));

					if (TileMap[i][j] == 'g')  map.setTextureRect(IntRect(0, 16 * 9 - 5, 3 * 16, 16 * 2 + 5));

					if (TileMap[i][j] == 'G')  map.setTextureRect(IntRect(145, 222, 222 - 145, 255 - 222));

					if (TileMap[i][j] == 'd')  map.setTextureRect(IntRect(0, 106, 74, 127 - 106));

					if (TileMap[i][j] == 'w')  map.setTextureRect(IntRect(99, 224, 140 - 99, 255 - 224));

					if (TileMap[i][j] == 'r')  map.setTextureRect(IntRect(143 - 32, 112, 16, 16));



					if (TileMap[i][j] == 'Q')  map.setTextureRect(IntRect(95, 7, 203 - 95, 111 - 7));

					if ((TileMap[i][j] == ' ') || (TileMap[i][j] == '0') || (TileMap[i][j] == 'N')) continue;


					map.setPosition(j * 16 - offsetX, i * 16 - offsetY);
					window.draw(map);
				}
			window.draw(p.sprite);
			string str = to_string(coins);
			str += ("/8 coins");
			text.setString(str);
			window.draw(text);
			if (pan.life == true)
				window.draw(pan.sprite);
			if (pan1.life == true)
				window.draw(pan1.sprite);
			if (pan2.life == true)
				window.draw(pan2.sprite);
			if (pan3.life == true)
				window.draw(pan3.sprite);
			if (pan4.life == true)
				window.draw(pan4.sprite);
			for (int i = 0; i < enemys.size(); i++)
			{
				if (enemys[i].life == true)
					window.draw(enemys[i].sprite);
			}

			window.display();
		}
		else
		{
			window.clear(Color::Black);
			window.draw(end);
			window.display();
		}
		if ((End.getStatus() == 0) && (music.getStatus() == 0) && (WinSound.getStatus() == 0))
			window.close();
	}
}
};
int main()
{
	srand(time(0));	

	Game Mario;
	Mario.Start();
  		
	return 0;
}