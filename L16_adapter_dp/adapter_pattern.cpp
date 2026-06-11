#include <iostream>
using namespace std;

class IReports {
public:
    virtual string getJsonData(const string& data) = 0;
    virtual ~IReports(){}
};

class XmlDataProvider {
public:
    string getXmlData(const string& data){
        return "This is the XML data format.";
    }
};

class XmlDataProviderAdapter : public IReports {
private:
    XmlDataProvider* xmlProvider;
public:
    XmlDataProviderAdapter(XmlDataProvider* provider){
        this->xmlProvider = provider;
    }

    string getJsonData (const string& data) override {
        string xml = xmlProvider->getXmlData(data);

        return "This is your required Json Data.";
    }
};

class Client {
public:
    void getReport(IReports* report, string rawData){
        cout<<"Processed Json is:"<<endl<<report->getJsonData(rawData)<<endl;
    }
};

int main (){
    //New Adaptee
    XmlDataProvider* xmlProv = new XmlDataProvider();

    IReports* adapter = new XmlDataProviderAdapter(xmlProv);

    string rawData = "Alice:42";

    Client* client = new Client();
    client->getReport(adapter, rawData);

    delete adapter;
    delete xmlProv;
    return 0;
}