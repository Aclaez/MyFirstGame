// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STURespawnComponentTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Components/STURespawnComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRespawnComponentCouldBeCreated, "STUGame.Components.Respawn.RespawnComponentCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRespawnShouldNotWork, "STUGame.Components.Respawn.RespawnShouldNotWork",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

bool FRespawnComponentCouldBeCreated::RunTest(const FString& Parameters)
{
    const USTURespawnComponent* RespawnComp = NewObject<USTURespawnComponent>();
    if (!TestNotNull("Respawn component exists", RespawnComp)) return false;
    return true;
}

bool FRespawnShouldNotWork::RunTest(const FString& Parameters)
{
    const USTURespawnComponent* RespawnComp = NewObject<USTURespawnComponent>();
    if (!TestNotNull("Respawn component exists", RespawnComp)) return false;

    TestTrueExpr(!RespawnComp->IsRespawnInProgress());

    return true;
}

#endif