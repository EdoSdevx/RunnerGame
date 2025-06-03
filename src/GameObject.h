#pragma once

struct Obstacle
{
    double x,y;
    int width,height;
};


class GameObject
{
    public:

        GameObject(double xPos, double yPos, int width, int height)
                 :m_x(xPos),m_y(yPos),m_width(width),m_height(height) {}

        virtual ~GameObject() {}

        virtual void update(double deltaTime) = 0;
        virtual void render() = 0;

        double getX() const { return m_x; }
        double getY() const { return m_y; }

        int getWidth() const { return m_width; }
        int getHeight() const { return m_height; }

        void setX(double x) { m_x = x; }
        void setY(double y) { m_y = y; }

        void setWidth(int w) { m_width = w; }
        void setHeight(int h) { m_height = h; }

    protected:
    
        double m_x = 0;
        double m_y = 0;

        int m_width = 0;
        int m_height = 0;
};
