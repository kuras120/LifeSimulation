

#ifndef LIFESIMULATION_IHUMAN_H
#define LIFESIMULATION_IHUMAN_H
class IHuman {
public:
    virtual int getSaturation() = 0;
    virtual void setSaturation(int level) = 0;
    virtual int getFatigue() = 0;
    virtual void setFatigue(int level) = 0;
    virtual std::pair<int, int> getPossition() = 0;

    virtual void stop() = 0;
    virtual std::string getName() = 0;
    virtual std::thread spawnThread() = 0;

};
#endif //LIFESIMULATION_IHUMAN_H
