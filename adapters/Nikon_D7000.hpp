#ifndef NIKON_D7000_HPP
#define NIKON_D7000_HPP

#include <Photo_Script>

static const FSize Nikon_D7000_Adapter_ID;

FReturn Nikon_D7000_Focus(struct FCamera *Camera);
FReturn Nikon_D7000_Click(struct FCamera *Camera);
FReturn Nikon_D7000_Update(struct FCamera *Camera);
FReturn Nikon_D7000_UnMount(struct FCamera *Camera);
FReturn Nikon_D7000_Mount(struct FCamera *Camera);
FBoolean Nikon_D7000_Assert(struct FCamera *Camera);
FBoolean Nikon_D7000_Detect(FVoid);

#endif