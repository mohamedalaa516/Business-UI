#include "Person.h"
#include<iostream>
#include<string>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"
using namespace std;

void Person::setName(const string& name) {
    Name = name;
}

string Person::getName() const {
    return Name;
}



void Seller::setAmount(int amt) {
    amount = amt;
    totalPay = amount * productPrice;
}

int Seller::getAmount() const {
    return amount;
}

void Seller::setGoods(Goods g) {
    if (g == Goods::MohamedAttia) {
        productName = "MohamedAttia";
        productPrice = 150;
    }
    else {
        productName = "NasrAbdelWanes";
        productPrice = 270;
    }
    totalPay = amount * productPrice;
}



void Seller::pay(int amountPaid) {
    totalPay -= amountPaid;
}

int Seller::getTotalPay() const {
    return totalPay;
}

void Seller::printInfo() const
{
    ImGui::Text("Name: %s", getName().c_str());
    ImGui::Text("Product: %s (%d per unit)", productName.c_str(), productPrice);
    ImGui::Text("Quantity: %d", amount);
    ImGui::Text("Total Pay: %d", totalPay);
}
