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
            InitWindow(width, height, title.c_str());
            InitAudioDevice();
        };
        void CloseGame() {
            CloseAudioDevice();
            CloseWindow();
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

class Challenger {
    public:
        int coordinate_x;
        int coordinate_y;
        int length;
        Color color;
        Challenger(int x, int y, int len, Color challenge_color) {
            coordinate_x = x;
            coordinate_y = y;
            length = len;
            color = challenge_color;
        }
        void renderChallenge() {
            return DrawRectangle(coordinate_x, coordinate_y, length, length, color);
        }
};

int main () {
    // Initialize windows
    int width {800};
    int height {450};


    GameWindow game_window(width, height, "Dinosaur Game");
    game_window.Initialize();

    // Initialize main character
    int radius {25};
    MainCharacter circle(width/2, height/2, radius, BLUE);

    // Initialize challenge (axe)
    int challenge_length {50};
    Challenger axe(500, 0, challenge_length, RED);

    // direction
    int direction {10};

    //Determind edges
    int l_main_x{circle.coordinate_x - circle.circle_radius};
    int r_main_x{circle.coordinate_x + circle.circle_radius};
    int u_main_x{circle.coordinate_y - circle.circle_radius};
    int b_main_x{circle.coordinate_y + circle.circle_radius};

    int l_axe_x{axe.coordinate_x};
    int r_axe_x{axe.coordinate_x + axe.length};
    int u_axe_x{axe.coordinate_y};
    int b_axe_x{axe.coordinate_y + axe.length};


    bool collision = b_axe_x >= u_main_x && 
                    u_axe_x <= b_main_x && 
                    r_axe_x >= l_main_x && 
                    l_axe_x <= r_main_x; 

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision) {
            DrawText("Game Over", width/2 - 60, height/2 - 10, 30, RED);
        } else {

            // Game logic starts
            l_main_x = circle.coordinate_x - circle.circle_radius;
            r_main_x = circle.coordinate_x + circle.circle_radius;
            u_main_x = circle.coordinate_y - circle.circle_radius;
            b_main_x = circle.coordinate_y + circle.circle_radius;

            l_axe_x = axe.coordinate_x;
            r_axe_x = axe.coordinate_x + axe.length;
            u_axe_x = axe.coordinate_y;
            b_axe_x = axe.coordinate_y + axe.length;

            collision = b_axe_x >= u_main_x && 
                    u_axe_x <= b_main_x && 
                    r_axe_x >= l_main_x && 
                    l_axe_x <= r_main_x; 


            circle.renderMain();
            axe.renderChallenge();

            // move the axe/challenger;
            axe.coordinate_y += direction;
            if (axe.coordinate_y + axe.length > height || axe.coordinate_y < 0) {
                direction = -direction;
            }

            // move main character
            if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && r_main_x < width) {
                circle.coordinate_x += 10;
            }

            if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && l_main_x > 0) {
                circle.coordinate_x -= 10;
            }

            if ((IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) && u_main_x > 0) {
                circle.coordinate_y -= 10;
            }

            if ((IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) && b_main_x < height) {
                circle.coordinate_y += 10;
            }
        }


        // Game logic ends
        EndDrawing();
    }

    game_window.CloseGame();
    
    return 0;
}