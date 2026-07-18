
#include <iostream>
#include <string>
using namespace std;

//BASE Class defining the template method
class ModelTrainer {
public:
    void trainPipeline(const string& dataPath){
        loadData(dataPath);
        preprocessData();
        trainModel(); //subclass specific
        evaluateModel(); //subclass specific
        saveModel();
    }
protected:
    void loadData(const string& path){
        cout<<"[Common] Loading dataset from "<<path<<" ...."<<endl;
        //eg - csv, images etc.
    }

    virtual void preprocessData(){
        cout<<"[Common] Splitting into train/test and norimalizing...."<<endl;

    }

    virtual void trainModel() = 0;
    virtual void evaluateModel() = 0;

    //Providing a default save
    virtual void saveModel(){
        cout<<"[Common] Saving model to the disk as default format."<<endl;
    }
};

//CONCRETE SUBCLASS 1: NEURAL NETWORK
class NeuralNetworkTrainer : public ModelTrainer{
protected:
    void trainModel() override {
        cout<<"[NeuralNet] Training Neural Network for 100 epochs"<<endl;
        //pseudocode: forward/backward passes, gradient descent
    }

    void evaluateModel() override {
        cout<<"[NeuralNet] Evaluating accuracy and loss on validation set....."<<endl;
    }

    void saveModel() override {
        cout<<"[Neuralnet] Serializing network weights to .h5 file...."<<endl;
    }
};

//CONCRETE SUBCLASS 2: DECISION TREE
class DecisionTreeTrainer : public ModelTrainer {
protected:
    //Use the default preprocessData() (train/test split + normalize)

    void trainModel() override {
        cout<<"[DecisionTree] Building decision tree with max_depth=5 ......"<<endl;
    }

    void evaluateModel() override {
        cout<<"[DecisionTree] Computing classification report (precision/recall) ....."<<endl;
    }

    //use default save model()
};

//USAGE
int main(){
    cout<<"====NEURAL NETWORK TRAINING===="<<endl;
    ModelTrainer* nnTrainer = new NeuralNetworkTrainer();
    nnTrainer->trainPipeline("data/images");
    cout<<endl;
    cout<<"==== DECISION TREE TRAINING ===="<<endl;
    ModelTrainer* dtTrainer = new DecisionTreeTrainer();
    dtTrainer->trainPipeline("data/iris.csv");

    return 0;
}