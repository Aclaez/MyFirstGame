// Shoot Them Up Game, All Rights Reserved.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TEST)

#include "Tests/STUHealthComponentTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Components/STUHealthComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FComponentCouldBeCreated, "STUGame.Components.Health.ComponentCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthShouldBeZeroByDefault, "STUGame.Components.Health.HealthShouldBeZeroByDefault",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthShouldNotBeAddedToDead, "STUGame.Components.Health.HealthShouldNotBeAddedToDead",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

bool FComponentCouldBeCreated::RunTest(const FString& Parameters)
{
    const USTUHealthComponent* HealthComp = NewObject<USTUHealthComponent>();
    if (!TestNotNull("Health component exists", HealthComp)) return false;
    return true;
}

bool FHealthShouldBeZeroByDefault::RunTest(const FString& Parameters)
{
    const USTUHealthComponent* HealthComp = NewObject<USTUHealthComponent>();
    if (!TestNotNull("Health component exists", HealthComp)) return false;

    TestTrueExpr(HealthComp->GetHealth() == 0.0f);
    TestTrueExpr(HealthComp->GetHealthPercent() == 0.0f);

    return true;
}

bool FHealthShouldNotBeAddedToDead::RunTest(const FString& Parameters)
{
    USTUHealthComponent* HealthComp = NewObject<USTUHealthComponent>();
    if (!TestNotNull("Health component exists", HealthComp)) return false;

    const auto TestTryToAddHealthByCount = [this](USTUHealthComponent* HealthComponent, const float Adding, const float Count)
    {
        HealthComponent->TryToAddHealth(Adding);
        TestTrueExpr(FMath::IsNearlyEqual(HealthComponent->GetHealth(), Count));
        TestTrueExpr(FMath::IsNearlyEqual(HealthComponent->GetHealthPercent(), Count));
    };

    TestTrueExpr(HealthComp->IsDead());

    TestTryToAddHealthByCount(HealthComp, 0.0f, 0.0f);
    TestTryToAddHealthByCount(HealthComp, -1000.0f, 0.0f);
    TestTryToAddHealthByCount(HealthComp, 30.0f, 0.0f);

    return true;
}

#endif