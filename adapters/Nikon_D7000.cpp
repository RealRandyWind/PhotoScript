#include <Nikon_D7000>

/* Include Nikon headers */

FReturn Nikon_D7000_Focus(struct FCamera *Camera)
{
	if(!_Assert_Camera(Camera))
	{
		return Failure;
	}

	return Success;
}

FReturn Nikon_D7000_Click(struct FCamera *Camera)
{
	if(!_Assert_Camera(Camera))
	{
		return Failure;
	}

	return Success;
}

FReturn Nikon_D7000_Update(struct FCamera *Camera)
{
	if(!_Assert_Camera(Camera))
	{
		return Failure;
	}

	return Success;
}

FReturn Nikon_D7000_UnMount(struct FCamera *Camera)
{
	if(!_Assert_Camera(Camera))
	{
		return Failure;
	}

	return Success;
}

FReturn Nikon_D7000_Mount(struct FCamera *Camera)
{
	if(!Camera)
	{
		return Failure;
	}

	return Success;
}

FBool Nikon_D7000_Assert(struct FCamera *Camera)
{
	if(!Camera)
	{
		return False;
	}

	return True;
}

FBool Nikon_D7000_Detect(FVoid)
{
	return True;
}

struct FAdapter Nikon_D7000(FVoid)
{
	FAdapter Adapter;

	Adapter._Valid = False;
	Adapter._Focus = Nikon_D7000_Focus;
	Adapter._Click = Nikon_D7000_Click;
	Adapter._Update = Nikon_D7000_Update;
	Adapter._UnMount = Nikon_D7000_UnMount;
	Adapter._Mount = Nikon_D7000_Mount;
	Adapter._Assert = Nikon_D7000_Assert;
	Adapter._Detect = Nikon_D7000_Detect;
	Adapter._ID = None;
	return Adapter;
}

static const FUUID Version_ID = _UUID();
static const FSize Nikon_D7000_Adapter_ID = _Register(Nikon_D7000());