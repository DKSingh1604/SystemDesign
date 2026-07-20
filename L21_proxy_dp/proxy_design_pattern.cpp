#include <iostream>
using namespace std;

// ------------------- VIRTUAL PROXY --------------------

// class IImage {
// public:
//     virtual void display() = 0;
//     virtual ~IImage() = default;
// };

// class RealImage : public IImage{
//     string fileName;
// public:
//     RealImage(string file){
//         this->fileName = file;
//         //Heavy Operation
//         cout<<"[RealImage] Loading image from disk: "<<fileName<<endl;
//     }

//     void display() override {
//         cout<<"[RealImage] Displaying "<<fileName<<endl;
//     }
// };

// class ImageProxy : public IImage {
//     RealImage* realImage;
//     string fileName;
// public:
//     ImageProxy(string file){
//         this->fileName = file;
//         realImage = NULL;
//     }

//     void display() override {
//         //Lazy initialization of RealImage
//         if(!realImage) {
//             realImage = new RealImage(fileName);
//         }
//         realImage->display();
//     }
// };

// int main(){
//     IImage* image1 = new ImageProxy("sample/image.png");
//     image1->display();
// }




//----------------REMOTE PROXY-------------------------
class IWeatherService {
public:
    virtual string getWeather(string city) = 0;
    virtual ~IWeatherService(){}
};

//Actual Weather Service
class RealWeatherService : public IWeatherService {
public:
    string getWeather(string city) override {
        return "The weather is 25°C, cloudy here!";
    }
};

//Proxy class
class WeatherProxy : public IWeatherService {
public:
    string getWeather(string city) override {
        cout<<"Connection to the servers....."<<endl;
        cout<<"Sending HTTP request for: "<<city<<endl;

        string response = fetchFromServer(city);
        cout<<"Received response!"<<endl;
        return response;
    }

private:
    string fetchFromServer(string city){
        return "22°C, It's cold here in "+ city + ".";
    }
};

int main(){
    IWeatherService* weather = new WeatherProxy();
    string result = weather->getWeather("Hyderabad");
    cout<<"Weather: "<<result<<endl;
}