#include "serverdisplay.h"

ServerDisplay::ServerDisplay(QWidget *parent) : QDialog(parent)
{

}

ServerDisplay::~ServerDisplay()
{

}

void ServerDisplay::runSimulationStep()
{
    m_game->simulateTimeStep(0.01);
}
