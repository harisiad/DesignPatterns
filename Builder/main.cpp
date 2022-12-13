#include <iostream>
#include <utility>
#include <vector>

class BuildingPlan
{
    friend class BuildingPlanBuilder;
    std::string planName_;
    float progress_ = 0.0f;
    float requiredDays_ = 0.0f;

    BuildingPlan() = default;
    BuildingPlan(std::string planName, const float& requiredDays) : planName_(std::move(planName)), requiredDays_(requiredDays) { }
public:
    void constructBuilding()
    {
        std::cout << "Starting construction\n";

        for (int i = 0; i < (int)requiredDays_; i++) {
            /** complex process that would require building construction */
            progress_ += 100.0f / requiredDays_;
            if (progress_ < 100.0f) {
                std::cout << "[" << planName_ << "]" << " Construction day end, current progress: " << progress_ << std::endl;
            } else {
                std::cout << "Construction of " << planName_ << " finished\n";
            }
        }
    }
};

class BuildingPlanBuilder
{
    std::vector<BuildingPlan> plans_;
public:
    BuildingPlanBuilder() = default;

    BuildingPlanBuilder addMoreBuildingPlans(const std::string& planName, float requiredDays)
    {
        plans_.push_back({planName, requiredDays});

        return *this;
    }

    static BuildingPlanBuilder create()
    {
        return {};
    }

    BuildingPlanBuilder build()
    {
        for (auto plan : plans_) {
            plan.constructBuilding();
        }

        return *this;
    }
};

int main()
{
/**
 * Old implementation
 * Before closing the API of BuildingPlan from the user
*/
//    BuildingPlan smallHouse("Small House", 10);
//    BuildingPlan bigHouse("Big House", 20);
//
//    for (int i = 0; i < 10; i++) {
//        smallHouse.constructBuilding();
//    }
//
//    for (int i = 0; i < 20; i++) {
//        bigHouse.constructBuilding();
//    }

/*
 * New implementation with closed BuildingPlan API and using Builder
 */
auto builder = BuildingPlanBuilder::create()
        .addMoreBuildingPlans("Small House", 10)
        .addMoreBuildingPlans("Big House", 20)
        .addMoreBuildingPlans("Big Park", 4)
        .build();

    return 0;
}