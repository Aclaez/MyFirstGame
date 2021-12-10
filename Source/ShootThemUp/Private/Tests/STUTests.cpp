// Shoot Them Up Game, All Rights Reserved.

#if (WITH_DEV_AUTOMATION_TESTS || WITH_PERF_AUTOMATION_TEST)

#include "Tests/STUTests.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Weapon/STUBaseWeapon.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathMaxInt, "STUGame.Math.MaxInt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FMathSqrt, "STUGame.Math.Sqrt",
    EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority);

bool FMathMaxInt::RunTest(const FString& Parameters)
{
    AddInfo("Max [int] func testing");

    TestTrue("2 different positive numbers", FMath::Max(13, 25) == 25);
    TestEqual("2 equal positive numbers", FMath::Max(25, 25), 25);
    TestTrueExpr(FMath::Max(0, 123) == 123);
    TestTrue("2 zeros", FMath::Max(0, 0) == 0);
    TestTrue("Negative number and zero", FMath::Max(-2345, 0) == 0);
    TestTrue("2 different negative numbers", FMath::Max(-45, -67) == -45);
    TestTrue("2 equal negative numbers", FMath::Max(-9, -9) == -9);

    return true;
}

bool FMathSqrt::RunTest(const FString& Parameters)
{
    AddInfo("Sqrt func testing");

    TestEqual("Sqrt(4) [0]", FMath::Sqrt(4.0f), 2.0f);
    //TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f);
    TestEqual("Sqrt(3) [1]", FMath::Sqrt(3.0f), 1.7f, 0.1f);

    return true;
}

#endif