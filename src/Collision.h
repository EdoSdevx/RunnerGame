#pragma once

inline bool checkCollision(double x1, double y1, int w1, int h1,
                           double x2, double y2, int w2, int h2)
{
    return (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}
