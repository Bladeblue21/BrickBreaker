//Basic Brick Breaker Game

/*TODO:

*/

#include <SFML/Graphics.hpp>

int main()
{
    int screenWidth = 1024;
    int screenHeight = 800;
    float PI = 3.14159265f;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Da Brick Breaker");

    //Brick related things
    const int numberOfBricks = 20;
    const int brickColumns = 5;
    const int brickRows = 4;

    float brickWidth = 50;
    float brickHeight = 25;

    sf::RectangleShape bricks[brickColumns * brickRows];
    int deadBricks[numberOfBricks] = { 1, 1, 1, 1, 1,
                                       1, 1, 1, 1, 1,
                                       1, 1, 1, 1, 1,
                                       1, 1, 1, 1, 1};

    int x, y;
    for (x = 0; x < brickColumns; x++)
    {
        for (y = 0; y < brickRows; y++)
        {
            bricks[brickColumns * y + x].setSize(sf::Vector2f(brickWidth, brickHeight));
            bricks[brickColumns * y + x].setFillColor(sf::Color::Magenta);
            bricks[brickColumns * y + x].setPosition(sf::Vector2f((x + 2) * 2.5f * brickWidth, (y + 2) * 3.f * brickHeight));
        }
    }

    //Ball related things
    float ballRadius = 15.f;
    float ballSpeed = 0.1f;
    float ballAngle = 220 * (PI / 180);

    sf::CircleShape ball(ballRadius);
    ball.setFillColor(sf::Color::Yellow);
    ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) + window.getSize().y / 4.f);

    //Paddle related things
    float paddleSpeed = 0.125f;

    sf::RectangleShape player_paddle(sf::Vector2f(100, 25));
    player_paddle.setFillColor(sf::Color::Cyan);
    player_paddle.setPosition((window.getSize().x / 2) - 50.f, (window.getSize().y) - 100.f);

    //Player Score
    int playerScore = 0;
    int brickScore = 10;

    sf::Font scoreFont;
    scoreFont.loadFromFile("sansation.ttf");

    sf::Text scoreText;
    scoreText.setFont(scoreFont);
    scoreText.setCharacterSize(32);
    scoreText.setColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x - 155.f, window.getSize().y - 45.f);

    int playerLives = 3;

    sf::Text livesText;
    livesText.setFont(scoreFont);
    livesText.setCharacterSize(32);
    livesText.setColor(sf::Color::White);
    livesText.setPosition(5.f, window.getSize().y - 45.f);

    //Game Over
    bool isGameOver = false;
    sf::Text gameOverText;
    gameOverText.setFont(scoreFont);
    gameOverText.setCharacterSize(64);
    gameOverText.setColor(sf::Color::Red);
    gameOverText.setPosition(window.getSize().x / 2 - 150.f, window.getSize().y / 2 - window.getSize().y / 4.f);


    sf::Clock clock;
    bool isPlaying = false;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                isPlaying = true;
            }
        }

        if (isPlaying)
        {
            window.clear(sf::Color::Black);

            //Player Controls
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                if (player_paddle.getPosition().x > 0)
                {
                    player_paddle.move(-paddleSpeed, 0);
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                if (player_paddle.getPosition().x < window.getSize().x - (player_paddle.getSize().x))
                {
                    player_paddle.move(paddleSpeed, 0);
                }
            }


            //Ball and Brick Collision
            for (int i = 0; i < numberOfBricks; i++)
            {
                if (deadBricks[i] == 1)
                {
                    if (ball.getGlobalBounds().intersects(bricks[i].getGlobalBounds()))
                    {
                        if (ball.getPosition().x + ballRadius > bricks[i].getPosition().x - bricks[i].getSize().x / 2 &&
                            ball.getPosition().x + ballRadius < bricks[i].getPosition().x - bricks[i].getSize().x / 4 &&
                            ball.getPosition().y + ballRadius > bricks[i].getPosition().y - bricks[i].getSize().y / 2 &&
                            ball.getPosition().y - ballRadius < bricks[i].getPosition().y + bricks[i].getSize().y / 2)
                        {
                            playerScore += brickScore;

                            ballAngle = PI - ballAngle;

                            ball.setPosition(bricks[i].getPosition().x - (bricks[i].getSize().x / 2) - ballRadius - 0.1f, ball.getPosition().y);
                            deadBricks[i] = 0;
                        }

                        else if (ball.getPosition().x - ballRadius < bricks[i].getPosition().x + bricks[i].getSize().x / 2 &&
                            ball.getPosition().x - ballRadius > bricks[i].getPosition().x + bricks[i].getSize().x / 4 &&
                            ball.getPosition().y + ballRadius > bricks[i].getPosition().y - bricks[i].getSize().y / 3 &&
                            ball.getPosition().y - ballRadius < bricks[i].getPosition().y + bricks[i].getSize().y / 3)
                        {
                            playerScore += brickScore;

                            ballAngle = PI - ballAngle;

                            ball.setPosition(bricks[i].getPosition().x + (bricks[i].getSize().x / 2) + ballRadius + 0.1f, ball.getPosition().y);
                            deadBricks[i] = 0;
                        }

                        else if (ball.getPosition().y - ballRadius < bricks[i].getPosition().y + bricks[i].getSize().y / 2 &&
                            ball.getPosition().y - ballRadius > bricks[i].getPosition().y + bricks[i].getSize().y / 4 &&
                            ball.getPosition().x + ballRadius > bricks[i].getPosition().x - bricks[i].getSize().x / 2 &&
                            ball.getPosition().x - ballRadius < bricks[i].getPosition().x + bricks[i].getSize().x)
                        {
                            playerScore += brickScore;

                            ballAngle = -ballAngle;

                            ball.setPosition(ball.getPosition().x, bricks[i].getPosition().y + (bricks[i].getSize().y / 2) + ballRadius + 0.1f);
                            deadBricks[i] = 0;
                        }

                        else if (ball.getPosition().y + ballRadius > bricks[i].getPosition().y - bricks[i].getSize().y / 2 &&
                            ball.getPosition().y + ballRadius < bricks[i].getPosition().y - bricks[i].getSize().y / 4 &&
                            ball.getPosition().x + ballRadius > bricks[i].getPosition().x - bricks[i].getSize().x / 2 &&
                            ball.getPosition().x - ballRadius < bricks[i].getPosition().x + bricks[i].getSize().x)
                        {
                            playerScore += brickScore;

                            ballAngle = -ballAngle;

                            ball.setPosition(ball.getPosition().x, bricks[i].getPosition().y - (bricks[i].getSize().y / 2) - ballRadius - 0.1f);
                            deadBricks[i] = 0;
                        }
                    }
                }
            }

            //Ball Wall Collision
            if (ball.getPosition().x + ballRadius >= window.getSize().x)
            {
                ballAngle = PI - ballAngle;
            }

            else if (ball.getPosition().x - ballRadius < 0)
            {
                ballAngle = PI - ballAngle;
            }

            else if (ball.getPosition().y - ballRadius <= 0)
            {
                ballAngle = -ballAngle;
            }

            else if (ball.getPosition().y > window.getSize().y)
            {
                ballAngle = -ballAngle;

                ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) + window.getSize().y / 4.f);

                if (playerLives > 1)
                {
                    playerLives--;
                }
                else
                {
                    isGameOver = true;
                }
                
                isPlaying = false;
            }

            //Paddle Collision
            if (ball.getGlobalBounds().intersects(player_paddle.getGlobalBounds()))
            {
                if (ball.getPosition().x + ballRadius > player_paddle.getPosition().x - player_paddle.getSize().x / 2 &&
                    ball.getPosition().x - ballRadius < player_paddle.getPosition().x + player_paddle.getSize().x &&
                    ball.getPosition().y + ballRadius > player_paddle.getPosition().y - player_paddle.getSize().y / 2 &&
                    ball.getPosition().y + ballRadius < player_paddle.getPosition().y - player_paddle.getSize().y / 4)
                {
                    ballAngle = -ballAngle;

                    ball.setPosition(ball.getPosition().x, player_paddle.getPosition().y - (player_paddle.getSize().y / 2) - ballRadius - 0.1f);
                }
            }

            ball.move((ballSpeed) * std::cos(ballAngle), (ballSpeed) * std::sin(ballAngle));
        }

        scoreText.setString("Score: " + std::to_string(playerScore));
        livesText.setString("Lives: " + std::to_string(playerLives));
        gameOverText.setString("Game Over!");

        window.clear();
        window.draw(scoreText);
        window.draw(livesText);

        for (int i = 0; i < numberOfBricks; i++)
            if (deadBricks[i] != 0)
                window.draw(bricks[i]);

        window.draw(ball);
        window.draw(player_paddle);

        if (isGameOver)
            window.draw(gameOverText);

        window.display();
    }

    return 0;
}