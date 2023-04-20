#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

class Input : public sf::Drawable{
    private:
        sf::CircleShape shape;
        bool isSelected;
        const char* lastColor;

    public:
        Input() {
            shape.setRadius(100.f);
            shape.setPosition(1800, 600);
            shape.setFillColor(sf::Color::Blue);
            lastColor = "Blue";
        }
        sf::CircleShape getShape() {return shape;} 

        bool getSelected() {return isSelected;}
        void setSelected(bool newVal) {isSelected = newVal;}

        float getRadius() {return shape.getRadius();}
        void setRadius(float newRadius) {shape.setRadius(newRadius);}

        void move(float x, float y) {shape.setPosition(x, y);}
        float getX() {return shape.getPosition().x;}
        float getY() {return shape.getPosition().y;}

        void setColor(sf::Color color) {shape.setFillColor(color);}
        sf::Color getColor() {return shape.getFillColor();}
        const char* getColorName() {return lastColor;}
        void setColorName(const char* newName) {lastColor = newName;}

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(shape, states);
        }
};
