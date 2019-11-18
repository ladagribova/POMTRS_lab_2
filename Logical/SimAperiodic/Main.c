
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void _INIT ProgramInit(void)
{
	GateControl.Init=1;
	FBGateControl(&GateControl);
}

void _CYCLIC ProgramCyclic(void)
{
	FBGateControl(&GateControl);
}

void _EXIT ProgramExit(void)
{

}

