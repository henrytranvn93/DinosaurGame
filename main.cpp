#include <iostream>
#include <string>
#include "raylib.h"

class GameWindow {
    public:
        int width;
        int height;
        std::string title;
        GameWindow(int window_width, int window_height, std::string window_title) {
            width = window_width;
            height = window_height;
            title = window_title;
        }
        void Initialize() {
            return InitWindow(this->width, this->height, this->title.c_str());
        }
};


class MainCharacter {
    public:
        int coordinate_x;
        int coordinate_y;
        int circle_radius;
        Color color; 
        MainCharacter(int x, int y, int radius, Color color) {
            coordinate_x = x;
            coordinate_y = y;
            circle_radius = radius;
        }
        void renderMain() {
            return DrawCircle(coordinate_x, coordinate_y, circle_radius, BLUE);
        }

};

int main () {
    // Initialize windows
    int width {800};
    int height {450};

    GameWindow axe_window(width, height, "Dinosaur Game");
    axe_window.Initialize();

    // Initialize main character
    int circle_x {width/2};
    int circle_y {height/2};
    int circle_radius {25};

    MainCharacter circle(circle_x, circle_y, circle_radius, BLUE);

    // axe coordinates
    int axe_x {400};
    int axe_y {0};
    int axe_length {50};

    // direction
    int direction {10};

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Game logic starts

        DrawCircle(circle_x, circle_y, circle_radius, BLUE);
        DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

        // move the axe;
        axe_y += direction;
        if (axe_y > height || axe_y < 0) {
            direction = -direction;
        }

        if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && circle_x < width) {
            circle_x = circle_x + 10;
        }

        if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && circle_x > 0) {
            circle_x -= 10;
        }

        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && circle_y > 0) {
            circle_y -= 10;
        }

        if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && circle_y < height) {
            circle_y += 10;
        }


        // Game logic ends
        EndDrawing();
    }
}