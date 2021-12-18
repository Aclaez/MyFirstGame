// Shoot Them Up Game, All Rights Reserved.

#if WITH_AUTOMATION_TESTS

#include "Tests/STUBaseCharacterTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Player/STUBaseCharacter.h"
#include "ShootThemUp/Public/Tests/TestUtils.h"
#include "Components/CapsuleComponent.h"
#include "Engine/CollisionProfile.h"
#include "Components/STUWeaponComponent.h"
#include "Components/STUHealthComponent.h"
#include "Components/STUCharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FBaseCharacterCouldBeCreated, "STUGame.Player.BaseCharacter.BaseCharacterCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterCollisionShouldBeSetupCorrectly,
    "STUGame.Player.BaseCharacter.CharacterCollisionShouldBeSetupCorrectly",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterWeaponCouldBeCreated, "STUGame.Player.BaseCharacter.CharacterWeaponCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterHealthCouldBeCreated, "STUGame.Player.BaseCharacter.CharacterHealthCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterMovementCouldBeCreated, "STUGame.Player.BaseCharacter.CharacterMovementCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterMeshCouldBeCreated, "STUGame.Player.BaseCharacter.CharacterMeshCouldBeCreated",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FCharacterMeshIsNotRunning, "STUGame.Player.BaseCharacter.CharacterMeshIsNotRunning",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)

using namespace STU::Tests;

namespace
{
constexpr char* BaseCharacterBPName = "Blueprint'/Game/Player/BP_STUBaseCharacter.BP_STUBaseCharacter'";
}

bool FBaseCharacterCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    return true;
}

bool FCharacterCollisionShouldBeSetupCorrectly::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    const auto CollisionComp = BaseCharacter->FindComponentByClass<UCapsuleComponent>();
    if (!TestNotNull("Collision component exists", CollisionComp)) return false;

    TestTrueExpr(CollisionComp->GetUnscaledCapsuleRadius() >= 20.0f);
    TestTrueExpr(CollisionComp->GetUnscaledCapsuleHalfHeight() >= 50.0f);
    TestTrueExpr(CollisionComp->GetCollisionProfileName() == UCollisionProfile::Pawn_ProfileName);
    TestTrueExpr(BaseCharacter->GetRootComponent() == CollisionComp);

    return true;
}

bool FCharacterWeaponCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    const auto WeaponComp = BaseCharacter->FindComponentByClass<USTUWeaponComponent>();
    if (!TestNotNull("Weapon component exists", WeaponComp)) return false;

    return true;
}

bool FCharacterHealthCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    const auto HealthComp = BaseCharacter->FindComponentByClass<USTUHealthComponent>();
    if (!TestNotNull("Health component exists", HealthComp)) return false;

    return true;
}

bool FCharacterMovementCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    const auto MovementComp = BaseCharacter->FindComponentByClass<USTUCharacterMovementComponent>();
    if (!TestNotNull("Movement component exists", MovementComp)) return false;

    return true;
}

bool FCharacterMeshCouldBeCreated::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    const auto MeshComp = BaseCharacter->FindComponentByClass<USkeletalMeshComponent>();
    if (!TestNotNull("Mesh component exists", MeshComp)) return false;

    return true;
}

bool FCharacterMeshIsNotRunning::RunTest(const FString& Parameters)
{
    LevelScope(FString(TestLevelName));

    UWorld* TestWorld = GetTestGameWorld();
    if (!TestNotNull("World exists", TestWorld)) return false;

    const UBlueprint* CharacterBlueprint = LoadObject<UBlueprint>(nullptr, *FString(BaseCharacterBPName));
    if (!TestNotNull("Character blueprint exists", CharacterBlueprint)) return false;

    const FTransform InitialTranform{FVector{0.0f, 0.0f, 130.0f}};
    const ASTUBaseCharacter* BaseCharacter = TestWorld->SpawnActor<ASTUBaseCharacter>(CharacterBlueprint->GeneratedClass, InitialTranform);
    if (!TestNotNull("Base character exists", BaseCharacter)) return false;

    TestTrueExpr(!BaseCharacter->IsRunning());

    return true;
}

#endif