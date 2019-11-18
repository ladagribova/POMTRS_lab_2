
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "CtrlLib.h"
#ifdef __cplusplus
	};
#endif
/* X64 Inverter Control */
void FBX64Ctrl(struct FBX64Ctrl* inst)
{
	if(inst->Control.Init){
		inst->State=STATE_NOT_READY_TO_SWITCH_ON;
		inst->Control.ActSpeed=0;
		inst->Control.Enable=0;
		inst->Control.SetSpeed=0;
		inst->Mapping.CMDD_Output=0;
		inst->Mapping.LFRD_Output=0;
		inst->Mapping.ETAD_Input=0;
		inst->Mapping.RFRD_Input=0;
		inst->Control.Init=0;		
		return;
	}
	
	inst->State=inst->Mapping.ETAD_Input & 0x006F;
	inst->Control.ActSpeed = inst->Mapping.RFRD_Input;
	inst->Control.ActSpeed = inst->Control.ActSpeed/60.0*2.0*3.1415926;
	
	if(!inst->Control.Enable){
		inst->Mapping.CMDD_Output = CMD_DISABLE_VOLTAGE;		
		inst->Mapping.LFRD_Output=0;
	} else {
		switch(inst->State)
		{
			case STATE_NOT_READY_TO_SWITCH_ON:
				break;
			case STATE_SWITCH_ON_DISABLED:	
				inst->Mapping.CMDD_Output = CMD_SHUTDOWN;
				inst->Mapping.LFRD_Output=0;
				break;
			case STATE_READY_TO_SWITCH_ON:
				inst->Mapping.CMDD_Output = CMD_SWITCH_ON;	
				inst->Mapping.LFRD_Output=0;
				break;
			case STATE_SWITCHED_ON:
				inst->Mapping.CMDD_Output = CMD_ENABLE_OPERATION;
				inst->Mapping.LFRD_Output=0;
				break;
			case STATE_OPERATION_ENABLED:
				inst->Mapping.LFRD_Output=inst->Control.SetSpeed*60.0/(2.0*3.1415926);
				break;
		}
	}		
}

