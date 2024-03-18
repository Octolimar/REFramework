#pragma once
#pragma managed

#include "API.hpp"

using namespace System::Collections::Generic;

namespace REFrameworkNET {
ref class API;

#define GENERATE_POCKET_CLASS(EVENT_NAME) \
static void EVENT_NAME##PreHandler_Internal(); \
static void EVENT_NAME##PostHandler_Internal(); \
public ref class EVENT_NAME { \
public: \
    delegate void Delegate(); \
    static event Delegate^ Pre; \
    static event Delegate^ Post; \
    static void TriggerPre() { \
        Pre(); \
    } \
    static void TriggerPost() { \
        Post(); \
    } \
    static System::Reflection::MethodInfo^ TriggerPreMethod = nullptr;\
    static System::Reflection::MethodInfo^ TriggerPostMethod = nullptr;\
    static uintptr_t FUNCTION_PRE_CALLBACK_ADDRESS = (uintptr_t)&EVENT_NAME##PreHandler_Internal; \
    static uintptr_t FUNCTION_POST_CALLBACK_ADDRESS = (uintptr_t)&EVENT_NAME##PostHandler_Internal; \
}; \
void EVENT_NAME##PreHandler_Internal() { \
    if (Callbacks::##EVENT_NAME::TriggerPreMethod == nullptr) { \
        auto self = System::Reflection::Assembly::LoadFrom(System::Reflection::Assembly::GetExecutingAssembly()->Location); \
        auto type = self->GetType("REFrameworkNET.Callbacks." #EVENT_NAME); \
        Callbacks::##EVENT_NAME::TriggerPreMethod = type->GetMethod("TriggerPre", System::Reflection::BindingFlags::Static | System::Reflection::BindingFlags::Public); \
    } \
    Callbacks::##EVENT_NAME::TriggerPreMethod->Invoke(nullptr, nullptr); \
} \
void EVENT_NAME##PostHandler_Internal() { \
    if (Callbacks::##EVENT_NAME::TriggerPostMethod == nullptr) { \
        auto self = System::Reflection::Assembly::LoadFrom(System::Reflection::Assembly::GetExecutingAssembly()->Location); \
        auto type = self->GetType("REFrameworkNET.Callbacks." #EVENT_NAME); \
        Callbacks::##EVENT_NAME::TriggerPostMethod = type->GetMethod("TriggerPost", System::Reflection::BindingFlags::Static | System::Reflection::BindingFlags::Public); \
    } \
    Callbacks::##EVENT_NAME::TriggerPostMethod->Invoke(nullptr, nullptr); \
}

namespace Callbacks {
    GENERATE_POCKET_CLASS(Initialize)
    GENERATE_POCKET_CLASS(InitializeLog)
    GENERATE_POCKET_CLASS(InitializeGameCore)
    GENERATE_POCKET_CLASS(InitializeStorage)
    GENERATE_POCKET_CLASS(InitializeResourceManager)
    GENERATE_POCKET_CLASS(InitializeScene)
    GENERATE_POCKET_CLASS(InitializeRemoteHost)
    GENERATE_POCKET_CLASS(InitializeVM)
    GENERATE_POCKET_CLASS(InitializeSystemService)
    GENERATE_POCKET_CLASS(InitializeHardwareService)
    GENERATE_POCKET_CLASS(InitializePushNotificationService)
    GENERATE_POCKET_CLASS(InitializeDialog)
    GENERATE_POCKET_CLASS(InitializeShareService)
    GENERATE_POCKET_CLASS(InitializeUserService)
    GENERATE_POCKET_CLASS(InitializeUDS)
    GENERATE_POCKET_CLASS(InitializeModalDialogService)
    GENERATE_POCKET_CLASS(InitializeGlobalUserData)
    GENERATE_POCKET_CLASS(InitializeSteam)
    GENERATE_POCKET_CLASS(InitializeWeGame)
    GENERATE_POCKET_CLASS(InitializeXCloud)
    GENERATE_POCKET_CLASS(InitializeRebe)
    GENERATE_POCKET_CLASS(InitializeBcat)
    GENERATE_POCKET_CLASS(InitializeEffectMemorySettings)
    GENERATE_POCKET_CLASS(InitializeRenderer)
    GENERATE_POCKET_CLASS(InitializeVR)
    GENERATE_POCKET_CLASS(InitializeSpeedTree)
    GENERATE_POCKET_CLASS(InitializeHID)
    GENERATE_POCKET_CLASS(InitializeEffect)
    GENERATE_POCKET_CLASS(InitializeGeometry)
    GENERATE_POCKET_CLASS(InitializeLandscape)
    GENERATE_POCKET_CLASS(InitializeHoudini)
    GENERATE_POCKET_CLASS(InitializeSound)
    GENERATE_POCKET_CLASS(InitializeWwiselib)
    GENERATE_POCKET_CLASS(InitializeSimpleWwise)
    GENERATE_POCKET_CLASS(InitializeWwise)
    GENERATE_POCKET_CLASS(InitializeAudioRender)
    GENERATE_POCKET_CLASS(InitializeGUI)
    GENERATE_POCKET_CLASS(InitializeSpine)
    GENERATE_POCKET_CLASS(InitializeMotion)
    GENERATE_POCKET_CLASS(InitializeBehaviorTree)
    GENERATE_POCKET_CLASS(InitializeAutoPlay)
    GENERATE_POCKET_CLASS(InitializeScenario)
    GENERATE_POCKET_CLASS(InitializeOctree)
    GENERATE_POCKET_CLASS(InitializeAreaMap)
    GENERATE_POCKET_CLASS(InitializeFSM)
    GENERATE_POCKET_CLASS(InitializeNavigation)
    GENERATE_POCKET_CLASS(InitializePointGraph)
    GENERATE_POCKET_CLASS(InitializeFluidFlock)
    GENERATE_POCKET_CLASS(InitializeTimeline)
    GENERATE_POCKET_CLASS(InitializePhysics)
    GENERATE_POCKET_CLASS(InitializeDynamics)
    GENERATE_POCKET_CLASS(InitializeHavok)
    GENERATE_POCKET_CLASS(InitializeBake)
    GENERATE_POCKET_CLASS(InitializeNetwork)
    GENERATE_POCKET_CLASS(InitializePuppet)
    GENERATE_POCKET_CLASS(InitializeVoiceChat)
    GENERATE_POCKET_CLASS(InitializeVivoxlib)
    GENERATE_POCKET_CLASS(InitializeStore)
    GENERATE_POCKET_CLASS(InitializeBrowser)
    GENERATE_POCKET_CLASS(InitializeDevelopSystem)
    GENERATE_POCKET_CLASS(InitializeBehavior)
    GENERATE_POCKET_CLASS(InitializeMovie)
    GENERATE_POCKET_CLASS(InitializeMame)
    GENERATE_POCKET_CLASS(InitializeSkuService)
    GENERATE_POCKET_CLASS(InitializeTelemetry)
    GENERATE_POCKET_CLASS(InitializeHansoft)
    GENERATE_POCKET_CLASS(InitializeNNFC)
    GENERATE_POCKET_CLASS(InitializeMixer)
    GENERATE_POCKET_CLASS(InitializeThreadPool)
    GENERATE_POCKET_CLASS(Setup)
    GENERATE_POCKET_CLASS(SetupJobScheduler)
    GENERATE_POCKET_CLASS(SetupResourceManager)
    GENERATE_POCKET_CLASS(SetupStorage)
    GENERATE_POCKET_CLASS(SetupGlobalUserData)
    GENERATE_POCKET_CLASS(SetupScene)
    GENERATE_POCKET_CLASS(SetupDevelopSystem)
    GENERATE_POCKET_CLASS(SetupUserService)
    GENERATE_POCKET_CLASS(SetupSystemService)
    GENERATE_POCKET_CLASS(SetupHardwareService)
    GENERATE_POCKET_CLASS(SetupPushNotificationService)
    GENERATE_POCKET_CLASS(SetupShareService)
    GENERATE_POCKET_CLASS(SetupModalDialogService)
    GENERATE_POCKET_CLASS(SetupVM)
    GENERATE_POCKET_CLASS(SetupHID)
    GENERATE_POCKET_CLASS(SetupRenderer)
    GENERATE_POCKET_CLASS(SetupEffect)
    GENERATE_POCKET_CLASS(SetupGeometry)
    GENERATE_POCKET_CLASS(SetupLandscape)
    GENERATE_POCKET_CLASS(SetupHoudini)
    GENERATE_POCKET_CLASS(SetupSound)
    GENERATE_POCKET_CLASS(SetupWwiselib)
    GENERATE_POCKET_CLASS(SetupSimpleWwise)
    GENERATE_POCKET_CLASS(SetupWwise)
    GENERATE_POCKET_CLASS(SetupAudioRender)
    GENERATE_POCKET_CLASS(SetupMotion)
    GENERATE_POCKET_CLASS(SetupNavigation)
    GENERATE_POCKET_CLASS(SetupPointGraph)
    GENERATE_POCKET_CLASS(SetupPhysics)
    GENERATE_POCKET_CLASS(SetupDynamics)
    GENERATE_POCKET_CLASS(SetupHavok)
    GENERATE_POCKET_CLASS(SetupMovie)
    GENERATE_POCKET_CLASS(SetupMame)
    GENERATE_POCKET_CLASS(SetupNetwork)
    GENERATE_POCKET_CLASS(SetupPuppet)
    GENERATE_POCKET_CLASS(SetupStore)
    GENERATE_POCKET_CLASS(SetupBrowser)
    GENERATE_POCKET_CLASS(SetupVoiceChat)
    GENERATE_POCKET_CLASS(SetupVivoxlib)
    GENERATE_POCKET_CLASS(SetupSkuService)
    GENERATE_POCKET_CLASS(SetupTelemetry)
    GENERATE_POCKET_CLASS(SetupHansoft)
    GENERATE_POCKET_CLASS(StartApp)
    GENERATE_POCKET_CLASS(SetupOctree)
    GENERATE_POCKET_CLASS(SetupAreaMap)
    GENERATE_POCKET_CLASS(SetupBehaviorTree)
    GENERATE_POCKET_CLASS(SetupFSM)
    GENERATE_POCKET_CLASS(SetupGUI)
    GENERATE_POCKET_CLASS(SetupSpine)
    GENERATE_POCKET_CLASS(SetupSpeedTree)
    GENERATE_POCKET_CLASS(SetupNNFC)
    GENERATE_POCKET_CLASS(Start)
    GENERATE_POCKET_CLASS(StartStorage)
    GENERATE_POCKET_CLASS(StartResourceManager)
    GENERATE_POCKET_CLASS(StartGlobalUserData)
    GENERATE_POCKET_CLASS(StartPhysics)
    GENERATE_POCKET_CLASS(StartDynamics)
    GENERATE_POCKET_CLASS(StartGUI)
    GENERATE_POCKET_CLASS(StartTimeline)
    GENERATE_POCKET_CLASS(StartOctree)
    GENERATE_POCKET_CLASS(StartAreaMap)
    GENERATE_POCKET_CLASS(StartBehaviorTree)
    GENERATE_POCKET_CLASS(StartFSM)
    GENERATE_POCKET_CLASS(StartSound)
    GENERATE_POCKET_CLASS(StartWwise)
    GENERATE_POCKET_CLASS(StartAudioRender)
    GENERATE_POCKET_CLASS(StartScene)
    GENERATE_POCKET_CLASS(StartRebe)
    GENERATE_POCKET_CLASS(StartNetwork)
    GENERATE_POCKET_CLASS(Update)
    GENERATE_POCKET_CLASS(UpdateDialog)
    GENERATE_POCKET_CLASS(UpdateRemoteHost)
    GENERATE_POCKET_CLASS(UpdateStorage)
    GENERATE_POCKET_CLASS(UpdateScene)
    GENERATE_POCKET_CLASS(UpdateDevelopSystem)
    GENERATE_POCKET_CLASS(UpdateWidget)
    GENERATE_POCKET_CLASS(UpdateAutoPlay)
    GENERATE_POCKET_CLASS(UpdateScenario)
    GENERATE_POCKET_CLASS(UpdateCapture)
    GENERATE_POCKET_CLASS(BeginFrameRendering)
    GENERATE_POCKET_CLASS(UpdateVR)
    GENERATE_POCKET_CLASS(UpdateHID)
    GENERATE_POCKET_CLASS(UpdateMotionFrame)
    GENERATE_POCKET_CLASS(BeginDynamics)
    GENERATE_POCKET_CLASS(PreupdateGUI)
    GENERATE_POCKET_CLASS(BeginHavok)
    GENERATE_POCKET_CLASS(UpdateAIMap)
    GENERATE_POCKET_CLASS(CreatePreupdateGroupFSM)
    GENERATE_POCKET_CLASS(CreatePreupdateGroupBehaviorTree)
    GENERATE_POCKET_CLASS(UpdateGlobalUserData)
    GENERATE_POCKET_CLASS(UpdateUDS)
    GENERATE_POCKET_CLASS(UpdateUserService)
    GENERATE_POCKET_CLASS(UpdateSystemService)
    GENERATE_POCKET_CLASS(UpdateHardwareService)
    GENERATE_POCKET_CLASS(UpdatePushNotificationService)
    GENERATE_POCKET_CLASS(UpdateShareService)
    GENERATE_POCKET_CLASS(UpdateSteam)
    GENERATE_POCKET_CLASS(UpdateWeGame)
    GENERATE_POCKET_CLASS(UpdateBcat)
    GENERATE_POCKET_CLASS(UpdateXCloud)
    GENERATE_POCKET_CLASS(UpdateRebe)
    GENERATE_POCKET_CLASS(UpdateNNFC)
    GENERATE_POCKET_CLASS(BeginPhysics)
    GENERATE_POCKET_CLASS(BeginUpdatePrimitive)
    GENERATE_POCKET_CLASS(BeginUpdatePrimitiveGUI)
    GENERATE_POCKET_CLASS(BeginUpdateSpineDraw)
    GENERATE_POCKET_CLASS(UpdatePuppet)
    GENERATE_POCKET_CLASS(UpdateGUI)
    GENERATE_POCKET_CLASS(PreupdateBehavior)
    GENERATE_POCKET_CLASS(PreupdateBehaviorTree)
    GENERATE_POCKET_CLASS(PreupdateFSM)
    GENERATE_POCKET_CLASS(PreupdateTimeline)
    GENERATE_POCKET_CLASS(UpdateBehavior)
    GENERATE_POCKET_CLASS(CreateUpdateGroupBehaviorTree)
    GENERATE_POCKET_CLASS(CreateNavigationChain)
    GENERATE_POCKET_CLASS(CreateUpdateGroupFSM)
    GENERATE_POCKET_CLASS(UpdateTimeline)
    GENERATE_POCKET_CLASS(PreUpdateAreaMap)
    GENERATE_POCKET_CLASS(UpdateOctree)
    GENERATE_POCKET_CLASS(UpdateAreaMap)
    GENERATE_POCKET_CLASS(UpdateBehaviorTree)
    GENERATE_POCKET_CLASS(UpdateTimelineFsm2)
    GENERATE_POCKET_CLASS(UpdateNavigationPrev)
    GENERATE_POCKET_CLASS(UpdateFSM)
    GENERATE_POCKET_CLASS(UpdateMotion)
    GENERATE_POCKET_CLASS(UpdateSpine)
    GENERATE_POCKET_CLASS(EffectCollisionLimit)
    GENERATE_POCKET_CLASS(UpdatePhysicsAfterUpdatePhase)
    GENERATE_POCKET_CLASS(UpdateGeometry)
    GENERATE_POCKET_CLASS(UpdateLandscape)
    GENERATE_POCKET_CLASS(UpdateHoudini)
    GENERATE_POCKET_CLASS(UpdatePhysicsCharacterController)
    GENERATE_POCKET_CLASS(BeginUpdateHavok2)
    GENERATE_POCKET_CLASS(UpdateDynamics)
    GENERATE_POCKET_CLASS(UpdateNavigation)
    GENERATE_POCKET_CLASS(UpdatePointGraph)
    GENERATE_POCKET_CLASS(UpdateFluidFlock)
    GENERATE_POCKET_CLASS(UpdateConstraintsBegin)
    GENERATE_POCKET_CLASS(LateUpdateBehavior)
    GENERATE_POCKET_CLASS(EditUpdateBehavior)
    GENERATE_POCKET_CLASS(LateUpdateSpine)
    GENERATE_POCKET_CLASS(BeginUpdateHavok)
    GENERATE_POCKET_CLASS(BeginUpdateEffect)
    GENERATE_POCKET_CLASS(UpdateConstraintsEnd)
    GENERATE_POCKET_CLASS(UpdatePhysicsAfterLateUpdatePhase)
    GENERATE_POCKET_CLASS(PrerenderGUI)
    GENERATE_POCKET_CLASS(PrepareRendering)
    GENERATE_POCKET_CLASS(UpdateSound)
    GENERATE_POCKET_CLASS(UpdateWwiselib)
    GENERATE_POCKET_CLASS(UpdateSimpleWwise)
    GENERATE_POCKET_CLASS(UpdateWwise)
    GENERATE_POCKET_CLASS(UpdateAudioRender)
    GENERATE_POCKET_CLASS(CreateSelectorGroupFSM)
    GENERATE_POCKET_CLASS(UpdateNetwork)
    GENERATE_POCKET_CLASS(UpdateHavok)
    GENERATE_POCKET_CLASS(EndUpdateHavok)
    GENERATE_POCKET_CLASS(UpdateFSMSelector)
    GENERATE_POCKET_CLASS(UpdateBehaviorTreeSelector)
    GENERATE_POCKET_CLASS(BeforeLockSceneRendering)
    GENERATE_POCKET_CLASS(EndUpdateHavok2)
    GENERATE_POCKET_CLASS(UpdateJointExpression)
    GENERATE_POCKET_CLASS(UpdateBehaviorTreeSelectorLegacy)
    GENERATE_POCKET_CLASS(UpdateEffect)
    GENERATE_POCKET_CLASS(EndUpdateEffect)
    GENERATE_POCKET_CLASS(UpdateWidgetDynamics)
    GENERATE_POCKET_CLASS(LockScene)
    GENERATE_POCKET_CLASS(WaitRendering)
    GENERATE_POCKET_CLASS(EndDynamics)
    GENERATE_POCKET_CLASS(EndPhysics)
    GENERATE_POCKET_CLASS(BeginRendering)
    GENERATE_POCKET_CLASS(UpdateSpeedTree)
    GENERATE_POCKET_CLASS(RenderDynamics)
    GENERATE_POCKET_CLASS(RenderGUI)
    GENERATE_POCKET_CLASS(RenderGeometry)
    GENERATE_POCKET_CLASS(RenderLandscape)
    GENERATE_POCKET_CLASS(RenderHoudini)
    GENERATE_POCKET_CLASS(UpdatePrimitiveGUI)
    GENERATE_POCKET_CLASS(UpdatePrimitive)
    GENERATE_POCKET_CLASS(UpdateSpineDraw)
    GENERATE_POCKET_CLASS(EndUpdatePrimitive)
    GENERATE_POCKET_CLASS(EndUpdatePrimitiveGUI)
    GENERATE_POCKET_CLASS(EndUpdateSpineDraw)
    GENERATE_POCKET_CLASS(GUIPostPrimitiveRender)
    GENERATE_POCKET_CLASS(ShapeRenderer)
    GENERATE_POCKET_CLASS(UpdateMovie)
    GENERATE_POCKET_CLASS(UpdateMame)
    GENERATE_POCKET_CLASS(UpdateTelemetry)
    GENERATE_POCKET_CLASS(UpdateHansoft)
    GENERATE_POCKET_CLASS(DrawWidget)
    GENERATE_POCKET_CLASS(DevelopRenderer)
    GENERATE_POCKET_CLASS(EndRendering)
    GENERATE_POCKET_CLASS(UpdateStore)
    GENERATE_POCKET_CLASS(UpdateBrowser)
    GENERATE_POCKET_CLASS(UpdateVoiceChat)
    GENERATE_POCKET_CLASS(UpdateVivoxlib)
    GENERATE_POCKET_CLASS(UnlockScene)
    GENERATE_POCKET_CLASS(UpdateVM)
    GENERATE_POCKET_CLASS(StepVisualDebugger)
    GENERATE_POCKET_CLASS(WaitForVblank)
    GENERATE_POCKET_CLASS(Terminate)
    GENERATE_POCKET_CLASS(TerminateScene)
    GENERATE_POCKET_CLASS(TerminateRemoteHost)
    GENERATE_POCKET_CLASS(TerminateHansoft)
    GENERATE_POCKET_CLASS(TerminateTelemetry)
    GENERATE_POCKET_CLASS(TerminateMame)
    GENERATE_POCKET_CLASS(TerminateMovie)
    GENERATE_POCKET_CLASS(TerminateSound)
    GENERATE_POCKET_CLASS(TerminateSimpleWwise)
    GENERATE_POCKET_CLASS(TerminateWwise)
    GENERATE_POCKET_CLASS(TerminateWwiselib)
    GENERATE_POCKET_CLASS(TerminateAudioRender)
    GENERATE_POCKET_CLASS(TerminateVoiceChat)
    GENERATE_POCKET_CLASS(TerminateVivoxlib)
    GENERATE_POCKET_CLASS(TerminatePuppet)
    GENERATE_POCKET_CLASS(TerminateNetwork)
    GENERATE_POCKET_CLASS(TerminateStore)
    GENERATE_POCKET_CLASS(TerminateBrowser)
    GENERATE_POCKET_CLASS(TerminateSpine)
    GENERATE_POCKET_CLASS(TerminateGUI)
    GENERATE_POCKET_CLASS(TerminateAreaMap)
    GENERATE_POCKET_CLASS(TerminateOctree)
    GENERATE_POCKET_CLASS(TerminateFluidFlock)
    GENERATE_POCKET_CLASS(TerminateBehaviorTree)
    GENERATE_POCKET_CLASS(TerminateFSM)
    GENERATE_POCKET_CLASS(TerminateNavigation)
    GENERATE_POCKET_CLASS(TerminatePointGraph)
    GENERATE_POCKET_CLASS(TerminateEffect)
    GENERATE_POCKET_CLASS(TerminateGeometry)
    GENERATE_POCKET_CLASS(TerminateLandscape)
    GENERATE_POCKET_CLASS(TerminateHoudini)
    GENERATE_POCKET_CLASS(TerminateRenderer)
    GENERATE_POCKET_CLASS(TerminateHID)
    GENERATE_POCKET_CLASS(TerminateDynamics)
    GENERATE_POCKET_CLASS(TerminatePhysics)
    GENERATE_POCKET_CLASS(TerminateResourceManager)
    GENERATE_POCKET_CLASS(TerminateHavok)
    GENERATE_POCKET_CLASS(TerminateModalDialogService)
    GENERATE_POCKET_CLASS(TerminateShareService)
    GENERATE_POCKET_CLASS(TerminateGlobalUserData)
    GENERATE_POCKET_CLASS(TerminateStorage)
    GENERATE_POCKET_CLASS(TerminateVM)
    GENERATE_POCKET_CLASS(TerminateJobScheduler)
    GENERATE_POCKET_CLASS(Finalize)
    GENERATE_POCKET_CLASS(FinalizeThreadPool)
    GENERATE_POCKET_CLASS(FinalizeHansoft)
    GENERATE_POCKET_CLASS(FinalizeTelemetry)
    GENERATE_POCKET_CLASS(FinalizeMame)
    GENERATE_POCKET_CLASS(FinalizeMovie)
    GENERATE_POCKET_CLASS(FinalizeBehavior)
    GENERATE_POCKET_CLASS(FinalizeDevelopSystem)
    GENERATE_POCKET_CLASS(FinalizeTimeline)
    GENERATE_POCKET_CLASS(FinalizePuppet)
    GENERATE_POCKET_CLASS(FinalizeNetwork)
    GENERATE_POCKET_CLASS(FinalizeStore)
    GENERATE_POCKET_CLASS(FinalizeBrowser)
    GENERATE_POCKET_CLASS(finalizeAutoPlay)
    GENERATE_POCKET_CLASS(finalizeScenario)
    GENERATE_POCKET_CLASS(FinalizeBehaviorTree)
    GENERATE_POCKET_CLASS(FinalizeFSM)
    GENERATE_POCKET_CLASS(FinalizeNavigation)
    GENERATE_POCKET_CLASS(FinalizePointGraph)
    GENERATE_POCKET_CLASS(FinalizeAreaMap)
    GENERATE_POCKET_CLASS(FinalizeOctree)
    GENERATE_POCKET_CLASS(FinalizeFluidFlock)
    GENERATE_POCKET_CLASS(FinalizeMotion)
    GENERATE_POCKET_CLASS(FinalizeDynamics)
    GENERATE_POCKET_CLASS(FinalizePhysics)
    GENERATE_POCKET_CLASS(FinalizeHavok)
    GENERATE_POCKET_CLASS(FinalizeBake)
    GENERATE_POCKET_CLASS(FinalizeSpine)
    GENERATE_POCKET_CLASS(FinalizeGUI)
    GENERATE_POCKET_CLASS(FinalizeSound)
    GENERATE_POCKET_CLASS(FinalizeWwiselib)
    GENERATE_POCKET_CLASS(FinalizeSimpleWwise)
    GENERATE_POCKET_CLASS(FinalizeWwise)
    GENERATE_POCKET_CLASS(FinalizeAudioRender)
    GENERATE_POCKET_CLASS(FinalizeEffect)
    GENERATE_POCKET_CLASS(FinalizeGeometry)
    GENERATE_POCKET_CLASS(FinalizeSpeedTree)
    GENERATE_POCKET_CLASS(FinalizeLandscape)
    GENERATE_POCKET_CLASS(FinalizeHoudini)
    GENERATE_POCKET_CLASS(FinalizeRenderer)
    GENERATE_POCKET_CLASS(FinalizeHID)
    GENERATE_POCKET_CLASS(FinalizeVR)
    GENERATE_POCKET_CLASS(FinalizeBcat)
    GENERATE_POCKET_CLASS(FinalizeRebe)
    GENERATE_POCKET_CLASS(FinalizeXCloud)
    GENERATE_POCKET_CLASS(FinalizeSteam)
    GENERATE_POCKET_CLASS(FinalizeWeGame)
    GENERATE_POCKET_CLASS(FinalizeNNFC)
    GENERATE_POCKET_CLASS(FinalizeGlobalUserData)
    GENERATE_POCKET_CLASS(FinalizeModalDialogService)
    GENERATE_POCKET_CLASS(FinalizeSkuService)
    GENERATE_POCKET_CLASS(FinalizeUDS)
    GENERATE_POCKET_CLASS(FinalizeUserService)
    GENERATE_POCKET_CLASS(FinalizeShareService)
    GENERATE_POCKET_CLASS(FinalizeSystemService)
    GENERATE_POCKET_CLASS(FinalizeHardwareService)
    GENERATE_POCKET_CLASS(FinalizePushNotificationService)
    GENERATE_POCKET_CLASS(FinalizeScene)
    GENERATE_POCKET_CLASS(FinalizeVM)
    GENERATE_POCKET_CLASS(FinalizeResourceManager)
    GENERATE_POCKET_CLASS(FinalizeRemoteHost)
    GENERATE_POCKET_CLASS(FinalizeStorage)
    GENERATE_POCKET_CLASS(FinalizeDialog)
    GENERATE_POCKET_CLASS(FinalizeMixer)
    GENERATE_POCKET_CLASS(FinalizeGameCore);

    public ref class Impl {
    public:
        static void Setup(REFrameworkNET::API^ api);
    };
};
}