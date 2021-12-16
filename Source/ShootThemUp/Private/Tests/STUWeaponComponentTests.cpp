// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "STUWeaponComponentTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Components/STUWeaponComponent.h"
#include "Player/STUPlayerCharacter.h"
#include "STURifleWeapon.h"
#include "STULauncherWeapon.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWeaponComponentCouldBeCreated, "STUGame.Components.Weapon.WeaponComponentCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FWeaponComponentIsFiring, "STUGame.Components.Weapon.WeaponComponentIsFiring",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

bool FWeaponComponentCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PlayerBlueprint = LoadObject<UBlueprint>(nullptr, *FString(PlayerBPName));
    if (!TestNotNull("PlayerBlueprint exists", PlayerBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUPlayerCharacter* Player = TestWorld->SpawnActor<ASTUPlayerCharacter>(PlayerBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Player exists", Player)) return false;

    const auto WeaponComponent = Player->FindComponentByClass<USTUWeaponComponent>();
    if (!TestNotNull("Weapon component exists", WeaponComponent)) return false;

    return true;
}

bool FWeaponComponentIsFiring::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUPlayerCharacter* Player = CreateBlueprint<ASTUPlayerCharacter>(TestWorld, FString(PlayerBPName), InitialTranform);
    if (!TestNotNull("Player exists", Player)) return false;

    const USTUWeaponComponent* WeaponComponent = Player->FindComponentByClass<USTUWeaponComponent>();
    if (!TestNotNull("Weapon component exists", WeaponComponent)) return false;

    TestTrueExpr(!WeaponComponent->IsFiring());

    return true;
}

#endif
