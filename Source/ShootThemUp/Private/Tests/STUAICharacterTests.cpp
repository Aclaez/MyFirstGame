// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUAICharacterTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "AI/STUAICharacter.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include <Components/WidgetComponent.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAICharacterCouldBeCreated, "STUGame.Player.AICharacter.AICharacterCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAICharacterHealthShouldBeSetupCorrectly,
    "STUGame.Player.AICharacter.AICharacterHealthShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

namespace
{
constexpr char* AICharacterBPName = "Blueprint'/Game/AI/BP_STUAICharacter.BP_STUAICharacter'";
}

bool FAICharacterCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* AIBlueprint = LoadObject<UBlueprint>(nullptr, *FString(AICharacterBPName));
    if (!TestNotNull("AIBlueprint exists", AIBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUAICharacter* AIPlayer = TestWorld->SpawnActor<ASTUAICharacter>(AIBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("AIPlayer exists", AIPlayer)) return false;

    return true;
}

bool FAICharacterHealthShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* AIBlueprint = LoadObject<UBlueprint>(nullptr, *FString(AICharacterBPName));
    if (!TestNotNull("AIBlueprint exists", AIBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUAICharacter* AIPlayer = TestWorld->SpawnActor<ASTUAICharacter>(AIBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("AIPlayer exists", AIPlayer)) return false;

    const auto HealthWidgetComp = AIPlayer->FindComponentByClass<UWidgetComponent>();
    if (!TestNotNull("Health widget component exists", HealthWidgetComp)) return false;

    TestTrueExpr(HealthWidgetComp->GetWidgetSpace() == EWidgetSpace::Screen);
    TestTrueExpr(HealthWidgetComp->GetDrawAtDesiredSize());

    return true;
}

#endif