#include "Atmosphere.hpp"

#define DEBUGE_MODE

void Atmosphere::clearThins()
{
    for (int i = layers.size()-1; i >= 0; i--)
    {
        if (layers[i].getSize() < 0.5)
        {
            upLayer(layers[i], i);
            layers.erase(layers.begin() + i);
        }
    }
}

bool Atmosphere::createLayer(const Layer input, const unsigned int index)
{
    if (index != 0)
    {
        if (index > layers.size())
        {
            throw std::invalid_argument("Index out of bound for layers");
        }
        else if (layers[index - 1].getName() == input.getName())
        {
            layers[index - 1].setSize(layers[index - 1].getSize() + input.getSize());
            return false;
        }
        else
        {
            createLayer(input, index - 1);
        }
    }
    else
    {
        layers.insert(layers.begin(), input);
        return true;
    }
    return false;
}

void Atmosphere::upLayer(const Layer input, const unsigned int index)
{
    if (index != 0)
    {
        if (index > layers.size())
        {
            throw std::invalid_argument("Index out of bound for layers");
        }
        else if (layers[index - 1].getName() == input.getName())
        {
            layers[index - 1].setSize(layers[index - 1].getSize() + input.getSize());
        }
        else
        {
            upLayer(input, index - 1);
        }
    }
}

bool Atmosphere::allElementsExits() const
{
    bool ox, di, oz; // oxigen, dioxid, ozon
    ox = di = oz = false;
    for (unsigned int i = 0; i < layers.size(); i++)
    {
        if (layers[i].getName() == oxigen)
        {
            ox = true;
        }
        else if (layers[i].getName() == dioxid)
        {
            di = true;
        }
        else if (layers[i].getName() == ozon)
        {
            oz = true;
        }
    }
    return ox && di && oz;
}

void Atmosphere::simulate()
{
    // unsigned int i = 0;
    // unsigned int iteration = 1;
    for (unsigned int j = 0; j < weather.size(); j++)
    // while (allElementsExits())
    {
        switch (weather[j])
        {
        case 'z': // zivatar
            std::cout << "------ZIVATAR------" << std::endl;
            for (unsigned int i = 0; i < layers.size(); i++)
            {
                #ifdef DEBUGE_MODE 
                std::cout << i << std::endl;
                #endif
                if (layers[i].getName() == oxigen)
                {
                    double tmp = layers[i].getSize() * 0.5; // 50% ozon
                    std::cout << "- " << tmp << " oxigen"
                                << " >> " << tmp << " ozon" << std::endl;
                    layers[i].setSize(layers[i].getSize() - tmp);
                    Layer newLayer('z', tmp);
                    bool created = createLayer(newLayer, i);
                    #ifdef DEBUGE_MODE
                    if (created) {std::cout << "TRUE";} else {std::cout << "FALSE";}
                    #endif
                    if (created)
                        i+= 2;
                }
                #ifdef DEBUGE_MODE 
                std::cout << i << std::endl;
                #endif
            }
            std::cout << "-------------------" << std::endl;
            break;
        case 'n': // napos
            std::cout << "------NAPOS------" << std::endl;
            for (unsigned int i = 0; i < layers.size(); i++)
            {
                #ifdef DEBUGE_MODE 
                std::cout << i << std::endl;
                #endif
                if (layers[i].getName() == oxigen)
                {
                    double tmp = layers[i].getSize() * 0.05; // 5% ozon
                    std::cout << "- " << tmp << " oxigen"
                                << " >> " << tmp << " ozon" << std::endl;
                    layers[i].setSize(layers[i].getSize() - tmp);
                    Layer newLayer('z', tmp);
                    bool created = createLayer(newLayer, i);
                    #ifdef DEBUGE_MODE
                    if (created) {std::cout << "TRUE";} else {std::cout << "FALSE";}
                    #endif
                    if (created)
                        i += 2;
                }
                if (layers[i].getName() == dioxid)
                {
                    double tmp = layers[i].getSize() * 0.05; // 5% oxigen
                    std::cout << "- " << tmp << " carbondioxid"
                                << " >> " << tmp << " oxigen" << std::endl;
                    layers[i].setSize(layers[i].getSize() - tmp);
                    Layer newLayer('x', tmp);
                    bool created = createLayer(newLayer, i);
                    #ifdef DEBUGE_MODE
                    if (created) {std::cout << "TRUE";} else {std::cout << "FALSE";}
                    #endif
                    if (created)
                        i += 2;
                }
                #ifdef DEBUGE_MODE 
                std::cout << i << std::endl;
                #endif
            }
            std::cout << "-----------------" << std::endl;
            break;
        case 'm': // mas
            std::cout << "------MAS------" << std::endl;
            for (unsigned int i = 0; i < layers.size(); i++)
            {
                #ifdef DEBUGE_MODE 
                std::cout << i << std::endl;
                #endif
                if (layers[i].getName() == ozon)
                {
                    double tmp = layers[i].getSize() * 0.05; // 5% oxigen
                    std::cout << "- " << tmp << " ozon"
                                << " >> " << tmp << " oxigen" << std::endl;
                    layers[i].setSize(layers[i].getSize() - tmp);
                    Layer newLayer('x', tmp);
                    bool created = createLayer(newLayer, i);
                    #ifdef DEBUGE_MODE
                    if (created) {std::cout << "TRUE";} else {std::cout << "FALSE";}
                    #endif
                    if (created)
                        i += 2;
                }
                if (layers[i].getName() == oxigen)
                {
                    double tmp = layers[i].getSize() * 0.1; // 10% dioxid
                    std::cout << "- " << tmp << " oxigen"
                                << " >> " << tmp << " carbondioxid" << std::endl;
                    layers[i].setSize(layers[i].getSize() - tmp);
                    Layer newLayer('s', tmp);
                    bool created = createLayer(newLayer, i);
                    #ifdef DEBUGE_MODE
                    if (created) {std::cout << "TRUE" << std::endl;} else {std::cout << "FALSE" << std::endl;}
                    #endif
                    if (created)
                        i += 2;
                }
                #ifdef DEBUGE_MODE 
                std::cout << i << std::endl;
                #endif
            }
            std::cout << "---------------" << std::endl;
            break;

        default:
            throw std::invalid_argument("No weather like this found!");
            break;
        }
        for(unsigned int i = 0; i < layers.size();i++)
        {
            std::cout << "- " << layers[i].toString() << std::endl;
        }
        std::cout << "---------------" << std::endl;
        
        // print(weather[i],iteration);
        // i++;iteration++;
        // if(i >= weather.size())
        //     i = 0;
    }
    // sleep(1);
    clearThins();
    // print(weather[i],iteration);
    // i++;iteration++;
    // if(i >= weather.size())
    //     i = 0;
}

void Atmosphere::print(const unsigned int it)
{
    std::cout << "------------OUTPUT" << it << "------------" << std::endl;
    for (unsigned int i = 0; i < layers.size(); i++)
    {
        std::cout << layers[i].toString() << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}
