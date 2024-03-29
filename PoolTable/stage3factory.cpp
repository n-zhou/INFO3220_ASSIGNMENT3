#include "stage3factory.h"

#include <iostream>
#include <cmath>
#include <QJsonArray>

#include "stage2ball.h"
#include "stage2table.h"
#include "util.h"

Stage3Factory::Stage3Factory()
{

}

void setIntrinsicBallPropertiesS3(const QJsonObject &config, Stage2Ball * ball, Ball* parent)
{
    ball->setVelocity(QJsonValueToVector2D(config["velocity"]));
    ball->setRadius(config["radius"].toDouble(10));
    ball->setPosition(QJsonValueToVector2D(config["position"],0,0));
    ball->setMass(config["mass"].toDouble(1.0));
    if(parent)
    {
        QString colour = config["colour"].toString();
        if(colour == QString())
        {
            ball->setColour(parent->colour());
        }
        else
        {
            ball->setColour(QColor(colour));
        }
    }
    else
    {
        ball->setColour(config["colour"].toString("white"));
    }
    ball->setStrength(config["strength"].toDouble(std::numeric_limits<double>::infinity()));
}


Ball* Stage3Factory::makeBallBasedOnParent(const QJsonObject &config, Ball* parent) const
{
    QJsonArray balls = config["balls"].toArray();
    Ball * ball;
    if(balls.size()==0)
    {
        //construct a simple stage 2 ball
        SimpleStage2Ball *simpleBall = new SimpleStage2Ball();
        setIntrinsicBallPropertiesS3(config, simpleBall,parent);
        ball = simpleBall;
    }
    else
    {
        //construct a composite ball
        CompositeBall * compositeBall = new CompositeBall();
        setIntrinsicBallPropertiesS3(config, compositeBall,parent);
        for(int i = 0; i < balls.size();++i)
        {
            Ball * newBall = makeBallBasedOnParent(balls[i].toObject(),compositeBall);
            if(newBall)
                compositeBall->addBall(newBall);
        }
        ball = compositeBall;
    }

    //check that the ball is within bounds
    if(parent)
    {
        if(ball->position().length()+ball->radius()-1.0f > parent->radius())
        {
            std::cout << "ball is not contained by parent" <<std::endl;
            delete ball;
            return nullptr;
        }
    }
    else
    {
        //check to make sure the ball is off the table at all
        if((ball->position().x()<ball->radius()) || (ball->position().x()>m_tableDimensions.x()-ball->radius()) ||
                ball->position().y()<ball->radius() || (ball->position().y()>m_tableDimensions.y()-ball->radius()))
        {
            std::cout << "ball is not contained by table" <<std::endl;
            delete ball;
            return nullptr;
        }
    }
    return ball;
}

Ball* Stage3Factory::makeBall(const QJsonObject &config)
{
    return makeBallBasedOnParent(config);
}

Table* Stage3Factory::makeTable(const QJsonObject &config)
{
    //copied from stage2factory::makeTable()
    QVector2D dimensions = QJsonValueToVector2D(config["size"],300,600);
    m_tableDimensions = dimensions;
    float friction = config["friction"].toDouble(0.01);
    QColor colour = QColor(config["colour"].toString("green"));

    QJsonArray pockets = config["pockets"].toArray();
    std::vector<Pocket*> pocketVector;
    for(int i = 0; i < pockets.size();++i)
    {
        QVector2D pos = QJsonValueToVector2D(pockets[i].toObject()["position"],nan(""),nan(""));
        if(std::isnan(pos.x())||std::isnan(pos.y()))
        {
            std::cout << "pocket must have both an x and y position" <<std::endl;
            continue;
        }
        float r = pockets[i].toObject()["radius"].toDouble(15);
        if(!circleRectangleIntersection(pos,r,dimensions/2,dimensions))
        {
            std::cout << "pocket must intersect with table" <<std::endl;
            continue;
        }
        pocketVector.push_back(new Pocket(pos,r));
    }

    return new Stage2Table(dimensions.x(),dimensions.y(),friction,colour,pocketVector);
}
