#include <iostream>
using namespace std;

class Coffee {
public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;
    virtual ~Coffee(){}
};

class SimpleCoffee : public Coffee{
public:
    string getDescription() override{
        return "Simple Coffee";
    }

    double cost() override {
        return 50;
    }
};

//DECORATORS
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee; // This is the object being wrapped
    
public:
    CoffeeDecorator(Coffee * c) : coffee(c){}
};

class MilkDecorator : public CoffeeDecorator {
    public:
    MilkDecorator(Coffee* c) : CoffeeDecorator(c){}

    string getDescription() override {
        return coffee -> getDescription() + ", Milk";
    }

    double cost() override {
        return coffee -> cost() + 10;
    }

    
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(Coffee* c) : CoffeeDecorator(c) {}
    
    string getDescription() override {
        return coffee->getDescription() + ", Sugar";
    }
    double cost() override {
        return coffee->cost() + 5;
    }
};

class CaramelDecorator : public CoffeeDecorator {
public:
    CaramelDecorator(Coffee* c) : CoffeeDecorator(c) {}
    
    string getDescription() override {
        return coffee->getDescription() + ", Caramel";
    }
    double cost() override {
        return coffee->cost() + 20;
    }
};

int main (){

    Coffee* myCoffee = new SimpleCoffee();
    cout<<myCoffee -> getDescription() << " : $"<<myCoffee -> cost()<<endl;

    myCoffee = new MilkDecorator(myCoffee);
    cout<<myCoffee->getDescription()<<" : $"<<myCoffee->cost()<<endl;

    myCoffee = new SugarDecorator(myCoffee);
    cout<<myCoffee->getDescription()<<" : $"<<myCoffee->cost()<<endl;
    
    myCoffee = new CaramelDecorator(myCoffee);
    cout<<myCoffee->getDescription()<<" : $"<<myCoffee->cost()<<endl;

    Coffee* specialCoffee = new CaramelDecorator(new MilkDecorator(new SimpleCoffee()));
    cout<<specialCoffee->getDescription()<<" : $"<<specialCoffee->cost()<<endl;


    return 0;
}