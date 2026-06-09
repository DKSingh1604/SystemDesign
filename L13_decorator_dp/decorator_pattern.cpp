#include <iostream>
using namespace std;

//PIZZA SHOP

class Pizza {
    public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;
    virtual ~Pizza() {};
};

class SimplePizza : public Pizza{
    public:
    string getDescription() override {
       return "This is Simple Pizza";
    }
    double cost() override {
        return 50;
    }
};

class PizzaDecorator : public Pizza {
    protected:
    Pizza* pizza;

    public:
    PizzaDecorator(Pizza* p) : pizza(p){}
};

class SaucePizzaDecorator : public PizzaDecorator {
    public:
    SaucePizzaDecorator(Pizza* p) : PizzaDecorator(p){};
    string getDescription() override {
        return pizza->getDescription() + " with Sauce"; 
    }
    double cost () override {
        return pizza->cost() + 200;
    }
};

class CherryDecorator : public PizzaDecorator {
    public:
    CherryDecorator(Pizza* p) : PizzaDecorator(p){}

    string getDescription() override {
        return pizza->getDescription() + " with Cherry";
    }

    double cost() override {
        return pizza->cost() + 300;
    }
};

class ToppingsDecorator : public PizzaDecorator {
    public:
    ToppingsDecorator(Pizza* p) : PizzaDecorator(p){}

    string getDescription()override{
        return pizza -> getDescription() + " with Toppings";
    }

    double cost () override {
        return pizza -> cost() + 500;
    }
};

int main(){

    Pizza* myPizza = new SimplePizza();
    cout<<myPizza->getDescription()<<" : $"<<myPizza->cost()<<endl;

    myPizza = new CherryDecorator(myPizza);
    cout<<myPizza->getDescription()<<" : $"<<myPizza->cost()<<endl;

    myPizza = new ToppingsDecorator(myPizza);
    cout<<myPizza->getDescription()<<" : $"<<myPizza->cost()<<endl;

    
    
    return 0;

}