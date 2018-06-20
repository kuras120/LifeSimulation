//
// Created by root on 6/20/18.
//

#include "ChessClub.h"

std::pair<int, int> ChessClub::getLocation() {
    return location_;
}

void ChessClub::start(std::shared_ptr<Human> human) {
    counter_ = std::make_shared<int>(0);
    human->goTo(location_.first+8, location_.second+1);
    human->goTo(location_.first+3, location_.second+1);
    logger_->info(human->getName() + " wchodzi do klubu szachowego");

    goToTable(human);

    human->setColor(WHITE);
    logger_->info(human->getName() + " wychodzi z klubu szachowego");
    human->goTo(location_.first+3, location_.second+1);
    human->goTo(location_.first+8, location_.second+1);
}

const std::pair<int, int> &ChessClub::getLocation_() const {
    return location_;
}

ChessClub::ChessClub(const std::shared_ptr<spdlog::logger> &logger_) : logger_(logger_) {
    auto tab1 = std::make_shared<Table>();
    tab1->position={location_.first+2, location_.second+3};
    tables.push_back(tab1);

    auto tab2 = std::make_shared<Table>();
    tab2->position={location_.first+2, location_.second+7};
    tables.push_back(tab2);

    auto tab3 = std::make_shared<Table>();
    tab3->position={location_.first+2, location_.second+11};
    tables.push_back(tab3);

    auto tab4 = std::make_shared<Table>();
    tab4->position={location_.first+2, location_.second+15};
    tables.push_back(tab4);

}

const std::vector<std::shared_ptr<Table>> &ChessClub::getTables() const {
    return tables;
}

void ChessClub::goToTable(std::shared_ptr<Human> human) {
    {
        mtx_.lock();
        if(lastTable!= nullptr) {
            logger_->info(human->getName() + " znalazl partnera do szach");

            human->setTarget(lastTable->position.first , lastTable->position.second-1);
            lastTable->available = false;
            (*counter_)++;
            human->setColor(GREEN);
            lastTable->available= true;
            auto &buff = lastTable;
            lastTable= nullptr;
            mtx_.unlock();


            human->goToTarget();
            (buff->conVar).notify_one();
            human->setColor(RED);

            (buff->conVar).notify_one();

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            buff->available= true;
            (buff->conVar).notify_one();
        } else {
            logger_->info(human->getName() + " nie znalazl partnera do szach");

            std::unique_lock<std::mutex> lockQueue(mtxQueue_);
            logger_->info(human->getName() + " nie znalazl partnera do szach1");
            while((*counter_)==4)
                conVar_.wait(lockQueue);
            logger_->info(human->getName() + " nie znalazl partnera do szach2");
            int i = -1;
            std::shared_ptr<Table> table;
            logger_->info(human->getName() + " nie znalazl partnera do szach3");
            do {
                i++;
                table=tables.at(i);
                logger_->info(human->getName() + " nie znalazl partnera do szachi");
            } while (!(tables.at(i)->available));
            lastTable=table;
            logger_->info(human->getName() + " nie znalazl partnera do szach4");

            std::unique_lock<std::mutex> lockTable(lastTable->mtx);

            logger_->info(human->getName() + " nie znalazl partnera do szach5");

            human->setTarget(lastTable->position.first, lastTable->position.second+1);
            logger_->info(human->getName() + " nie znalazl partnera do szach6");


            logger_->info(human->getName() + " nie znalazl partnera do szach7");

            human->goToTarget();

            mtx_.unlock();
            conVar_.notify_one();

            auto buff = lastTable;
            (buff->conVar).wait(lockQueue);
            human->setColor(RED);
            (buff->conVar).wait(lockQueue);

        }
    }
}
