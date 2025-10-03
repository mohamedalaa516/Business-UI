#pragma once
#include<string>
using namespace std;

class Person {
private:
    string Name;
public:
    void setName(const string& name);
    string getName() const;
};
class Seller : public Person {
private:
    int amount = 0;
    int totalPay = 0;
    string productName;
    int productPrice = 0;

public:
    enum class Goods { MohamedAttia = 150, NasrAbdelWanes = 270 };

    void setAmount(int amt);
    int getAmount() const;

    void setGoods(Goods g);


    void pay(int amountPaid);
    int getTotalPay() const;

    void printInfo() const;
};