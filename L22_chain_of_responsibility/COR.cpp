#include <iostream>
using namespace std;

//Abstract Handler (Base Class)
class IMoneyHandler {
protected:
    IMoneyHandler* nextHandler;

public:
    IMoneyHandler(){
        this->nextHandler = NULL;
    }

    void setNextHandler(IMoneyHandler* next){
        nextHandler = next;
    }

    virtual void dispense(int amount) = 0;
};

class ThousandHandler : public IMoneyHandler {
private:
    int numNotes;

public:
    ThousandHandler (int numNotes) {
        this->numNotes = numNotes;
    }

    void dispense (int amount) override {
        int notesNeeded = amount / 1000;
        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else{
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) {
            cout<<"Dispensing "<<notesNeeded<< " * ₹1000 notes."<<endl;
        }

        int remainingAmount = amount - (notesNeeded * 1000);
        if(remainingAmount > 0){
            if(nextHandler != NULL) nextHandler->dispense(remainingAmount);
            else{
                cout<<"Remaining amount of ₹"<<remainingAmount<<" cannot be fulfilled.";
            }
        }
    }
};

class FiveHundredHandler : public IMoneyHandler {
private:
    int numNotes;

public:
    FiveHundredHandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 500;
        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else{
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) {
            cout<<"Dispensing "<<notesNeeded<< " * ₹500 notes."<<endl;
        }

        int remainingAmount = amount - (notesNeeded * 500);
        if(remainingAmount > 0){
            if(nextHandler != NULL) nextHandler->dispense(remainingAmount);
            else{
                cout<<"Remaining amount of ₹"<<remainingAmount<<" cannot be fulfilled.";
            }
        }
    }
};

class TwoHundredhandler : public IMoneyHandler {
private:
    int numNotes;

public:
    TwoHundredhandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 200;
        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else{
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) {
            cout<<"Dispensing "<<notesNeeded<< " * ₹200 notes."<<endl;
        }

        int remainingAmount = amount - (notesNeeded * 200);
        if(remainingAmount > 0){
            if(nextHandler != NULL) nextHandler->dispense(remainingAmount);
            else{
                cout<<"Remaining amount of ₹"<<remainingAmount<<" cannot be fulfilled.";
            }
        }
    }
};

class OneHundredhandler : public IMoneyHandler {
private:
    int numNotes;

public:
    OneHundredhandler(int numNotes){
        this->numNotes = numNotes;
    }

    void dispense(int amount) override {
        int notesNeeded = amount / 100;
        if(notesNeeded > numNotes){
            notesNeeded = numNotes;
            numNotes = 0;
        }
        else{
            numNotes -= notesNeeded;
        }

        if(notesNeeded > 0) {
            cout<<"Dispensing "<<notesNeeded<< " * ₹100 notes."<<endl;
        }

        int remainingAmount = amount - (notesNeeded * 100);
        if(remainingAmount > 0){
            if(nextHandler != NULL) nextHandler->dispense(remainingAmount);
            else{
                cout<<"Remaining amount of ₹"<<remainingAmount<<" cannot be fulfilled.";
            }
        }
    }
};

//Client Code
int main(){
    IMoneyHandler* thousandHandler = new ThousandHandler(3);
    IMoneyHandler* fiveHundredHandler = new FiveHundredHandler(5);
    IMoneyHandler* twoHundredHandler = new TwoHundredhandler(18);
    IMoneyHandler* oneHundredHandler = new OneHundredhandler(20);
    
    thousandHandler->setNextHandler(fiveHundredHandler);
    fiveHundredHandler->setNextHandler(twoHundredHandler);
    twoHundredHandler->setNextHandler(oneHundredHandler);

    int amountToWithdraw = 4500;

    cout<<endl<<"Dispensing amount: ₹"<<amountToWithdraw<<endl;
    thousandHandler->dispense(amountToWithdraw);

    return 0;

}