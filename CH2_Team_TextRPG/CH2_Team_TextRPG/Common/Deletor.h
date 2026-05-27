#pragma once

#define SAFE_DELETE(x) { if(x){ delete x; x = 0; } }
#define SAFE_DELETE_ARRAY(x) { if(x) { delete [] x; x = 0; } }

template<class T>
void SafeDelete(T*& P)
{
    if(P != nullptr)
    {
      delete P;
      P = nullptr;
    }
}

template<class T>
void SafeDeleteArray(T*& P)
{
    if(P != nullptr)
    {
      delete[] P;
      P = nullptr;
    }
}
