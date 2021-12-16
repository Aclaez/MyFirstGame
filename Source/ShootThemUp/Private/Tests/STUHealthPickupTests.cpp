// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUHealthPickupTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Pickups/STUHealthPickup.h"
#include "Player/STUPlayerCharacter.h"
#include "STURifleWeapon.h"
#include "STULauncherWeapon.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthPickupCouldBeCreated, "STUGame.Pickups.Health.HealthPickupCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthCollisionShouldBeSetupCorrectly, "STUGame.Pickups.Health.HealthCollisionShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FHealthMeshShouldBeSetupCorrectly, "STUGame.Pickups.Health.HealthMeshShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

bool FHealthPickupCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(HealthBPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUHealthPickup* Pickup = TestWorld->SpawnActor<ASTUHealthPickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    return true;
}

bool FHealthCollisionShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(HealthBPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUHealthPickup* Pickup = TestWorld->SpawnActor<ASTUHealthPickup>(PickupBlueprint->GeneratedClass, InitialTranform);
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

bool FHealthMeshShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(HealthBPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUHealthPickup* Pickup = TestWorld->SpawnActor<ASTUHealthPickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    const auto MeshComp = Pickup->FindComponentByClass<UStaticMeshComponent>();
    if (!TestNotNull("StaticMesh exists", MeshComp)) return false;

    TestTrueExpr(MeshComp->GetCollisionEnabled() == ECollisionEnabled::NoCollision);

    return true;
}

#endif