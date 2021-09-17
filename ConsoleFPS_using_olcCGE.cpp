#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>
#include "olcConsoleGameEngine.h"
#define BOX '#'

using namespace std;

const int N = 32;
char lab[N][N];

/* cover map edges */
void init()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			lab[i][j] = 0;
			if (i == 0 || i == N - 1) lab[i][j] = BOX;
		}
		lab[i][0] = BOX;
		lab[i][N - 1] = BOX;
	}
}

int rndEven(int s, int k)
{
	vector<int> v;
	for (int i = s; i < k; i++)
	{
		if (i % 2 == 0) v.push_back(i);
	}
	random_shuffle(v.begin(), v.end());
	return v[0];
}

int rndOdd(int s, int k)
{
	vector<int> v;
	for (int i = s; i < k; i++)
	{
		if (i % 2 == 1) v.push_back(i);
	}
	random_shuffle(v.begin(), v.end());
	return v[0];
}

wstring divide(int xp, int yp, int xk, int yk)
{
	wstring maze = L"";
	int sciana;
	int przejscie;
	if (xk - xp >= yk - yp)
	{
		if (xk - xp > 3)
		{
			sciana = rndEven(xp + 1, xk - 1);

			for (int i = yp; i < yk; i++)
				lab[i][sciana] = BOX;
			przejscie = rndOdd(yp, yk);
			lab[przejscie][sciana] = ' ';

			divide(xp, yp, sciana, yk);
			divide(sciana, yp, xk, yk);
		}
	}
	else if (xk - xp < yk - yp)
	{
		if (yk - yp > 3)
		{
			sciana = rndEven(yp + 1, yk - 1);
			for (int i = xp; i < xk; i++)
				lab[sciana][i] = BOX;
			przejscie = rndOdd(xp, xk);
			lab[sciana][przejscie] = ' ';

			divide(xp, yp, xk, sciana);
			divide(xp, sciana, xk, yk);
		}

	}
	for (int i = 0; i < N; i++)
	{
		for (int y = 0; y < N; y++)
		{
			if (lab[i][y] != BOX) lab[i][y] = '.';
		}
	}
	for (int i = 0; i <= N; i++)
	{
		for (int y = 0; y <= N; y++)
		{
			maze += lab[i][y];
		}
	}

	return maze;
}

wstring randMaze()
{
	int hash = 0;
	wstring maze = L"";
	for (int i = 0; i < 33; i++)
	{
		for (int y = 0; y < 33; y++)
		{
			hash = rand() % 2;
			if (hash == 0)
			{
				maze += L".";
			}
			else maze += L"#";
		}
	}



	return maze;
}

class UltimateConsoleFPS : public olcConsoleGameEngine {
private:
	wstring map;

	int nMapWidth = 32;
	int nMapHeight = 32;

	float fPlayerX = 14.7f; 
	float fPlayerY = 5.09f;
	float fPlayerA = 0.0f;
	float fFOV = M_PI / 4.0f;
	float fDepth = 16.0f;
	float fSpeed = 5.0f;

public:
	UltimateConsoleFPS()
	{
		m_sAppName = L"Improved Console FPS";
	}
	virtual bool OnUserCreate()
	{
		srand(time(NULL));

		/*init();
		map = divide(1, 1, N - 1, N - 1);*/

		//map = randMaze();

		map += L"#########.......#########.......";
		map += L"#...............#...............";
		map += L"#.......#########.......########";
		map += L"#..............##..............#";
		map += L"#......##......##......##......#";
		map += L"#......##..............##......#";
		map += L"#..............##..............#";
		map += L"###............####............#";
		map += L"##.............###.............#";
		map += L"#............####............###";
		map += L"#..............................#";
		map += L"#..............##..............#";
		map += L"#..............##..............#";
		map += L"#...........#####...........####";
		map += L"#..............................#";
		map += L"###..####....########....#######";
		map += L"####.####.......######..........";
		map += L"#...............#...............";
		map += L"#.......#########.......##..####";
		map += L"#..............##..............#";
		map += L"#......##......##.......#......#";
		map += L"#......##......##......##......#";
		map += L"#..............##..............#";
		map += L"###............####............#";
		map += L"##.............###.............#";
		map += L"#............####............###";
		map += L"#..............................#";
		map += L"#..............................#";
		map += L"#..............##..............#";
		map += L"#...........##..............####";
		map += L"#..............##..............#";
		map += L"################################";

		return true;

	}
	virtual bool OnUserUpdate(float fElapsedTime)
	{
		/* Controls */
		// Handle Player's Rotation and Movement
		if (m_keys[L'A'].bHeld)
			fPlayerA -= (0.5f) * fSpeed / M_PI * fElapsedTime;

		// 
		if (m_keys[L'D'].bHeld)
			fPlayerA += (0.5f) * fSpeed / M_PI * fElapsedTime;

		// Forward + walls collision
		if (m_keys[L'W'].bHeld)
		{
			fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
			fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
				fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
			}
		}

