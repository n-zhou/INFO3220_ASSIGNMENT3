#ifndef STAGE3FACTORY_H
#define STAGE3FACTORY_H

#include "abstractfactory.h"

class Stage3Factory : public AbstractFactory
{
public:
    Stage3Factory();

    Ball* makeBall(const QJsonObject &config);

    Table* makeTable(const QJsonObject &config);
};

#endif // STAGE3FACTORY_H
