#include <Photo_Script>

static FSize _CameraCount = 0;
static struct FCamera Cameras[CAMERA_MAX];

static FSize _AdapterCount = 0;
static struct FAdapter _Adapters[ADAPTER_MAX];

FVoid _BeforeExitPhotoScript()
{
	/*cleanup everything */
}

FVoid _Exception(FSize Code, FString Function, FString File, FSize Line);
{
	printf("Exception(%d.%d) at \"%s\" in file \"%s\" line %d\n", 
		Code & Exception_TypeMask, 
		Code & Exception_CodeMask, 
		Function, File, Line);
	
	if(Code & Exception_ExitMask)
	{
		_BeforeExitPhotoScript();
		exit(EXIT_FAILURE);
	}
}

FUUID _UUID()
{
	FUUID ID;

	ID.A = ID.B = ID.C = ID.D = ID.E = 0;
	return ID;
}

FBool _Assert_Camera(struct FCamera *Camera)
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

FBool _Assert_Adapter(struct FAdapter *Adapter)
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
	if (_AdapterCount < ADAPTER_MAX)
	{
		_Trow_Exception(0);
		return ADAPTER_MAX;
	}

	if(!_Assert_Adapter(&Adapter))
	{
		return ADAPTER_MAX;
	}

	Adapter._ID = _AdapterCount;
	_Adapters[_AdapterCount] = Adapter;
	return _AdapterCount++;
}

FSize _Mount(struct FAdapter *Adapter)
{
	if(_CameraCount < CAMERA_MAX)
	{
		_Trow_Exception(0);
		return CAMERA_MAX;
	}

	if(!Adapter._Valid)
	{
		_Trow_Exception(0);
		return CAMERA_MAX;
	}

	if(Adapter._Mount(&Cameras[_CameraCount]) < Success)
	{
		_Trow_Exception(0);
		return CAMERA_MAX;
	};

	Cameras[_CameraCount]._ID = _CameraCount;
	return _CameraCount++;
}

FSize _Detect(FVoid)
{
	return CAMERA_MAX;
}