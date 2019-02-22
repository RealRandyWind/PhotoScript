#ifndef PHOTO_SCRIPT_HPP
#define PHOTO_SCRIPT_HPP

#include <time.h>

#define HASH_SIZE 8
#define CAMERA_POINTS_MAX_X 36
#define CAMERA_POINTS_MAX_Y 24
#define CAMERA_POINTS_MAX (CAMERA_POINTS_MAX_X * CAMERA_POINTS_MAX_Y)
#define CAMERA_MAX 64
#define ADAPTER_MAX 32

#define EXCEPTION_EXITMASK 1
#define EXCEPTION_TYPEMASK 16
#define EXCEPTION_CODEMASK ~(EXCEPTION_TYPEMASK | EXCEPTION_EXITMASK)

#define _Trow_Exception(Code) _Exception((Code), __FUNCSIG__, __FILE__, (FSize)__LINE__)

#define Null 0
#define True 1
#define False 0
#define Failure -1
#define Success 0
#define None 0
#define First 1
#define Start 0

typedef int FInteger;
typedef char * FString;
typedef int FReturn;
typedef double FReal;
typedef int FBoolean;
typedef size_t FSize;
typedef time_t FTime;
typedef void FVoid;

static const FReal Focus_Auto = -1.0;
static const FReal Focus_Infinite = 0.0;

struct FUUID
{
	unsigned int Hash[HASH_SIZE];
};

struct FAdapter
{
	FSize _ID;
	FBoolean _Valid;
	FReturn (* _Focus)(FTime, struct FCamera *);
	FReturn (* _Click)(struct FCamera *);
	FReturn (* _Update)(struct FCamera *);
	FReturn (* _UnMount)(struct FCamera *);
	FReturn (* _Mount)(struct FCamera *);
	FBoolean (* _Assert)(struct FCamera *);
	FBoolean (* _Detect)(FVoid);
};

struct FPlan
{
	FSize _PID, _GID, _TID, NStops, N;
	FTime TStart, TEnd, T, TEvery;
	FVoid (* BeforeClick)(struct FCamera *);
	FVoid (* AfterClick)(struct FCamera *);
	FVoid (* BeforeFocus)(struct FCamera *);
	FVoid (* AfterFocus)(struct FCamera *);
};

struct FCamera
{
	FAdapter *_Adapter;
	FBoolean _Connected, _Valid;
	FSize _ID, _DID, WB, ISO;
	FReal A, S, TTL, EV, MM;
	FReal Points[CAMERA_POINTS_MAX];
	struct FPlan Plan;
};

FUUID _UUID();

FVoid _BeforeExit();

FVoid _Exception(FSize, FString , FString , FSize);
FBoolean _Assert_Camera(struct FCamera *);
FBoolean _Assert_Adapter(struct FAdapter *);

FSize _Register(struct FAdapter);
FSize _Mount(struct FAdapter *);
FSize _Detect(FVoid);

#endif