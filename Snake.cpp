#include <sstream>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Create snake
RectangleShape rectangle(Vector2f(40, 40));
map<int, RectangleShape> snake = {
		{ 0, rectangle }
};

// Create fruit
RectangleShape fruit(Vector2f(40, 40));

int main() {
	int screenWidth = 1920;
	int screenHeight = 1080;

	int snakeSpeed = 40;

	// Create a video mode object
	VideoMode vm(screenWidth, screenHeight);

	// Crate and open a window for the game
	RenderWindow window(vm, "Snake", Style::Fullscreen);

	// Snake setup
	snake[0].setFillColor(Color::Green);
	snake[0].setPosition(Vector2f((screenWidth / 2), (screenHeight / 2 + 20)));

	// Set starting direction
	enum class direction { UP, RIGHT, DOWN, LEFT };
	direction snakeDirection = direction::RIGHT;

	// Fruit setup
	fruit.setFillColor(Color::Red);
	srand((int)time(0));
	int fruitY = (rand() % ((screenHeight - 40) / 40));
	int fruitX = (rand() % ((screenWidth - 40) / 40));
	while (!isSpaceEmpty(Vector2f(fruitX, fruitY))) {
		fruitY = (rand() % ((screenHeight - 40) / 40));
		fruitX = (rand() % ((screenWidth - 40) / 40));
	}

	fruit.setPosition(Vector2f(fruitX * 40, fruitY * 40));

	// Create score
	int score = 0;
	Text scoreText;
	scoreText.setString("Score: 0");
	Font font;
	font.loadFromFile("font/8bitOperatorPlus-Regular.ttf");
	scoreText.setFont(font);
	scoreText.setFillColor(Color::White);
	scoreText.setCharacterSize(60);
	scoreText.setPosition(10, 10);

	int frameTime = 240;
	int timer = 0;

	while (window.isOpen()) {

		// Exit on pressing ESC
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			window.close();
		}

		window.clear();

		// Player inputs
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			snakeDirection = direction::UP;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			snakeDirection = direction::RIGHT;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			snakeDirection = direction::DOWN;
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			snakeDirection = direction::LEFT;
		}

		window.draw(fruit);

		// Draw the snake
		for (int i = 0; i < snake.size(); i++) {
			window.draw(snake[0]);
		}

		// Draw the score
		window.draw(scoreText);

		// Keep the snake moving
		if (timer == frameTime) {
			switch (snakeDirection) {
			case direction::UP:
				snake[0].setPosition(snake[0].getPosition().x, snake[0].getPosition().y - snakeSpeed);
				break;
			case direction::RIGHT:
				snake[0].setPosition(snake[0].getPosition().x + snakeSpeed, snake[0].getPosition().y);
				break;
			case direction::DOWN:
				snake[0].setPosition(snake[0].getPosition().x, snake[0].getPosition().y + snakeSpeed);
				break;
			case direction::LEFT:
				snake[0].setPosition(snake[0].getPosition().x - snakeSpeed, snake[0].getPosition().y);
				break;
			}

			if (snake[0].getPosition() == fruit.getPosition()) {
				score++;
				stringstream ss;
				ss << "Score: " << score;
				scoreText.setString(ss.str());

				if (score % 10 == 0 && frameTime > 60) {
					frameTime -= 20;
				}
			}

			timer = 0;
		}

		timer++;

		// Display all visuals
		window.display();
	}
}

bool isSpaceEmpty(Vector2f coords) {
	if (snake[0].getPosition() != coords) {
		return true;
	}
	else {
		return false;
	}
}
