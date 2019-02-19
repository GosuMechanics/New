#pragma once
#define MAKE_RVA(ADDRESS) ( (DWORD)GetModuleHandleA(0) + (DWORD)##ADDRESS )
#define MAKEPTR(ptr) *(DWORD*)((DWORD)GetModuleHandleA(0) + (DWORD)##ptr)
