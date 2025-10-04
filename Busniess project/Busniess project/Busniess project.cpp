#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"

#include <map>
#include <string>
#include "Person.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Seller System GUI");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);
    //==============================================================//
    ImGui::StyleColorsDark(); 
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    // الخلفية تبقى شفافة
    colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_ChildBg] = ImVec4(0, 0, 0, 0);
    colors[ImGuiCol_PopupBg] = ImVec4(0, 0, 0, 0.8f);

    // النص أبيض
    colors[ImGuiCol_Text] = ImVec4(1, 1, 1, 1);

    // InputText خلفية شفافة وحدود فاتحة
    colors[ImGuiCol_FrameBg] = ImVec4(0, 0, 0, 0.5f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.2f, 0.2f, 0.2f, 0.7f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.3f, 0.3f, 0.3f, 0.9f);

    // زرار بلون أزرق فاتح
    colors[ImGuiCol_Button] = ImVec4(0.1f, 0.5f, 0.9f, 0.9f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.2f, 0.6f, 1.0f, 1.0f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.05f, 0.3f, 0.6f, 1.0f);
    //=====================================================================//

    //background
    sf::Texture texture;
    texture.loadFromFile("asset/atm.jpg");
    sf::Sprite sprite(texture);
    sprite.setScale(
        static_cast<float>(window.getSize().x) / texture.getSize().x,
        static_cast<float>(window.getSize().y) / texture.getSize().y
    );

    // Data
    map<string, Seller> HashSeller;
    char nameInput[128] = "";
    int amountInput = 0;
    int productChoice = 0;
    int payInput = 0;
    char currentSeller[128] = "";
    int menuChoice = 0;

    sf::Clock deltaClock;

    while (window.isOpen()) {
        // ---------------- Event Loop ----------------
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // ---------------- Update ImGui ----------------
        ImGui::SFML::Update(window, deltaClock.restart());

        // ---------------- Main Menu Window ----------------
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(window.getSize().x, window.getSize().y));



        ImGui::Begin("Buttons", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoBackground);  // 👈 من غير خلفية

        if (menuChoice == 0) {
            // ألوان وتنسيق الأزرار
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.5f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.7f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.3f, 0.7f, 1.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(20, 10));

            ImVec2 buttonSize(300, 80);

            float centerX = (ImGui::GetWindowSize().x - buttonSize.x) * 0.5f;
            float centerY = (ImGui::GetWindowSize().y - (buttonSize.y * 3 + 20 * 2)) * 0.5f;

            ImGui::SetCursorPos(ImVec2(centerX, centerY));
            if (ImGui::Button("Accountant", buttonSize)) menuChoice = 1;

            ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 20));
            if (ImGui::Button("Seller", buttonSize)) menuChoice = 2;

            ImGui::SetCursorPos(ImVec2(centerX, ImGui::GetCursorPosY() + 20));
            if (ImGui::Button("Exit", buttonSize)) window.close();

            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor(3);
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
            if (ImGui::Button("Back")) menuChoice = 0;
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

            if (ImGui::Button("Back")) menuChoice = 0;
        }

        ImGui::End(); // End Main Menu

        // ---------------- Render ----------------
        window.clear(sf::Color::Black);
        window.draw(sprite);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
