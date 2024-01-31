#include <raylib.h>
using namespace std;
#include <string>
#include <iostream>

class Ball
{
public:
	float x;
	float y;
	float speedX;
	float speedY;
	float radius;

	void Draw()
	{
		DrawCircle(x, y, radius, WHITE);
	}
};

class Player
{
public:
	float x;
	float y;
	float speed;
	float side;
	int ballPos;

	Player();
	//Player(float x, float y, float side, float speed);
	
	Rectangle getRect()
	{
		return Rectangle{ x - side / 2, y - side / 2, 30, 30}; // offset needed to properly move the rectangle by its center and not the top left corner.
	}

	void Draw()
	{
		DrawRectangleRec(getRect(), WHITE);
	}

	//bool playerCollision(Player p1, Player p2);

};

Player::Player()
{
	x = GetScreenWidth() / 2;
	y = GetScreenHeight() / 2;			// x and y represent the center of the rectangle now that the rectangle is offset.
	side = 30;
	speed = 300;
	ballPos = 0;
}

void DrawBorder()
{
	DrawRectangle(5, 5, GetScreenWidth() - 10, GetScreenHeight() - 10, BLACK);
}

void DrawGoal()
{
	DrawRectangle(0, (GetScreenHeight() - 200) / 2, 10, 200, BLACK);
	DrawRectangle(GetScreenWidth() - 10, (GetScreenHeight()-200) / 2, 10, 200, BLACK);
}

float kickX(float posX, float& speed, int& speedDecX, float posY, int flagPos, int& bounceFlag)
{
	//int temp = 0;

	if (flagPos == 2)
	{
		if (bounceFlag == 1)
		{
			posX -= speed * GetFrameTime();
			speedDecX = 33;
		}

		else
			posX += speed * GetFrameTime();
	}
	
	else if (flagPos == 1)
	{
		if (bounceFlag == 1)
		{
			posX += speed * GetFrameTime();
			speedDecX = 33;
		}

		else
			posX -= speed * GetFrameTime();

	}

	if (speed != 0)
	{
		if (posX < 10 || posX > GetScreenWidth()  - 10)		//ball bounces off left and right end of screen
		{
			if (posY < GetScreenHeight() - 300 && posY > 300) //the ball goes through the goal parameters.
			{
				speedDecX = 11;
				speedDecX *= -1;
			}

			else 
			{
				speed *= -1;
				speedDecX = 11;
				speedDecX *= -1;
			}
		}
		speed -= speedDecX;
	}

	if (speed >= 0 && speed * GetFrameTime() <= 1)
	{
		speed = 0;
		bounceFlag = 0;
	}

	return posX;
}

float kickY(float posY, float& speed, int direction, int& speedDecY, int bounceFlag) // puts curve on the ball (this took me an embarrassing amount of time to get "right").
{

	if (posY < 10 || posY > GetScreenHeight() - 10)		//ball bounces off top and bottom of screen;
	{
		speedDecY *= -1;
	}
																		//MAYBE TO DO: fine tune curving when ball bounces off the wall.
	if (direction == 1)
	{
		if (speed >= -70)
			posY -= 2*speedDecY;
	}

	if (direction == -1)
	{
		if (speed >= -70)
			posY += 2*speedDecY;
	}


	if (speed >= -70)				//serves as a "clock" for how long the y position of the ball will change.
	{
		if (bounceFlag == 1)
			speed -= 20;

		else
			speed -= 5;

	}

	return posY;
}


bool playerCollision(Player p1, Player p2)	//Checks if the players collide... not sure if necessary since the is an if statment in main - check that.
{
	if (CheckCollisionRecs(p1.getRect(), p2.getRect()))
		return true;

	else
		return false;
}

void playerBounce(Player p1, Player p2, float& x1, float& y1)		//TODO: create function that knocks both players back when colliding.
{
	if (playerCollision(p1, p2))
	{
		x1 += 10;					//TODO: figure out how to send the players backwards depending on what direction they come from.
		y1 += 10;					//		maybe something with checking slopes or subtracting the last two values of x/y and see if 
	}
}


