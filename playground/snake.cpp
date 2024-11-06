#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <glfw3.h>

extern GLFWwindow* window;

using namespace std;

enum Direction { UP, DOWN, LEFT, RIGHT };

struct SnakeSegment {
    int x, y;
};

int gridWidth = 25;
int gridHeight = 25;
Direction dir = RIGHT;
vector<SnakeSegment> snake;
SnakeSegment food;
int score = 0;  // Score variable

void initializeGame() {
    // create snake
    snake.push_back({ gridWidth / 2, gridHeight / 2 });
    snake.push_back({ gridWidth / 2 - 1, gridHeight / 2 });
    snake.push_back({ gridWidth / 2 - 2, gridHeight / 2 });

    // food
    srand(time(0));
    food.x = rand() % gridWidth;
    food.y = rand() % gridHeight;
}

void updateGame() {
    // move the snake
    SnakeSegment newHead = snake.front(); // Get the head of the snake
    if (dir == UP)    newHead.y += 1;
    if (dir == DOWN)  newHead.y -= 1;
    if (dir == LEFT)  newHead.x -= 1;
    if (dir == RIGHT) newHead.x += 1;

    // Check for collisions with the edges
    if (newHead.x < 0 || newHead.x >= gridWidth || newHead.y < 0 || newHead.y >= gridHeight) {
        printf("Game Over! Final Score: %d\n", score);
        exit(0);
    }

    // Check for collisions with itself
    for (const auto& segment : snake) {
        if (newHead.x == segment.x && newHead.y == segment.y) {
            printf("Game Over! Final Score: %d\n", score);
            exit(0);
        }
    }

    // after eating food
    snake.insert(snake.begin(), newHead);

    // check if food was eaten
    if (newHead.x == food.x && newHead.y == food.y) {
        score++;  // Increase score
        printf("Score: %d\n", score);  // Print score to the console
        // Generate new food
        food.x = rand() % gridWidth;
        food.y = rand() % gridHeight;
    }
    else {
        // Remove the tail if no food was eaten
        snake.pop_back();
    }
}

void drawSquare(int x, int y) {
    float size = 1.0f / gridWidth;
    float xpos = x * size * 2 - 1;
    float ypos = y * size * 2 - 1;

    glBegin(GL_QUADS);
    glVertex2f(xpos, ypos);
    glVertex2f(xpos + size * 2, ypos);
    glVertex2f(xpos + size * 2, ypos + size * 2);
    glVertex2f(xpos, ypos + size * 2);
    glEnd();
}

void renderGame() {
    // clear
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the snake
    glColor3f(0.0f, 1.0f, 0.0f); // Green color for the snake
    for (const auto& segment : snake) {
        drawSquare(segment.x, segment.y);
    }

    // Draw the food
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the food
    drawSquare(food.x, food.y);

    // Swap buffers
    glfwSwapBuffers(window);
}

void processInput() {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && dir != DOWN) {
        dir = UP;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && dir != UP) {
        dir = DOWN;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && dir != RIGHT) {
        dir = LEFT;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && dir != LEFT) {
        dir = RIGHT;
    }
}

int main(void)
{
    // initialize window
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    window = glfwCreateWindow(640, 480, "Snake Game", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    initializeGame();

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput();

        // Game logic
        updateGame();

        // Rendering
        renderGame();

        glfwPollEvents();
        //Speed
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }

    glfwTerminate();
    return 0;
}