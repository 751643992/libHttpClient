// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#pragma once
#pragma pack(push, 16)

#include "EtwPlus.h"

#if defined(__cplusplus)
extern "C" {
#endif

// Field Descriptors, used in the ETX_EVENT_DESCRIPTOR array below
//
EXTERN_C __declspec(selectany) ETX_FIELD_DESCRIPTOR ATGSampleTelemetry_SampleLoaded_Fields[2] = {{EtxFieldType_UnicodeString,0},{EtxFieldType_UnicodeString,0}};

// Event name mapping
//
#define SampleLoaded_value 1

// Event Descriptor array
//
EXTERN_C __declspec(selectany) ETX_EVENT_DESCRIPTOR ATGSampleTelemetryEvents[1] =  {
    {{ 1, 1, 0, 0, 0, 0, 0x0 }, "SampleLoaded", "0.7.0.1", ATGSampleTelemetry_SampleLoaded_Fields, 2, 0, EtxEventEnabledState_Undefined, EtxEventEnabledState_ProviderDefault, EtxPopulationSample_Undefined, 100, EtxEventLatency_Undefined, EtxEventLatency_ProviderDefault, EtxEventPriority_Undefined, EtxEventPriority_ProviderDefault }};

// Provider Descriptor for ATGSampleTelemetry
//
EXTERN_C __declspec(selectany) ETX_PROVIDER_DESCRIPTOR ATGSampleTelemetryProvider = {"ATGSampleTelemetry", {0x1d9d44d6,0x4b94,0x4b72,{0xa8,0xa4,0xda,0x77,0xe0,0x50,0x9e,0xbb}}, 1, (ETX_EVENT_DESCRIPTOR*)&ATGSampleTelemetryEvents, 0, EtxProviderEnabledState_Undefined, EtxProviderEnabledState_OnByDefault, 0, 100, EtxProviderLatency_Undefined, EtxProviderLatency_Normal, EtxProviderPriority_Undefined, EtxProviderPriority_Normal};

// ETW handle for ATGSampleTelemetry
//
EXTERN_C __declspec(selectany) REGHANDLE ATGSampleTelemetryHandle = (REGHANDLE)0;

/*++

Routine Description:

    Register the provider with ETW+.

Arguments:
    
    None

Remarks:

    ERROR_SUCCESS if success or if the provider was already registered. 
    Otherwise, an error code.

--*/
#define EventRegisterATGSampleTelemetry() EtxRegister(&ATGSampleTelemetryProvider, &ATGSampleTelemetryHandle)

/*++

Routine Description:

    Unregister the provider from ETW+.

Arguments:
            None
Remarks:
    ERROR_SUCCESS if success or if the provider was not registered. 
    Otherwise, an error code.
--*/
#define EventUnregisterATGSampleTelemetry() EtxUnregister(&ATGSampleTelemetryProvider, &ATGSampleTelemetryHandle)

#define EventEnabledSampleLoaded() (TRUE)

// Entry point to log the event SampleLoaded
//
__inline
ULONG
EventWriteSampleLoaded(__in_opt PCWSTR ExeName)
{
#define ARGUMENT_COUNT_ATGSampleTelemetry_SampleLoaded 2

    EVENT_DATA_DESCRIPTOR EventData[ARGUMENT_COUNT_ATGSampleTelemetry_SampleLoaded];
    UINT8 scratch[64];

    EtxFillCommonFields_v7(&EventData[0], scratch, 64);

    EventDataDescCreate(&EventData[1], (ExeName != NULL) ? ExeName : L"", (ExeName != NULL) ? (ULONG)((wcslen(ExeName) + 1) * sizeof(WCHAR)) : (ULONG)sizeof(L""));

    return EtxEventWrite(&ATGSampleTelemetryEvents[0], &ATGSampleTelemetryProvider, ATGSampleTelemetryHandle, ARGUMENT_COUNT_ATGSampleTelemetry_SampleLoaded, EventData);
}
#if defined(__cplusplus)
};
#endif

#pragma pack(pop)