
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "CtrlLib.h"
#ifdef __cplusplus
	};
#endif
/* Управление лампочками */
void FBGateLed(struct FBGateLed* inst)
{
	if(inst->Init){
		inst->cnt_fast = 2000;
		inst->cnt_middle = 5000;
		inst->cnt_slow = 10000;
		inst->Mapping.Led1=0;
		inst->Mapping.Led2=0;
		inst->Mapping.Led3=0;
		inst->Mapping.Led4=0;
		inst->Init=0;
		inst->LedState=GATE_LED_BBBB;
		inst->Timestamp = AsIOTimeCyclicStart();;
		inst->TimestampPrev = inst->Timestamp;
		return;
	}
	
	inst->Timestamp = AsIOTimeCyclicStart();	

	switch (inst->LedState){
		case GATE_LED_BBBB:
				if((inst->Timestamp-inst->TimestampPrev)>=500000){
					inst->Mapping.Led1=!inst->Mapping.Led1;
					inst->TimestampPrev=inst->Timestamp;
				}
				inst->Mapping.Led2=inst->Mapping.Led1;
				inst->Mapping.Led3=inst->Mapping.Led1;
				inst->Mapping.Led4=inst->Mapping.Led1;
			break;
		case GATE_LED_oooo:
			inst->Mapping.Led1=0;
			inst->Mapping.Led2=0;
			inst->Mapping.Led3=0;
			inst->Mapping.Led4=0;
			break;
		case GATE_LED_Oooo:
			if(inst->StatePos = ST_NEARLY_OPEN)
			{
				inst->cnt_slow = inst->cnt_slow - 1; 
				if(inst->cnt_slow == 0)
				{
					inst->Mapping.Led1 = !inst->Mapping.Led1;
					inst->cnt_slow = 1000;
				}
			}
			inst->Mapping.Led2=0;
			inst->Mapping.Led3=0;
			inst->Mapping.Led4=0;
			break;
		case GATE_LED_OOoo:
			if(inst->StatePos = ST_MIDDLE)
			{
				inst->cnt_fast = inst->cnt_fast - 1; 
				if(inst->cnt_fast == 0)
				{
					inst->Mapping.Led1=!inst->Mapping.Led1;
					inst->Mapping.Led2=!inst->Mapping.Led2;
					inst->cnt_fast = 100;
				}
			}
			inst->Mapping.Led3=0;
			inst->Mapping.Led4=0;
			break;
		case GATE_LED_OOOo:
			if(inst->StatePos = ST_NEARLY_CLOSED)
			{
				inst->cnt_slow = inst->cnt_slow - 1; 
				if(inst->cnt_slow == 0)
				{
					inst->Mapping.Led1=!inst->Mapping.Led1;
					inst->Mapping.Led2=!inst->Mapping.Led2;
					inst->Mapping.Led3=!inst->Mapping.Led3;
					inst->cnt_slow = 1000;
				}
			}
			inst->Mapping.Led4=0;
			break;
		
		case GATE_LED_OOOO:
			inst->Mapping.Led1=0;
			inst->Mapping.Led2=0;
			inst->Mapping.Led3=0;
			inst->Mapping.Led4=0;
			break;
	}
}
