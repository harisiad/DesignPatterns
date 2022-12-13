#include <iostream>
#include <vector>

class BuildingPlan
{
    friend class BuildingPlanBuilder;
    std::vector<BuildingPlan> plans_;
    std::string planName_;
    float progress_ = 0.0f;
    float requiredDays_ = 0.0f;

    BuildingPlan() {}
    BuildingPlan(const std::string& planName, const float& requiredDays) : planName_(planName), requiredDays_(requiredDays) { }
public:
    void constructBuilding()
    {
        std::cout << "Starting construction\n";

        for (int i = 0; i < requiredDays_; i++) {
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
    BuildingPlan plan_;
public:
    BuildingPlanBuilder() {}

    BuildingPlanBuilder(std::string planName, float requiredDays)
    {
        plan_ = {planName, requiredDays};
    }

    BuildingPlanBuilder addMoreBuildingPlans(std::string planName, float requiredDays)
    {
        BuildingPlan plan {planName, requiredDays};
        plan_.plans_.push_back(plan);

        return *this;
    }

    static BuildingPlanBuilder create()
    {
        return {};
    }

    BuildingPlanBuilder build()
    {
        for (auto plan : plan_.plans_) {
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