#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
using namespace std;

//Base interface for files and folders
class FileSystemItem {
public:
    virtual ~FileSystemItem(){}
    virtual void ls(int indent = 0) = 0;
    virtual void openAll(int indent = 0) = 0;
    virtual int getSize() = 0;
    virtual FileSystemItem* cd(const string& name) = 0;
    virtual string getName() = 0;
    virtual bool isFolder() = 0;
};

//Leaf: File
class File : public FileSystemItem {
    string name;
    int size;
public:
    File(const string& n, int s){
        name = n;
        size = s;
    }

    void ls(int indent = 0) override {
        cout<< string(indent, ' ')<<name<<endl;
    }

    void openAll(int indent = 0) override {
        cout<< string(indent, ' ')<<name<<endl;
    }

    int getSize() override {
        return size;
    }

    FileSystemItem* cd(const string&) override {
        return NULL;
    }

    string getName() override {
        return name;
    }
    
    bool isFolder() override {
        return false;
    }
};

//Root - Folder
class Folder : public FileSystemItem {
    string name;
    vector<FileSystemItem*> children;
public:
    Folder(const string& n){
        name = n;
    }
    ~Folder(){
        for(auto c : children) delete c;
    }

    void add(FileSystemItem* item){
        children.push_back(item);
    }

    void ls(int indent = 0) override {

        for(auto child : children){
            if(child->isFolder()){
                cout<<string(indent, ' ')<<"+ "<<child->getName()<<endl;
            }
            else{
                cout<<string(indent, ' ')<<child->getName()<<endl;
            }
        }
    }

    void openAll(int indent = 0) override {
        cout<<string(indent, ' ')<<"+ "<<name<<endl;
        for(auto child : children){
            child->openAll(indent + 4);
        }
    }

    int getSize()override{
        int total = 0;
        for(auto child : children){
            total += child->getSize();
        }
        return total;
    }

    FileSystemItem* cd(const string& target) override {
        for(auto child : children){
            if(child->isFolder() && child->getName() == target){
                return child;
            }
        }
        //not found or not a folder
        return NULL;
    }

    string getName() override {
        return name;
    }

    bool isFolder() override {
        return true;
    }
};

int main () {
    //Build file system
    Folder* root = new Folder("root");
    root->add(new File("File1.txt", 1));
    root->add(new File("File2.txt", 1));
    
    Folder* docs = new Folder("docs");
    docs->add(new File("Resume.pdf", 1));
    docs->add(new File("Notes.txt", 1));
    root->add(docs);

    Folder* images = new Folder("images");
    images->add(new File("photo.png", 1));
    root->add(images);

    // root->openAll();
    // root->ls();
    // docs->ls();

    // FileSystemItem* cwd = root->cd("docs");
    // if(cwd != NULL){
    //     cwd->ls();
    // }
    // else{
    //     cout<<endl<<"Could not cd into the docs!"<<endl;
    // }

    cout<<root->getSize();


    delete root;
    return 0;
}