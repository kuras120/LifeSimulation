//
// Created by wojtek on 17.06.18.
//

#ifndef LIFESIMULATION_IHUMAN_H
#define LIFESIMULATION_IHUMAN_H
class IHuman {
public:
    virtual int getSaturation() = 0;
    virtual void setSaturation(int level) = 0;
    virtual int getFatigue() = 0;
    virtual void setFatigue(int level) = 0;
    virtual std::pair<int, int> GetPossition() = 0;

};
#endif //LIFESIMULATION_IHUMAN_H
