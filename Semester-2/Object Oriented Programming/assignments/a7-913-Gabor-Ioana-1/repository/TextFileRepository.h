//
// Created by ioana on 04.05.2023.
//

#ifndef A7_913_GABOR_IOANA_1_TEXTFILEREPOSITORY_H
#define A7_913_GABOR_IOANA_1_TEXTFILEREPOSITORY_H


#include "AbstractFileRepository.h"
#include "domain/Event.h"

template<class T>
class TextFileRepository : public AbstractFileRepository<T> {
public:
    explicit TextFileRepository(const std::string &fileName) : AbstractFileRepository<T>(fileName) {}

    void load() override;

    void save() override;
};

template<class T>
void TextFileRepository<T>::load() {
    std::ifstream fileReader(this->fileName);
    this->entities = std::vector<T>();
    T entity;
    while (fileReader >> entity) {
        if (entity == T()) {
            break;
        }
        this->entities.push_back(entity);
    }
    fileReader.close();
}

template<class T>
void TextFileRepository<T>::save() {
    std::ofstream fileWriter(this->fileName);
    for (auto &entity: this->entities) {
        fileWriter << entity << '\n';
    }
    fileWriter.close();
}


#endif //A7_913_GABOR_IOANA_1_TEXTFILEREPOSITORY_H
