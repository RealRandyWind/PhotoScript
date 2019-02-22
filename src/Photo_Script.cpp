#include <stdlib.h>
#include <stdio.h>

#include <Photo_Script>

#define EXCEPTION_MSG_DDSSD "Exception(%d.%d) at \"%s\" in file \"%s\" line %d\n"

static FSize _CameraCount = 0;
static FSize _CameraID = 0;
static struct FCamera _Cameras[CAMERA_MAX] = {{None}};

static FSize _AdapterCount = 0;
static FSize _AdapterID = 0;
static struct FAdapter _Adapters[ADAPTER_MAX] = {{None}};

FVoid _BeforeExit()
{
	/*cleanup everything */
}

FVoid _Exception(FSize Code, FString Function, FString File, FSize Line)
{
	printf(EXCEPTION_MSG_DDSSD, 
		Code & EXCEPTION_TYPEMASK,
		Code & EXCEPTION_CODEMASK,
		Function, File, Line);
	
	if(Code & EXCEPTION_EXITMASK)
	{
		_BeforeExit();
		exit(EXIT_FAILURE);
	}
}

FUUID _UUID()
{
	FUUID ID;
	FSize Index, End;

	End = HASH_SIZE;
	for(Index = Start; Index < End; ++Index)
	{
		ID.Hash[Index] = None;
	}
	return ID;
}

FBoolean _Assert_Camera(struct FCamera *Camera)
{
	if(!Camera)
	{
		_Trow_Exception(0);
		return False;
	}

	Camera->_Valid = False;

	if(!Camera->_Adapter)
	{
		_Trow_Exception(0);
		return False;
	}

	/* assert existance */
	if(!Camera->_Adapter->_Assert(Camera))
	{
		_Trow_Exception(0);
		return False;
	}

	Camera->_Valid = True;
	return Camera->_Valid;
}

FBoolean _Assert_Adapter(struct FAdapter *Adapter)
{
	if(!Adapter)
	{
		_Trow_Exception(0);
		return False;
	}

	Adapter->_Valid = False;

	if(!Adapter->_Focus)
	{
		_Trow_Exception(0);
		return False;
	}

	if(!Adapter->_Click)
	{
		_Trow_Exception(0);
		return False;
	}

	if(!Adapter->_Update)
	{
		_Trow_Exception(0);
		return False;
	}

	if(!Adapter->_UnMount)
	{
		_Trow_Exception(0);
		return False;
	}

	if(!Adapter->_Mount)
	{
		_Trow_Exception(0);
		return False;
	}

	if(!Adapter->_Assert)
	{
		_Trow_Exception(0);
		return False;
	}

	if(!Adapter->_Detect)
	{
		_Trow_Exception(0);
		return False;
	}

	Adapter->_Valid = True;
	return Adapter->_Valid;
}

FSize _Register(struct FAdapter Adapter)
{
	if(_AdapterCount < ADAPTER_MAX)
	{
		_Trow_Exception(0);
		return ADAPTER_MAX;
	}

	if(!_Assert_Adapter(&Adapter))
	{
		return ADAPTER_MAX;
	}

	Adapter._ID = _AdapterID;
	_Adapters[Adapter._ID] = Adapter;
	_AdapterID = _AdapterID < ++_AdapterCount
		? _Adapters[_AdapterID]._ID
		: _AdapterCount;
	return Adapter._ID;
}

FSize _Mount(struct FAdapter *Adapter)
{
	FSize CameraID;

	if(_CameraCount < CAMERA_MAX)
	{
		_Trow_Exception(0);
		return CAMERA_MAX;
	}

	if(!Adapter->_Valid)
	{
		_Trow_Exception(0);
		return CAMERA_MAX;
	}

	if(Adapter->_Mount(&_Cameras[_CameraCount]) < Success)
	{
		_Trow_Exception(0);
		return CAMERA_MAX;
	}

	CameraID = _CameraID;
	_Cameras[CameraID]._ID = CameraID; 
	_CameraID = _CameraID < ++_CameraCount
		? _Cameras[CameraID]._ID
		: _CameraCount;
	return CameraID;
}

FSize _Detect(FVoid)
{
	return CAMERA_MAX;
}