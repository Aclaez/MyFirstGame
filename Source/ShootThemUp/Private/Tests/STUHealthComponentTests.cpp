// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUHealthComponentTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Components/STUHealthComponent.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include "STUPlayerCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthComponentCouldBeCreated, "STUGame.Components.Health.HealthComponentCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthShouldBeZeroByDefault, "STUGame.Components.Health.HealthShouldBeZeroByDefault",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthShouldNotBeAddedToDead, "STUGame.Components.Health.HealthShouldNotBeAddedToDead",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthShouldBeAddedToAlive, "STUGame.Components.Health.HealthShouldBeAddedToAlive",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

bool FHealthComponentCouldBeCreated::RunTest(const FString& Parameters)
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
    };

    TestTrueExpr(HealthComp->IsDead());

    TestTryToAddHealthByCount(HealthComp, 0.0f, 0.0f);
    TestTryToAddHealthByCount(HealthComp, -1000.0f, 0.0f);
    TestTryToAddHealthByCount(HealthComp, 30.0f, 0.0f);

    return true;
}

using namespace STU::Tests;

bool FHealthShouldBeAddedToAlive::RunTest(const FString& Parameters)
{
    LevelScope("/Game/Levels/TestLevel");

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUPlayerCharacter* TestPlayer = CreateBlueprint<ASTUPlayerCharacter>(TestWorld, FString(PlayerBPName), InitialTranform);
    if (!TestNotNull("Player exists", TestPlayer)) return false;

    USTUHealthComponent* HealthComponent = TestPlayer->FindComponentByClass<USTUHealthComponent>();
    if (!TestNotNull("Health component exists", HealthComponent)) return false;

    const auto TestTryToAddHealthByCount = [this](USTUHealthComponent* Component, const float Adding, const float Count)
    {
        Component->TryToAddHealth(Adding);
        TestTrueExpr(FMath::IsNearlyEqual(Component->GetHealth(), Count));
    };

    TestTrueExpr(HealthComponent->IsHealthFull());

    TestTryToAddHealthByCount(HealthComponent, 0.0f, 100.0f);
    TestTryToAddHealthByCount(HealthComponent, 1000.0f, 100.0f);
    TestTryToAddHealthByCount(HealthComponent, -1000.0f, 100.0f);

    return true;
}

#endif