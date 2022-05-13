#include "Layer.hpp"

Layer::Layer(char c, double lsize) : size(lsize)
{
    if (c == 'x')
    {
        name = oxigen;
    }
    else if (c == 's')
    {
        name = dioxid;
    }
    else if (c == 'z')
    {
        name = ozon;
    }
    else
    {
        throw std::invalid_argument("No matter exits with that name in the atmosphere!");
    }
}

std::string Layer::toString() const
{
    std::string matName;
    switch (name)
    {
    case oxigen:
        matName = "oxigen";
        break;
    case dioxid:
        matName = "carbondioxid";
        break;
    case ozon:
        matName = "ozon";
        break;
    default:
        throw std::invalid_argument("No layer name found!");
        break;
    }
    matName = matName + " " + std::to_string(getSize()).substr(0, 6);
    return matName;
}