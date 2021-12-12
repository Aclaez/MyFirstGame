// Shoot Them Up Game, All Rights Reserved.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TEST)

#include "STUWeaponComponentTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUPlayerCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWeaponComponentCouldBeCreated, "STUGame.Components.Weapon.WeaponComponentCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

namespace
{
class LevelScope
{
public:
    LevelScope(const FString& MapName) { AutomationOpenMap(MapName); }
    ~LevelScope() { ADD_LATENT_AUTOMATION_COMMAND(FExitGameCommand); }
};
}  // namespace

bool FWeaponComponentCouldBeCreated::RunTest(const FString& Parameters)
{
    AutomationOpenMap("/Game/Levels/TestLevel");
    return true;
}

#endif
