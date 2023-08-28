#include <iostream>
#include <raylib.h>

struct Ball {
    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;
};

int main() {
    const float aspectRatio = 16.0 / 9;
    const int height = 1080;
    const int width = height * aspectRatio;
    const int fpsFontSize = height * (1.0 / 36);

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(width, height, "Testezin");
    SetTargetFPS(60);

    unsigned int count = 0;
    struct Ball* balls[10000];

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if (count < 10000) {
                struct Ball* tmp = (struct Ball*) malloc(sizeof(struct Ball));
                tmp->color = BLUE;
                tmp->pos = GetMousePosition();
                tmp->radius = 4;
                tmp->vel = (Vector2){((float)rand()/(float)(RAND_MAX/2.0))-1, ((float)rand()/(float)(RAND_MAX/2.0))-1};

                balls[count] = tmp;
                count++;
            }
        }

        for (int i = 0; i < count; i++) {
            float x = balls[i]->pos.x;
            float y = balls[i]->pos.y;

            if (x - balls[i]->radius < 0 || x + balls[i]->radius > width) {
                balls[i]->vel.x *= -1; 
            }
            if (y - balls[i]->radius < 0 || y + balls[i]->radius > height) {
                balls[i]->vel.y *= -1;
            }

            balls[i]->pos.x += balls[i]->vel.x;
            balls[i]->pos.y += balls[i]->vel.y;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        for (int i = 0; i < count; i++) {
            DrawCircleV(balls[i]->pos, balls[i]->radius, balls[i]->color);
        }

        char str[10];
        sprintf(str, "%d", GetFPS());
        DrawText(str, 0, 0, fpsFontSize, RAYWHITE);
        sprintf(str, "%d", count);
        DrawText(str, 0, height - fpsFontSize, fpsFontSize, RAYWHITE);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
