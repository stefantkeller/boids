#ifndef __DRAWABLE_H__
#define __DRAWABLE_H__

#include <SFML/Graphics.hpp>

class Drawable {
    public:
        Drawable();
        Drawable(const std::string &filename, int pos_x, int pos_y);
        ~Drawable();
        void setTexture(const std::string &filename);
        void setPosition(const float pos_x, const float pos_y);
        void setRotation(const float angle);
        virtual void drawOn(sf::RenderWindow &window);
        float x() const;
        float y() const;

    private:
        sf::Texture texture_;
        sf::Sprite sprite_;
};

#endif //__DRAWABLE_H__
