#ifndef STAGE3FACTORY_H
#define STAGE3FACTORY_H

#include "abstractfactory.h"
#include "ball.h"

/**
 * @brief The Stage3Factory class does exactly the same thing as Stage2Factory
 * except it doesn't apply the decorators. The decorators are a hinderence
 * to serialization which it them unideal for networking.
 * @author Nic Zhou
 * @since Stage3
 * @see Stage2Factory
 */
class Stage3Factory : public AbstractFactory
{
public:
    Stage3Factory();

    /**
     * @brief makes and returns a stageOneBall
     * @param config is the configuration for the ball in json format
     * @return a pointer to a valid stage2Ball
     */
    Ball* makeBall(const QJsonObject &config);

    /**
     * @brief makes and returns a stageOneTable
     * @param config is the configuration for the table in json format
     * @return a pointer to a valid stage2Table
     */
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
