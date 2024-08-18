#include <numeric>

#include "screen.h"
#include "structs.h"

void rotate(vec3& point, float x = 1, float y = 1, float z = 1);
void draw_line(Screen& screen, float x1, float y1, float x2, float y2);

int main() {
    Screen screen;
    std::vector<vec3> points{
        {100, 100, 100}, {200, 100, 100}, {200, 200, 100}, {100, 200, 100},

        {100, 100, 200}, {200, 100, 200}, {200, 200, 200}, {100, 200, 200}};
    std::vector<connection> connections{
        {0, 4}, {1, 5}, {2, 6}, {3, 7}, {0, 1}, {1, 2},
        {2, 3}, {3, 0}, {4, 5}, {5, 6}, {6, 7}, {7, 4},
    };
    vec3 centreoid{0, 0, 0};
    for (auto& p : points) {
        centreoid.x += p.x;
        centreoid.y += p.y;
        centreoid.z += p.z;
    }

    centreoid.x /= (float)points.size();
    centreoid.y /= (float)points.size();
    centreoid.z /= (float)points.size();

    while (true) {
        for (auto& p : points) {
            p.x -= centreoid.x;
            p.y -= centreoid.y;
            p.z -= centreoid.z;
            rotate(p, 0.02f, 0.01f, 0.002f);
            p.x += centreoid.x;
            p.y += centreoid.y;
            p.z += centreoid.z;
            screen.add_pixel(p.x, p.y);
        }
        for (auto& conn : connections) {
            draw_line(screen, points[conn.a].x, points[conn.a].y,
                      points[conn.b].x, points[conn.b].y);
        }

        screen.render();
        screen.clear();

        screen.handle_input();
        SDL_Delay(30);
    }
    return 0;
}
void draw_line(Screen& screen, float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;

    float length = std::sqrt(dx * dx + dy * dy);
    float angle = std::atan2(dy, dx);
    for (float i = 0; i < length; i++) {
        screen.add_pixel(x1 + std::cos(angle) * i, y1 + std::sin(angle) * i);
    }
}
void rotate(vec3& point, float x, float y, float z) {
    float rad = 0;

    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}