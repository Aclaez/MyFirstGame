// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUAmmoPickupTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Pickups/STUAmmoPickup.h"
#include "Player/STUPlayerCharacter.h"
#include "STURifleWeapon.h"
#include "STULauncherWeapon.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include <Components/SphereComponent.h>
#include <Components/StaticMeshComponent.h>

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAmmoPickupCouldBeCreated, "STUGame.Pickups.Ammo.AmmoPickupCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAmmoCollisionShouldBeSetupCorrectly, "STUGame.Pickups.Ammo.AmmoCollisionShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAmmoMeshShouldBeSetupCorrectly, "STUGame.Pickups.Ammo.AmmoMeshShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

bool FAmmoPickupCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(AmmoBPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUAmmoPickup* Pickup = TestWorld->SpawnActor<ASTUAmmoPickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    return true;
}

bool FAmmoCollisionShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(AmmoBPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUAmmoPickup* Pickup = TestWorld->SpawnActor<ASTUAmmoPickup>(PickupBlueprint->GeneratedClass, InitialTranform);
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

bool FAmmoMeshShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PickupBlueprint = LoadObject<UBlueprint>(nullptr, *FString(AmmoBPName));
    if (!TestNotNull("PickupBlueprint exists", PickupBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUAmmoPickup* Pickup = TestWorld->SpawnActor<ASTUAmmoPickup>(PickupBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Pickup exists", Pickup)) return false;

    const auto MeshComp = Pickup->FindComponentByClass<UStaticMeshComponent>();
    if (!TestNotNull("StaticMesh exists", MeshComp)) return false;

    TestTrueExpr(MeshComp->GetCollisionEnabled() == ECollisionEnabled::NoCollision);

    return true;
}

#endif