int main()
{
	InitWindow(1200, 800, "Soccer");

	const char* startText = nullptr;
	int startFlag = 0;

	Ball ball;
	ball.x = GetScreenWidth() / 2.0;
	ball.y = GetScreenHeight() / 2.0;
	ball.radius = 10;
	ball.speedX = 0;
	ball.speedY = 0;

	Player playerR1;
	playerR1.x = GetScreenWidth() / 2.0 + 120;
	playerR1.y;			// x and y represent the center of the rectangle now that the rectangle is offset.
	playerR1.side;
	playerR1.speed;
	playerR1.ballPos = 1;

	Player playerL1;
	playerL1.x = GetScreenWidth() / 2.0 - 120;
	playerL1.y;			// x and y represent the center of the rectangle now that the rectangle is offset.
	playerL1.side;
	playerL1.speed;
	playerL1.ballPos = 5;

	int ballPos = 0;		//Marks what team has the ball...I think
	int flagPos = 0;			//Marks what player has the ball

	int kickFlag = 0;
	int kickFlagY = 0;
	float temp = 400;
	int speedDecX = 10;
	int speedDecY = 1;
	int bounceFlag = 0;

	const char* winnerText = "Space to Start";
	int scoreLeft = 0;
	int scoreRight = 0;
	bool R = 0;
	bool L = 0;

	char key = 'null';
	char lastKey = 'null';
	

	SetTargetFPS(60);
	
	playerCollision(playerR1, playerL1);			//YOU CAN PASS WHOLE OBJECTS TO A FUNCTION, I WISH I LEARNED THAT 3 HOURS AGO!!!!

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_SPACE))
			startFlag = 1;
			
		if (startFlag == 1)
		{
			ball.Draw();
			R = false;
			L = false;

			if (IsKeyDown(KEY_L))
			{
				if (playerR1.x <= GetScreenWidth() - 20)		//player gets stopped at border.
				{
					playerR1.x += playerR1.speed * GetFrameTime();	// regulates the speed according to the fps.
				}
			}

			if (IsKeyDown(KEY_J))
			{
				if (playerR1.x >= 0 + 20)
				{
					playerR1.x -= playerR1.speed * GetFrameTime();
				}
			}

			if (IsKeyDown(KEY_I))
			{
				if (playerR1.y >= 0 + 20)
				{
					playerR1.y -= playerR1.speed * GetFrameTime();
				}
			}

			if (IsKeyDown(KEY_K))
			{
				if (playerR1.y <= GetScreenHeight() - 20)
				{
					playerR1.y += playerR1.speed * GetFrameTime();
				}
			}

			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, playerR1.getRect()))
			{
				bounceFlag = 0;

				if (ball.speedX < 600)
				{
					ballPos = playerR1.ballPos;
					kickFlag = 0;
					kickFlagY = 0;
				}

				if (ball.speedX > 600)
				{
					flagPos = 2;
					bounceFlag = 1;
				}

				temp = 0;					//Not sure if this does anything, check up on that.

				speedDecX = 10;
				speedDecY = 1;
			}

			if (ballPos == 1)
			{
				ball.x = playerR1.x - ball.radius - playerR1.side / 2;	// ball "sticks" to the player when touched
				ball.y = playerR1.y;
				flagPos = 1;

				if (IsKeyPressed(KEY_U))
				{
					ball.speedX = 800;
					ball.speedY = playerR1.speed;

					kickFlag = 1;
					ballPos = 0;

					if (IsKeyDown(KEY_K))
						kickFlagY = -1;

					if (IsKeyDown(KEY_I))
						kickFlagY = 1;

				}
			}
			
			if (IsKeyDown(KEY_D))
			{
				if (playerL1.x <= GetScreenWidth() - 20)		//player gets stopped at border.
				{
					playerL1.x += playerL1.speed * GetFrameTime();	// regulates the speed according to the fps.
				}
			}

			if (IsKeyDown(KEY_A))
			{
				if (playerL1.x >= 0 + 20)
				{
					playerL1.x -= playerL1.speed * GetFrameTime();
				}
			}

			if (IsKeyDown(KEY_W))
			{
				if (playerL1.y >= 0 + 20)
				{
					playerL1.y -= playerL1.speed * GetFrameTime();
				}
			}

			if (IsKeyDown(KEY_S))
			{
				if (playerL1.y <= GetScreenHeight() - 20)
				{
					playerL1.y += playerL1.speed * GetFrameTime();
				}
			}

			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, playerL1.getRect()))
			{
				bounceFlag = 0;

				if (ball.speedX < 600)
				{
					ballPos = playerL1.ballPos;
					kickFlag = 0;
					kickFlagY = 0;
				}

				if (ball.speedX > 600)
				{
					flagPos = 1;
					bounceFlag = 1;
				}

				temp = 0;					//Not sure if this does anything, check up on that.

				speedDecX = 10;
				speedDecY = 1;
			}

			if (ballPos == 5)
			{
				ball.x = playerL1.x + ball.radius + playerL1.side / 2;	// ball "sticks" to the player when touched
				ball.y = playerL1.y;
				flagPos = 2;

				if (IsKeyPressed(KEY_Q))
				{
					ball.speedX = 800;
					ball.speedY = playerL1.speed;

					kickFlag = 1;
					ballPos = 0;

					if (IsKeyDown(KEY_S))
						kickFlagY = -1;

					if (IsKeyDown(KEY_W))
						kickFlagY = 1;

				}
			}


			if (kickFlag == 1)
			{
				ball.x = kickX(ball.x, ball.speedX, speedDecX, ball.y, flagPos, bounceFlag);
				ball.y = kickY(ball.y, ball.speedY, kickFlagY, speedDecY, bounceFlag);
			}

			if (ball.x < 0)
			{
				winnerText = "Right Player Wins!";
				R = true;
			}

			if (ball.x > GetScreenWidth())
			{
				winnerText = "Left Player Wins!";
				L = true;
			}

			if (winnerText && IsKeyPressed(KEY_SPACE))
			{
				//playerR1.getRect();
				//Player();
				ball.x = GetScreenWidth() / 2;
				ball.y = GetScreenHeight() / 2;
				ball.speedX = 0;
				ball.speedY = 0;

				playerR1.x = GetScreenWidth() / 2 + 120;
				playerR1.y = GetScreenHeight() / 2;
				playerR1.side;
				playerR1.speed;
				playerR1.ballPos = 1;

				playerL1.x = GetScreenWidth() / 2 - 120;
				playerL1.y = GetScreenHeight() / 2;
				playerL1.side;
				playerL1.speed;
				playerL1.ballPos = 5;

				winnerText = nullptr;

				if (L == true)
					scoreLeft++;

				else if (R == true)
					scoreRight++;
			}

			if (CheckCollisionRecs(playerL1.getRect(), playerR1.getRect()))			//checks when two players collide
			{
				////playerR1.speed = 0;
				//if (lastKey == key)							//makes it so players don't go through each other.
				//	playerR1.speed = 0;
				//else
				//{
				//	playerR1.speed = 300;
				//	lastKey = key;
				//}

				playerBounce(playerL1, playerR1, playerL1.x, playerL1.y);
			}

			if (IsKeyDown(KEY_L))								//might be unnecessary after the playerBounce function is completed.
				key = 'l';

			if (IsKeyDown(KEY_J))
				key = 'j';

			if (IsKeyDown(KEY_I))
				key = 'i';

			if (IsKeyDown(KEY_K))
				key = 'k';

			/*cout << key;
			cout << lastKey << endl;*/


			//TODO: Create a loop that calls the playerCollision function for every combination of two players.
			//		Put all the players in an array and use a for loop
		}

		BeginDrawing();
		ClearBackground(WHITE);
		int textWidth = MeasureText(winnerText, 60);
		
		if (startFlag == 0)
			DrawText(startText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 90, 60, GREEN);
		
		DrawBorder();
		DrawGoal();
		ball.Draw();
		playerR1.Draw();
		playerL1.Draw();

		if (winnerText)
		{
			textWidth = MeasureText(winnerText, 60);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 90, 60, GREEN);
		}
			
		DrawText(TextFormat("%i", scoreLeft), GetScreenWidth() / 2 - 140, 20, 30, GREEN);
		DrawText(TextFormat("%i", scoreRight), GetScreenWidth() / 2 + 100, 20, 30, GREEN);

		EndDrawing();
	}

	CloseWindow();
	return 0;

}