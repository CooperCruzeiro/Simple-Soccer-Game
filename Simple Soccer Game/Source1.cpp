//#include <raylib.h>
//using namespace std;
//#include <string>
//class Ball
//{
//public:
//	float x;
//	float y;
//	float speedY;
//	float speedX;
//	float radius;
//
//	void Draw()
//	{
//		DrawCircle(x, y, radius, WHITE);
//	}
//};
//
//class Paddle
//{
//public:
//	float x;
//	float y;
//	float speed;
//	float width;
//	float height;
//
//	Rectangle getRect()
//	{
//		return Rectangle{ x - width / 2, y - height / 2, 10, 100 };
//	}
//
//	void Draw()
//	{
//		DrawRectangleRec(getRect(), WHITE);
//	}
//};
//
//
//int main()
//{
//	InitWindow(800, 600, "Pong");
//
//	const char* startText = nullptr;
//	int startFlag = 0;
//
//	Ball ball;
//
//	ball.x = GetScreenWidth() / 2.0;
//	ball.y = GetScreenHeight() / 2.0;
//	ball.radius = 5;
//	ball.speedX = 300;
//	ball.speedY = 300;
//
//	Paddle leftPaddle;
//	leftPaddle.x = 50;
//	leftPaddle.y = GetScreenHeight() / 2;
//	leftPaddle.width = 10;
//	leftPaddle.height = 100;
//	leftPaddle.speed = 500;
//
//	Paddle rightPaddle;
//	rightPaddle.x = GetScreenWidth() - 50;
//	rightPaddle.y = GetScreenHeight() / 2;
//	rightPaddle.width = 10;
//	rightPaddle.height = 100;
//	rightPaddle.speed = 500;
//
//	const char* winnerText = "Space to Start";
//	int scoreLeft = 0;
//	int scoreRight = 0;
//	bool R = 0;
//	bool L = 0;
//
//	SetWindowState(FLAG_VSYNC_HINT);
//
//	while (!WindowShouldClose())
//	{
//		if (IsKeyPressed(KEY_SPACE))
//			startFlag = 1;
//
//		if (startFlag == 1)
//		{
//			ball.Draw();
//			R = false;
//			L = false;
//
//			ball.x += ball.speedX * GetFrameTime();
//			ball.y += ball.speedY * GetFrameTime();
//
//			if (ball.y < 0)
//			{
//				ball.y < 0;
//				ball.speedY *= -1;
//			}
//
//			if (ball.y > GetScreenHeight())
//			{
//				ball.y = GetScreenHeight();
//				ball.speedY *= -1;
//			}
//
//			if (IsKeyDown(KEY_W))
//			{
//				leftPaddle.y -= leftPaddle.speed * GetFrameTime();
//			}
//			if (IsKeyDown(KEY_S))
//			{
//				leftPaddle.y += leftPaddle.speed * GetFrameTime();
//			}
//
//			if (IsKeyDown(KEY_UP))
//			{
//				rightPaddle.y -= rightPaddle.speed * GetFrameTime();
//			}
//			if (IsKeyDown(KEY_DOWN))
//			{
//				rightPaddle.y += rightPaddle.speed * GetFrameTime();
//			}
//
//			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, leftPaddle.getRect()))
//			{
//				if (ball.speedX < 0)
//				{
//					ball.speedX *= -1.1;
//					ball.speedY = (ball.y - leftPaddle.y) / leftPaddle.height / 2 * ball.speedX;
//				}
//			}
//
//			if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, rightPaddle.getRect()))
//			{
//				if (ball.speedX > 0)
//				{
//					ball.speedX *= -1.1;
//					ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2) * -ball.speedX;
//				}
//			}
//
//			if (ball.x < 0)
//			{
//				winnerText = "Right Player Wins!";
//				R = true;
//			}
//
//			if (ball.x > GetScreenWidth())
//			{
//				winnerText = "Left Player Wins!";
//				L = true;
//			}
//
//			if (winnerText && IsKeyPressed(KEY_SPACE))
//			{
//				ball.x = GetScreenWidth() / 2;
//				ball.y = GetScreenHeight() / 2;
//				ball.speedX = 300;
//				ball.speedY = 300;
//
//				rightPaddle.x = GetScreenWidth() - 50;
//				rightPaddle.y = GetScreenHeight() / 2;
//				leftPaddle.x = 50;
//				leftPaddle.y = GetScreenHeight() / 2;
//
//				winnerText = nullptr;
//
//				if (L == true)
//					scoreLeft++;
//
//				if (R == true)
//					scoreRight++;
//			}
//		}
//
//		BeginDrawing();
//		ClearBackground(BLACK);
//
//		int textWidth = MeasureText(winnerText, 60);
//
//		if (startFlag == 0)
//			DrawText(startText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, GREEN);
//
//
//		leftPaddle.Draw();
//		rightPaddle.Draw();
//
//		if (winnerText)
//		{
//			textWidth = MeasureText(winnerText, 60);
//			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, GREEN);
//		}
//
//		DrawText(TextFormat("%i", scoreLeft), GetScreenWidth() / 2 - 140, 20, 30, GREEN);
//		DrawText(TextFormat("%i", scoreRight), GetScreenWidth() / 2 + 100, 20, 30, GREEN);
//
//		DrawFPS(10, 10);
//		EndDrawing();
//	}
//
//	CloseWindow();
//	return 0;
//}