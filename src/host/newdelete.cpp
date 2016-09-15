/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/

#include "precomp.h"

void EnsureHeap()
{
    // This function exists to ensure it gets touched by the linker before the msvcrt lib.
    // Removing this function (and the reference in the DLL's main.cpp) will cause the linker to reorder and collide this
    // file's new/delete definitions with those in the default CRT.
    return;
}

#pragma prefast(suppress: 28250, "ignoring this warning because the original compiler internal implementation didn't have SAL annotations")
void * _cdecl operator new(_In_ size_t size)
{
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
}

#pragma prefast(suppress: 28250, "ignoring this warning because the original compiler internal implementation didn't have SAL annotations")
void * __cdecl operator new[](_In_ size_t cb)
{
    return operator new(cb);
}

#pragma prefast(suppress: 28250, "ignoring this warning because the original compiler internal implementation didn't have SAL annotations")
void _cdecl operator delete(_In_ void *pv)
{
    HeapFree(GetProcessHeap(), 0, pv);
}

#pragma prefast(suppress: 28250, "ignoring this warning because the original compiler internal implementation didn't have SAL annotations")
void __cdecl operator delete[](_In_ void * p)
{
    operator delete(p);
}
