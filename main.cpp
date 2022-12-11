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
        MainCharacter(int x, int y, int radius, Color main_color) {
            coordinate_x = x;
            coordinate_y = y;
            circle_radius = radius;
            color = main_color;
        }
        void renderMain() {
            return DrawCircle(coordinate_x, coordinate_y, circle_radius, color);
        }

};

int main () {
    // Initialize windows
    int width {800};
    int height {450};

    GameWindow game_window(width, height, "Dinosaur Game");
    game_window.Initialize();

    // Initialize main character
    MainCharacter circle(width/2, height/2, 25, BLUE);

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

        circle.renderMain();
        DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);

        // move the axe;
        axe_y += direction;
        if (axe_y > height || axe_y < 0) {
            direction = -direction;
        }

        // move main character
        if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && circle.coordinate_x < width) {
            circle.coordinate_x += 10;
        }

        if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && circle.coordinate_x > 0) {
            circle.coordinate_x -= 10;
        }

        if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && circle.coordinate_y > 0) {
            circle.coordinate_y -= 10;
        }

        if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && circle.coordinate_y < height) {
            circle.coordinate_y += 10;
        }


        // Game logic ends
        EndDrawing();
    }
    return 0;
}