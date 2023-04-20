#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Input.h"

bool isHoveringShape(const sf::CircleShape& shape, const sf::RenderWindow& window) {
    if(shape.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
        std::cout << "Yes" << std::endl;
        return true;
    }
    
    std::cout << "No" << std::endl;
    return false; 
}

int main() {
    sf::RenderWindow window(sf::VideoMode(2560, 1440), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    if(!ImGui::SFML::Init(window)) {
        return EXIT_FAILURE;
    }

    ImGui::GetIO().FontGlobalScale = 3.f;
    ImGui::GetStyle().ScaleAllSizes(3.f);

    Input input;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
                
            if(!ImGui::GetIO().WantCaptureMouse) {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    input.setSelected(isHoveringShape(input.getShape(), window));
                }
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::SetNextWindowSize(ImVec2(1000, 1440));
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::Begin("Control Panel", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        // Change radius
        static float newSize = input.getRadius();
        ImGui::SliderFloat("Slider", &newSize, 100.f, 600.f);

        // Change position
        static float x = 1800, y = 600;
        ImGui::SliderFloat("XSlide", &x, 1700.f, 1900.f);
        ImGui::SliderFloat("YSlide", &y, 500.f, 700.f);

        // Change color
        const char* items[] = {"Blue", "Green", "Red"};
        static const char* current_item = "Blue";
        sf::Color newColor;

        if(ImGui::BeginCombo("##combo", current_item)) {
            for(int i = 0; i < IM_ARRAYSIZE(items); i++) {
                bool is_selected = (current_item == items[i]);
                if(ImGui::Selectable(items[i], is_selected))
                        current_item = items[i];
            }
            ImGui::EndCombo();
        }

        if(input.getSelected()) {
        if(strcmp(current_item, "Blue") == 0)
            newColor = sf::Color::Blue;
        else if(strcmp(current_item, "Green") == 0)
            newColor = sf::Color::Green;
        else if(strcmp(current_item, "Red") == 0)
            newColor = sf::Color::Red;
        }

        if(!input.getSelected()) {
           newSize = input.getRadius();
           x = input.getX();
           y = input.getY();
           current_item = input.getColorName();
        }

        if(input.getSelected()) {
            input.setRadius(newSize);
            input.move(x, y);
            input.setColor(newColor);
            input.setColorName(current_item);
        }

        ImGui::End();

        window.clear();
        window.draw(input);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return 0;
}
