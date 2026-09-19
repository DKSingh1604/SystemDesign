#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//DS for payment details
struct PaymentRequest {
    string sender;
    string receiver;
    double amount;
    string currency;

    PaymentRequest(const string& sender, const string& receiver, double amt, const string& currency){
        this->sender = sender;
        this->receiver = receiver;
        this->amount = amt;
        this->currency = currency;
    }
};

//BANKING SYSTME INTERFACE and Implementations
class BankingSystem {
public:
    virtual bool processPayment(double amount) = 0;
    virtual ~BankingSystem(){}
};

class PaytmBankingSystem : public BankingSystem {
public:
    PaytmBankingSystem(){}
    bool processPayment(double amount)override {
        //Simulate 20% success
        int r = rand() % 100;
        return r < 20;
    }
};

class RazorpayBankingSystem : public BankingSystem {
public:
    RazorpayBankingSystem(){}
    bool processPayment(double amount) override {
        //Simulate 90% success
        int r = rand() % 100;
        return r < 90;
    }
};

//Abstract Base class for Payment Gateway
class PaymentGateway {
protected:
    BankingSystem* bankingSystem;
public:
    PaymentGateway(){
        bankingSystem = NULL;
    }
    virtual ~PaymentGateway(){
        delete bankingSystem;
    }

    //Template method defining the standard payment flow
    virtual bool processPayment(PaymentRequest* request){
        if(!validatePayment(request)){
            cout<<"[PaymentGateway] Validation failed for "<<request->sender<<endl;
            return false;
        }

        if(!initiatePayment(request)){
            cout<<"[PaymentGateway] Initiattion failed for "<<request->sender<<endl;
            return false;
        }

        if(!confirmPayment(request)){
            cout<<"[PaymentGateway] Confirmation failed for "<<request->sender<<endl;
            return false;
        }
        
        return true;
    }

    //Steps to be implemented by concrete classes
    virtual bool validatePayment(PaymentRequest* request) = 0;
    virtual bool initiatePayment(PaymentRequest* request) = 0;
    virtual bool confirmPayment(PaymentRequest* request) = 0;
};

//Concrete Paytm Gatreway
class PaytmGateway : public PaymentGateway {
public:
    PaytmGateway(){
        bankingSystem = new PaytmBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout<<"[Paytm] Validating payment for "<<request->sender<<endl;

        if(request->amount <= 0 || request->currency != "INR"){
            return false;
        }
        return true;
    }

    bool initiatePayment(PaymentRequest* request) override {
        cout<<"[Paytm] Initiating payment of "<<request->sender<<endl;
        return bankingSystem->processPayment(request->amount);
    }

    bool confirmPayment(PaymentRequest* request) override {
        cout<<"[Paytm] Confirming payment of "<<request->sender<<endl;
        return true;
    }
};

class RazorpayGateway : public PaymentGateway {
public:
    RazorpayGateway(){
        bankingSystem = new RazorpayBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout<<"[RZP] Validating payment for "<<request->sender<<endl;

        if(request->amount <= 0){
            return false;
        }
        return true;
    }

    bool initiatePayment(PaymentRequest* request) override {
        cout<<"[RZP] Initiating payment of "<<request->sender<<endl;
        return bankingSystem->processPayment(request->amount);
    }

    bool confirmPayment(PaymentRequest* request) override {
        cout<<"[RZP] Confirming payment of "<<request->sender<<endl;
        return true;
    }
};

//PROXY CLASS
class PaymentGatewayProxy : public PaymentGateway {
    PaymentGateway* realGateway;
    int retries;

public:
    PaymentGatewayProxy(PaymentGateway* gateway, int maxRetries){
        realGateway = gateway;
        retries = maxRetries;
    }
    ~PaymentGatewayProxy(){
        delete realGateway;
    }

    // bool processPayment()
};

