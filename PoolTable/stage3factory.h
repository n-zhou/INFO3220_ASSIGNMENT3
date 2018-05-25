#ifndef STAGE3FACTORY_H
#define STAGE3FACTORY_H

#include "abstractfactory.h"
#include "ball.h"

class Stage3Factory : public AbstractFactory
{
public:
    Stage3Factory();

    Ball* makeBall(const QJsonObject &config);

    Table* makeTable(const QJsonObject &config);

private:
    /**
     * @brief makeBallBasedOnParent creates a ball with defaults and bounds based upon the parent
     * @param config
     * @param parent is the parent ball, if it is null then it is a base ball
     * @return a pointer to a ball
     */
    Ball *makeBallBasedOnParent(const QJsonObject &config, Ball* parent = nullptr) const;

    QVector2D m_tableDimensions;
};

#endif // STAGE3FACTORY_H
