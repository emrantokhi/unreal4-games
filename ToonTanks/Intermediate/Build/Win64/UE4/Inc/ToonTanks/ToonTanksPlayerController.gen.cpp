// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ToonTanks/ToonTanksPlayerController.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeToonTanksPlayerController() {}
// Cross Module References
	TOONTANKS_API UClass* Z_Construct_UClass_AToonTanksPlayerController_NoRegister();
	TOONTANKS_API UClass* Z_Construct_UClass_AToonTanksPlayerController();
	ENGINE_API UClass* Z_Construct_UClass_APlayerController();
	UPackage* Z_Construct_UPackage__Script_ToonTanks();
// End Cross Module References
	void AToonTanksPlayerController::StaticRegisterNativesAToonTanksPlayerController()
	{
	}
	UClass* Z_Construct_UClass_AToonTanksPlayerController_NoRegister()
	{
		return AToonTanksPlayerController::StaticClass();
	}
	struct Z_Construct_UClass_AToonTanksPlayerController_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AToonTanksPlayerController_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_APlayerController,
		(UObject* (*)())Z_Construct_UPackage__Script_ToonTanks,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AToonTanksPlayerController_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "ToonTanksPlayerController.h" },
		{ "ModuleRelativePath", "ToonTanksPlayerController.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AToonTanksPlayerController_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AToonTanksPlayerController>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AToonTanksPlayerController_Statics::ClassParams = {
		&AToonTanksPlayerController::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002A4u,
		METADATA_PARAMS(Z_Construct_UClass_AToonTanksPlayerController_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AToonTanksPlayerController_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AToonTanksPlayerController()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AToonTanksPlayerController_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AToonTanksPlayerController, 1356298593);
	template<> TOONTANKS_API UClass* StaticClass<AToonTanksPlayerController>()
	{
		return AToonTanksPlayerController::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AToonTanksPlayerController(Z_Construct_UClass_AToonTanksPlayerController, &AToonTanksPlayerController::StaticClass, TEXT("/Script/ToonTanks"), TEXT("AToonTanksPlayerController"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AToonTanksPlayerController);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
