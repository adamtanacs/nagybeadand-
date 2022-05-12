#if !defined(READER_HPP)
#define READER_HPP
#include <iostream>
#include <math.h>
#include <vector>
#include <exception>

enum Matter
{
    ozon,
    oxigen,
    dioxid
};

class Layer
{
private:
    Matter name;
    double size;

public:
    Layer(char c, double lsize) : size(lsize)
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

    Matter getName() const { return name; }

    double getSize() const { return size; }
    void setSize(const double size) { this->size = size; }

    std::string toString() const
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
        matName = matName + " " + std::to_string(getSize()).substr(0, log10(100000) + 1);
        return matName;
    }
};

class Atmosphere
{
private:
    std::vector<Layer> layers;

    void clearThins()
    {
        for (unsigned int i = 0; i < layers.size(); i++)
        {
            if (layers[i].getSize() < 0.5)
            {
                upLayer(layers[i], i);
                layers.erase(layers.begin() + i);
            }
        }
    }

    void print(const char weather, const unsigned int it)
    {
        std::string weatherString;
        switch (weather)
        {
        case 'z':
            weatherString = "Zivatar";
            break;

        case 'n':
            weatherString = "Napos";
            break;

        case 'm':
            weatherString = "Mas";
            break;

        default:
            break;
        }
        std::cout << "------------OUTPUT" << it << "------------" << weatherString << std::endl;
        for (unsigned int i = 0; i < layers.size(); i++)
        {
            std::cout << layers[i].toString() << std::endl;
        }
        std::cout << "------------------------------" << std::endl;
    }

public:
    Atmosphere(int size)
    {
        for (int i = 0; i < size; i++)
        {
            char c;
            double lsize;
            std::cin >> c >> lsize;
            Layer tmp(c, lsize);
            layers.push_back(tmp);
        }
    }

    bool createLayer(const Layer input, const unsigned int index)
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

    void upLayer(const Layer input, const unsigned int index)
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

    bool allElementsExits() const
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

    void simulate(const std::string weather)
    {
        // unsigned int i = 0;
        // unsigned int iteration = 1;
        for (unsigned int i = 0; i < weather.size(); i++)
        // while (allElementsExits())
        {
            switch (weather[i])
            {
            case 'z': // zivatar
                std::cout << "------ZIVATAR------" << std::endl;
                for (unsigned int i = 0; i < layers.size(); i++)
                {
                    if (layers[i].getName() == oxigen)
                    {
                        double tmp = layers[i].getSize() * 0.5; // 50% ozon
                        std::cout << "- " << tmp << " oxigen"
                                  << " >> " << tmp << " ozon" << std::endl;
                        layers[i].setSize(layers[i].getSize() - tmp);
                        Layer newLayer('z', tmp);
                        bool created = createLayer(newLayer, i);
                        if (created)
                            i++;
                    }
                }
                std::cout << "-------------------" << std::endl;
                break;
            case 'n': // napos
                std::cout << "------NAPOS------" << std::endl;
                for (unsigned int i = 0; i < layers.size(); i++)
                {
                    if (layers[i].getName() == oxigen)
                    {
                        double tmp = layers[i].getSize() * 0.05; // 5% ozon
                        std::cout << "- " << tmp << " oxigen"
                                  << " >> " << tmp << " ozon" << std::endl;
                        layers[i].setSize(layers[i].getSize() - tmp);
                        Layer newLayer('z', tmp);
                        bool created = createLayer(newLayer, i);
                        if (created)
                            i++;
                    }
                    if (layers[i].getName() == dioxid)
                    {
                        double tmp = layers[i].getSize() * 0.05; // 5% oxigen
                        std::cout << "- " << tmp << " carbondioxid"
                                  << " >> " << tmp << " oxigen" << std::endl;
                        layers[i].setSize(layers[i].getSize() - tmp);
                        Layer newLayer('x', tmp);
                        bool created = createLayer(newLayer, i);
                        if (created)
                            i++;
                    }
                }
                std::cout << "-----------------" << std::endl;
                break;
            case 'm': // mas
                std::cout << "------MAS------" << std::endl;
                for (unsigned int i = 0; i < layers.size(); i++)
                {
                    if (layers[i].getName() == ozon)
                    {
                        double tmp = layers[i].getSize() * 0.05; // 5% oxigen
                        std::cout << "- " << tmp << " ozon"
                                  << " >> " << tmp << " oxigen" << std::endl;
                        layers[i].setSize(layers[i].getSize() - tmp);
                        Layer newLayer('x', tmp);
                        bool created = createLayer(newLayer, i);
                        if (created)
                            i++;
                    }
                    if (layers[i].getName() == oxigen)
                    {
                        double tmp = layers[i].getSize() * 0.1; // 10% dioxid
                        std::cout << "- " << tmp << " oxigen"
                                  << " >> " << tmp << " carbondioxid" << std::endl;
                        layers[i].setSize(layers[i].getSize() - tmp);
                        Layer newLayer('s', tmp);
                        bool created = createLayer(newLayer, i);
                        if (created)
                            i++;
                    }
                }
                std::cout << "---------------" << std::endl;
                break;

            default:
                throw std::invalid_argument("No weather like this found!");
                break;
            }
            clearThins();
            // print(weather[i],iteration);
            // i++;iteration++;
            // if(i >= weather.size())
            //     i = 0;
        }

        // print(weather[i],iteration);
        // i++;iteration++;
        // if(i >= weather.size())
        //     i = 0;
    }

    void print(const unsigned int it)
    {
        std::cout << "------------OUTPUT" << it << "------------" << std::endl;
        for (unsigned int i = 0; i < layers.size(); i++)
        {
            std::cout << layers[i].toString() << std::endl;
        }
        std::cout << "-------------------------------" << std::endl;
    }

    int getSize() { return layers.size(); }
};

#endif // READER_HPP