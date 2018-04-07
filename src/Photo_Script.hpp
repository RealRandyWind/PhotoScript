#ifndef PHOTO_SCRIPT_HPP
#define PHOTO_SCRIPT_HPP

#define CAMERA_MAX 64
#define CAMERA_FPOINTS_MAX 512
#define ADAPTER_MAX 32
#define Exception_ExitMask 1
#define Exception_TypeMask 16
#define Exception_CodeMask ~(Exception_TypeMask | Exception_ExitMask)

#define _Trow_Exception(Code) _Exception((Code), __FUNCSIG__, __FILE__, (FSize)__LINE__)

#define Null 0
#define True 1
#define False 0
#define Failure -1
#define Success 0
#define None 0

typedef char * FString;
typedef int FReturn;
typedef double FReal;
typedef int FBool;
typedef size_t FSize;
typedef time_t FTime;
typedef void FVoid;

static const FReal Focus_Auto = -1.0;
static const FReal Focus_Infinite = 0.0;

struct FUUID
{
	unsigned int A, B, C, D, E;
};

struct FAdapter
{
	FSize _ID;
	FBool _Valid;
	FReturn (* _Focus)(FTime, struct FCamera *);
	FReturn (* _Click)(struct FCamera *);
	FReturn (* _Update)(struct FCamera *);
	FReturn (* _UnMount)(struct FCamera *);
	FReturn (* _Mount)(struct FCamera *);
	FBool (* _Assert)(struct FCamera *);
	FBool (* _Detect)(FVoid);
};

struct FPlan
{
	FSize _PID, NStops, N;
	FTime TStart, TEnd, T, TDelta;
	FVoid (* BeforeClick)(struct FCamera *);
	FVoid (* AfterClick)(struct FCamera *);
	FVoid (* BeforeFocus)(struct FCamera *);
	FVoid (* AfterFocus)(struct FCamera *);
};

struct FCamera
{
	FAdapter *_Adapter;
	FBool _CONNECTED, _VALID;
	FSize Center, Upper, Lower, Left, Right, UpperLeft, UpperRight, LowerLeft, LowerRight;
	FSize _ID, _DID, WB, ISO;
	FReal A, S, MM, LW;
	FReal FPoints[CAMERA_FPOINTS_MAX];
	struct FPlan Plan;
};

FUUID _UUID();

FVoid _BeforeExitPhotoScript();

FVoid _Exception(FSize, FString , FString , FSize);
FBool _Assert_Camera(struct FCamera *);
FBool _Addert_Adapter(struct FAdapter *);

FSize _Register(struct FAdapter);
FSize _Mount(struct FAdapter *);
FSize _Detect(FVoid);

#endif