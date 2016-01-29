#ifdef SUPPORTS_PRAGMA_ONCE
# pragma once
#endif
#ifndef sl_sigstream_rtw_h
#define sl_sigstream_rtw_h
/*
 *
 * Copyright 2008-2014 The MathWorks, Inc.
 *
 * This header is the interface to the sigstream module. It is used by the
 * RTW-RSim and Rapid Accelerator targets.
 *
 * 
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

extern void rtwAobHierarchyCreateRootNode(void **outAobHierarchy);

extern void rtwAobHierarchyCreateNode(const char *name, void **outAobHierarchy);

extern void rtwAobHierarchySetDim(
    void *pOpaqueAobHierarchy,
    const unsigned int nDims,
    const unsigned int *pDim
    );

extern void rtwAobHierarchyAddChild(
    void *pOpaqueAobParent, 
    void *pOpaqueAobChild
    );

extern void rtwAobHierarchyVerifyNNodes(
    void *pOpaqueAobHierarchy,
    const unsigned int nNodes
    );

extern void rtwSignalProbeCollectionCreateInstance(
    const char *datasetName,
    const char *elementName,
    const char *allButLocalBlockPath,
    const char *localBlockPath,
    const char *sigLogSelectorFileName,
    const unsigned int portIdx,
    void **outSignalProbeCollection
    );

extern void rtwSignalProbeCollectionDestroyInstance(
    void *pOpaqueSignalProbeCollection    
    );

extern void rtwSignalProbeCollectionAddElement(
    void * const pOpaqueSignalProbeCollection,
    const char *signalName,
    const char *interpMethod,
    const unsigned int decimation,
    const unsigned int maxDataPoints,
    const unsigned int nDims,
    const unsigned int *pDim,
    const unsigned int complexity,
    const char *units,
    const char *typeName
    );

extern void rtwSignalProbeCollectionAddElementFxp(
    void * const pOpaqueSignalProbeCollection,
    const char *signalName,
    const char *interpMethod,
    const unsigned int decimation,
    const unsigned int maxDataPoints,
    const unsigned int nDims,
    const unsigned int *pDim,
    const unsigned int complexity,
    const char *units,
    const char *typeName,
    const unsigned int isSigned,
    const int wordLength,
    const double slopeAdjustmentFactor,
    const int fixedExponent,
    const double bias
    );

extern void rtwSignalProbeCollectionVerifyNLeaves(
    const void * const pOpaqueSignalProbeCollection,
    const unsigned int nLeaves
    );

extern void rtwSignalProbeCollectionSetAobHierarchy(
    void * const pOpaqueSignalProbeCollection,
    void * const pOpaqueAobHierarchy
    );

extern void rtwSignalProbeCollectionFinalizeMetaData(
    void * const pOpaqueSignalProbeCollection
    );

extern void rtwSignalProbeCollectionAppendSample(
    void * const pOpaqueSignalProbeCollection,
    const unsigned int elementIdx,
    const double t,
    const void * const pData
    );

extern void rtwSignalProbeCollectionSaveDatasetMatFile(
    const void * const pOpaqueSignalProbeCollection,
    const char *fileName
    );

extern int rtwSignalProbeCollectionGetLoggingIsOn(
    const void * const pOpaqueSignalProbeCollection
    );

#ifdef __cplusplus
}
#endif

#endif /* sl_sigstream_rtw_h */

/* LocalWords:  RSim
 */
