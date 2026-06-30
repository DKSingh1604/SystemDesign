#pragma once
#include <iostream>
#include "../strategies/SequentialPlayStrategy.hpp"
#include "../strategies/CustomQueueStrategy.hpp"
#include "../strategies/RandomPlayStrategy.hpp"
#include "../enums/PlayStartegy.hpp"
using namespace std;

class StrategyManager {
private:
    static StrategyManager* instance;
    SequentialPlayStrategy* sequentialStrategy;
    RandomPlayStrategy* randomStrategy;
    CustomQueueStrategy* customStrategy;

    StrategyManager(){
        sequentialStrategy = new SequentialPlayStrategy();
        randomStrategy = new RandomPlayStrategy();
        customStrategy = new CustomQueueStrategy();
    }
public:
    static StrategyManager* getInstance(){
        if(!instance){
            instance = new StrategyManager();
        }
        return instance;
    }
    PlayStrategy* getStrategy(PlayStartegyType type){
        if(type == PlayStartegyType::SEQUENTIAL){
            return sequentialStrategy;
        }
        else if(type == PlayStartegyType::RANDOM){
            return randomStrategy;
        }
        else {
            return customStrategy;
        }
    }
};
StrategyManager* StrategyManager::instance = NULL;