// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUPlayerCharacterTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Player/STUPlayerCharacter.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlayerCharacterCouldBeCreated, "STUGame.Player.PlayerCharacter.PlayerCharacterCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlayerSpringArmCouldBeCreated, "STUGame.Player.PlayerCharacter.PlayerSpringArmCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlayerCameraCouldBeCreated, "STUGame.Player.PlayerCharacter.PlayerCameraCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlayerCameraCollisionCouldBeCreated, "STUGame.Player.PlayerCharacter.PlayerCameraCollisionCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

bool FPlayerCharacterCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PlayerBlueprint = LoadObject<UBlueprint>(nullptr, *FString(PlayerBPName));
    if (!TestNotNull("PlayerBlueprint exists", PlayerBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUPlayerCharacter* Player = TestWorld->SpawnActor<ASTUPlayerCharacter>(PlayerBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Player exists", Player)) return false;

    return true;
}

bool FPlayerSpringArmCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PlayerBlueprint = LoadObject<UBlueprint>(nullptr, *FString(PlayerBPName));
    if (!TestNotNull("PlayerBlueprint exists", PlayerBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUPlayerCharacter* Player = TestWorld->SpawnActor<ASTUPlayerCharacter>(PlayerBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Player exists", Player)) return false;

    const auto SpringArmComp = Player->FindComponentByClass<USpringArmComponent>();
    if (!TestNotNull("Spring arm component exists", SpringArmComp)) return false;

    return true;
}

bool FPlayerCameraCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PlayerBlueprint = LoadObject<UBlueprint>(nullptr, *FString(PlayerBPName));
    if (!TestNotNull("PlayerBlueprint exists", PlayerBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUPlayerCharacter* Player = TestWorld->SpawnActor<ASTUPlayerCharacter>(PlayerBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Player exists", Player)) return false;

    const auto CameraComp = Player->FindComponentByClass<UCameraComponent>();
    if (!TestNotNull("Camera component exists", CameraComp)) return false;

    return true;
}

bool FPlayerCameraCollisionCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* PlayerBlueprint = LoadObject<UBlueprint>(nullptr, *FString(PlayerBPName));
    if (!TestNotNull("PlayerBlueprint exists", PlayerBlueprint)) return false;

    const FTransform InitialTranform{FVector{100.0f, 100.0f, 130.0f}};
    const ASTUPlayerCharacter* Player = TestWorld->SpawnActor<ASTUPlayerCharacter>(PlayerBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Player exists", Player)) return false;

    const auto CameraCollisionComp = Player->FindComponentByClass<USphereComponent>();
    if (!TestNotNull("Camera collision component exists", CameraCollisionComp)) return false;

    return true;
}

#endif