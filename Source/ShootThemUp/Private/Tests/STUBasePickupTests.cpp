// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUBasePickupTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Pickups/STUBasePickup.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include "Components/SphereComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBasePickupCouldBeCreated, "STUGame.Pickups.Base.BasePickupCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPickupCollisionShouldBeSetupCorrectly, "STUGame.Pickups.Base.PickupCollisionShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBasePickupCouldBeTaken, "STUGame.Pickups.Base.BasePickupCouldBeTaken",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

namespace
{
constexpr char* BPName = "Blueprint'/Game/Pickups/BP_STUBasePickup.BP_STUBasePickup'";
}

bool FBasePickupCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUBasePickup* Pickup = TestWorld->SpawnActor<ASTUBasePickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    return true;
}

bool FPickupCollisionShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUBasePickup* Pickup = TestWorld->SpawnActor<ASTUBasePickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    const auto CollisionComp = Pickup->FindComponentByClass<USphereComponent>();
    if (!TestNotNull("CollisionComp exists", CollisionComp)) return false;

    TestTrueExpr(CollisionComp->GetUnscaledSphereRadius() >= 30.0f);
    TestTrueExpr(CollisionComp->GetCollisionEnabled() == ECollisionEnabled::QueryOnly);
    TestTrueExpr(CollisionComp->GetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic) == ECollisionResponse::ECR_Overlap);
    TestTrueExpr(CollisionComp->GetGenerateOverlapEvents());
    TestTrueExpr(Pickup->GetRootComponent() == CollisionComp);

    return true;
}

bool FBasePickupCouldBeTaken::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUBasePickup* Pickup = TestWorld->SpawnActor<ASTUBasePickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    TestTrueExpr(Pickup->CouldBeTaken());

    return true;
}

#endif