		// Backwards + collision
		if (m_keys[L'S'].bHeld)
		{
			fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
			fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;;
				fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;;
			}
		}
		// Handle Strafe Right movement & collision
		if (m_keys[L'E'].bHeld)
		{
			fPlayerX += cosf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY -= sinf(fPlayerA) * fSpeed * fElapsedTime;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= cosf(fPlayerA) * fSpeed * fElapsedTime;
				fPlayerY += sinf(fPlayerA) * fSpeed * fElapsedTime;
			}
		}

		// Handle Strafe Left movement & collision
		if (m_keys[L'Q'].bHeld)
		{
			fPlayerX -= cosf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY += sinf(fPlayerA) * fSpeed * fElapsedTime;
			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX += cosf(fPlayerA) * fSpeed * fElapsedTime;
				fPlayerY -= sinf(fPlayerA) * fSpeed * fElapsedTime;
			}
		}

		for (int x = 0; x < ScreenWidth(); x++)
		{
			// For each column, calculate the projected ray angle into world space
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)ScreenWidth()) * fFOV;

			// Find distance to wall
			float fStepSize = 0.1f;		  // Increment size for ray casting, decrease to increase										
			float fDistanceToWall = 0.0f; //                                      resolution

			bool bHitWall = false;		// Set when ray hits wall block
			bool bBoundary = false;		// Set when ray hits boundary between two wall blocks

			float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
			float fEyeY = cosf(fRayAngle);

			// Incrementally cast ray from player, along ray angle, testing for 
			// intersection with a block
			while (!bHitWall && fDistanceToWall < fDepth)
			{
				fDistanceToWall += fStepSize;
				int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
				int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

				// Test if ray is out of bounds
				if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight)
				{
					bHitWall = true;			// Just set distance to maximum depth
					fDistanceToWall = fDepth;
				}
				else
				{
					// Ray is inbounds so test to see if the ray cell is a wall block
					if (map.c_str()[nTestX * nMapWidth + nTestY] == '#')
					{
						// Ray has hit wall
						bHitWall = true;

						// To highlight tile boundaries, cast a ray from each corner
						// of the tile, to the player. The more coincident this ray
						// is to the rendering ray, the closer we are to a tile 
						// boundary, which we'll shade to add detail to the walls
						vector<pair<float, float>> p;

						// Test each corner of hit tile, storing the distance from
						// the player, and the calculated dot product of the two rays
						for (int tx = 0; tx < 2; tx++)
							for (int ty = 0; ty < 2; ty++)
							{
								// Angle of corner to eye
								float vy = (float)nTestY + ty - fPlayerY;
								float vx = (float)nTestX + tx - fPlayerX;
								float d = sqrt(vx * vx + vy * vy);
								float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
								p.push_back(make_pair(d, dot));
							}

						// Sort Pairs from closest to farthest
						sort(p.begin(), p.end(), [](const pair<float, float>& left, const pair<float, float>& right) {return left.first < right.first; });

						// First two/three are closest (we will never see all four)
						float fBound = 0.01;
						if (acos(p.at(0).second) < fBound) bBoundary = true;
						if (acos(p.at(1).second) < fBound) bBoundary = true;
						if (acos(p.at(2).second) < fBound) bBoundary = true;
					}
				}
			}

			// Calculate distance to ceiling and floor
			int nCeiling = (float)(ScreenHeight() / 2.0) - ScreenHeight() / ((float)fDistanceToWall);
			int nFloor = ScreenHeight() - nCeiling;

			// Shader walls based on distance
			short nShade = ' ';
			if (fDistanceToWall <= fDepth / 4.0f)			nShade = 0x2588;	// Very close	
			else if (fDistanceToWall < fDepth / 3.0f)		nShade = 0x2593;
			else if (fDistanceToWall < fDepth / 2.0f)		nShade = 0x2592;
			else if (fDistanceToWall < fDepth)				nShade = 0x2591;
			else											nShade = ' ';		// Too far away

			if (bBoundary)		nShade = ' '; // Black it out

			for (int y = 0; y < ScreenHeight(); y++)
			{
				// Each Row
				if (y <= nCeiling)
					Draw(x, y, L' '); // instead of screen[y * ScreenWidth() + x] = ' ';
				else if (y > nCeiling && y <= nFloor)
					Draw(x, y, nShade);
				else // Floor
				{
					// Shade floor based on distance
					float b = 1.0f - (((float)y - ScreenHeight() / 2.0f) / ((float)ScreenHeight() / 2.0f));
					if (b < 0.25)		nShade = '#';
					else if (b < 0.5)	nShade = 'x';
					else if (b < 0.75)	nShade = '.';
					else if (b < 0.9)	nShade = '-';
					else				nShade = ' ';
					Draw(x, y, nShade);
				}
			}
		}

		// Display Map
		for (int nx = 0; nx < nMapWidth; nx++)
			for (int ny = 0; ny < nMapWidth; ny++)
				Draw(nx + 1, ny + 1, map[ny * nMapWidth + nx]);
		Draw((int)fPlayerY + 1, (int)fPlayerX + 1, L'P');

		return true;
	}
	
};

int main()
{
	setlocale(LC_CTYPE, "Polish"); // żeby móc komentować z polskimi znakami


	UltimateConsoleFPS game;
	game.ConstructConsole(320, 240, 4, 4);
	game.Start();
	//// Display Stats
	//swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);

	//// Display Frame
	//screen[ScreenWidth() * ScreenHeight() - 1] = '\0';
	//WriteConsoleOutputCharacter(hConsole, screen, ScreenWidth() * ScreenHeight(), { 0,0 }, &dwBytesWritten);


	}