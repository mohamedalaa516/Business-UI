#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include <map>
#include<iostream>
#include <string>
#include "Person.h"

using namespace std;

int main() {
    unsigned int width = 640;
    unsigned int height = 360;
    sf::RenderWindow window(sf::VideoMode(width, height), "Seller System GUI");

    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);


    map<string, Seller> HashSeller;
    char nameInput[128] = "";
    int amountInput = 0;
    int productChoice = 0;
    int payInput = 0;
    char currentSeller[128] = "";
    int menuChoice = 0;

    sf::Clock deltaClock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        ImGui::Begin("Main Menu");

        if (menuChoice == 0) {
            if (ImGui::Button("Accountant")) {
                menuChoice = 1;
            }
            if (ImGui::Button("Seller")) {
                menuChoice = 2;
            }
            if (ImGui::Button("Exit")) {
                window.close();
            }
        }
        else if (menuChoice == 1) {
            ImGui::InputText("Name", nameInput, sizeof(nameInput));
            ImGui::InputInt("Quantity", &amountInput);
            ImGui::RadioButton("MohamedAttia", &productChoice, 1);
            ImGui::RadioButton("NasrAbdelWanes", &productChoice, 2);

            if (ImGui::Button("Add Seller")) {
                Seller s;
                s.setName(nameInput);
                s.setAmount(amountInput);
                Seller::Goods g = (productChoice == 1) ? Seller::Goods::MohamedAttia : Seller::Goods::NasrAbdelWanes;
                s.setGoods(g);

                HashSeller[nameInput] = s;
            }
            if (ImGui::Button("Back")) {
                menuChoice = 0;
            }
        }
        else if (menuChoice == 2) {
            ImGui::InputText("Enter your name", currentSeller, sizeof(currentSeller));
            if (ImGui::Button("Load Seller")) {
                if (HashSeller.find(currentSeller) == HashSeller.end()) {
                    ImGui::OpenPopup("Error");
                }
            }

            if (ImGui::BeginPopup("Error")) {
                ImGui::Text("Name not found!");
                if (ImGui::Button("OK")) ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }

            static bool showInfo = false;

            if (HashSeller.find(currentSeller) != HashSeller.end()) {
                Seller& s = HashSeller[currentSeller];

                if (ImGui::Button("Show Info")) {
                    showInfo = true;
                }

                if (showInfo) {
                    s.printInfo();
                    if (ImGui::Button("Hide Info")) {
                        showInfo = false;
                    }
                }

                ImGui::InputInt("Pay amount", &payInput);
                if (ImGui::Button("Pay")) {
                    s.pay(payInput);
                }

                ImGui::Text("Remaining total: %d", s.getTotalPay());
            }
        }

        ImGui::End();

        window.clear();
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

}