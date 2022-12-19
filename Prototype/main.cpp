#include <iostream>
#include <map>
#include <memory>

enum class RobotType
{
    NONE = 0, ATTACK = 1, DEFENSE = 2, SUPPORT = 3
};

struct Robot
{
    int serialNumber = 0;
    RobotType type = RobotType::NONE;

    Robot() = default;

    Robot(int serialNumber, RobotType type) : serialNumber(serialNumber),
                                              type(type) {}

    Robot(RobotType type) : type(type) {}

    Robot(const Robot &rhs) : Robot{rhs.serialNumber, rhs.type} {}

    friend std::ostream &operator<<(std::ostream &os, const Robot &robot)
    {
        os << "serialNumber: " << robot.serialNumber << " type: " << static_cast<int>(robot.type);
        return os;
    }
};

struct RobotFactory
{
    RobotFactory()
    {
        robotTypes[RobotType::NONE] = std::make_unique<Robot>(RobotType::NONE);
        robotTypes[RobotType::ATTACK] = std::make_unique<Robot>(RobotType::ATTACK);
        robotTypes[RobotType::DEFENSE] = std::make_unique<Robot>(RobotType::DEFENSE);
        robotTypes[RobotType::SUPPORT] = std::make_unique<Robot>(RobotType::SUPPORT);
    }

    std::unique_ptr<Robot> create(RobotType rt)
    {
        auto robot = *robotTypes[rt];
        robot.serialNumber = serialNumber++;

        return std::make_unique<Robot>(*robotTypes[rt]);
    }

    std::unique_ptr<Robot> prototype()
    {
        auto prot = *robotTypes[RobotType::NONE];
        prot.serialNumber = serialNumber++;

        /**
         * implementation for any kind of replacement for the robot prototype
         */

        return std::make_unique<Robot>(prot);
    }

private:
    int serialNumber = 0;
    std::map<RobotType, std::unique_ptr<Robot>> robotTypes;
};

int main()
{
    RobotFactory rf;
    auto robot = rf.create(RobotType::ATTACK);
    auto prototype = rf.prototype();

    std::cout << *robot << std::endl << *prototype;

    return 0;
}