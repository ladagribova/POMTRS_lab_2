#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "CtrlLib.h"
#ifdef __cplusplus
	};
#endif
/* Управление воротами */
void FBGateControl(struct FBGateControl* inst)
{
	if(inst->Init){
		inst->Init = 0;
		inst->State = ST_UNKNOWN;
		inst->X64Ctrl.Control.Init = 1;
		inst->Mapping.DirectionSwitch = 0;
		inst->Mapping.SensorClose = 0;
		inst->Mapping.SensorNearlyClose = 0;
		inst->Mapping.SensorNearlyOpen = 0;
		inst->Mapping.SensorOpen = 0;
		FBX64Ctrl(&inst->X64Ctrl);
		inst->X64Ctrl.Control.Enable = 1;
		inst->Leds.Init=1;
		FBGateLed(&inst->Leds);
		return;
	}	

	switch (inst->State){
		case ST_UNKNOWN:
			inst->Leds.LedState = GATE_LED_BBBB;
			if (inst->Mapping.DirectionSwitch == 0){	//Налево
				if(inst->Mapping.SensorClose){
					inst->State = ST_CLOSED;
					break;
				}
				if(inst->Mapping.SensorNearlyClose){
					inst->State = ST_NEARLY_CLOSED;
					break;
				}
				if(inst->Mapping.SensorNearlyOpen){
					inst->State = ST_MIDDLE;
					break;
				}
				if(inst->Mapping.SensorNearlyOpen){
					inst->State = ST_NEARLY_OPEN;
					break;
				}
				inst->X64Ctrl.Control.SetSpeed = -SPEED_LOW; 
			} else {									//Направо
				if(inst->Mapping.SensorClose){
					inst->State = ST_NEARLY_CLOSED;
					break;
				}
				if(inst->Mapping.SensorNearlyClose){
					inst->State = ST_MIDDLE;
					break;
				}
				if(inst->Mapping.SensorNearlyOpen){
					inst->State = ST_NEARLY_OPEN;
					break;
				}
				if(inst->Mapping.SensorNearlyOpen){
					inst->State = ST_OPEN;
					break;
				}
				inst->X64Ctrl.Control.SetSpeed = SPEED_LOW; 
			  }
			break;
		case ST_OPEN:
			inst->Leds.LedState = GATE_LED_oooo;
			if((inst->X64Ctrl.Control.ActSpeed>0)&&(inst->Mapping.SensorOpen==0)){
				inst->State = ST_NEARLY_OPEN;
				break;
			}
			if (inst->Mapping.DirectionSwitch == 0){	//Налево
				inst->X64Ctrl.Control.SetSpeed = -SPEED_ZERO; 				
			} else {									//Направо
				inst->X64Ctrl.Control.SetSpeed = SPEED_LOW; 				
			  }
			break;
		case ST_NEARLY_OPEN:
			inst->Leds.LedState = GATE_LED_Oooo;
			if(inst->X64Ctrl.Control.ActSpeed>0){
				if(inst->Mapping.SensorNearlyOpen){
					inst->State = ST_MIDDLE;
					break;
				}
			} else {
				if(inst->Mapping.SensorOpen){
					inst->State = ST_OPEN;
					break;
				}
              }
			if (inst->Mapping.DirectionSwitch == 0){	//Налево
				inst->X64Ctrl.Control.SetSpeed = -SPEED_LOW; 				
			} else {									//Направо
				inst->X64Ctrl.Control.SetSpeed = SPEED_LOW; 				
			  }
			break;
		case ST_MIDDLE:
			inst->Leds.LedState = GATE_LED_OOoo;
			if(inst->X64Ctrl.Control.ActSpeed>0){
				if(inst->Mapping.SensorNearlyClose){
					inst->State = ST_NEARLY_CLOSED;
					break;
				}
			} else {
				if(inst->Mapping.SensorNearlyOpen){
					inst->State = ST_NEARLY_OPEN;
					break;
				}
              }
			if (inst->Mapping.DirectionSwitch == 0){	//Налево
				inst->X64Ctrl.Control.SetSpeed = -SPEED_HIGH; 				
			} else {									//Направо
				inst->X64Ctrl.Control.SetSpeed = SPEED_HIGH; 				
			  }
			break;
		case ST_NEARLY_CLOSED:
			inst->Leds.LedState = GATE_LED_OOOo;
			if(inst->X64Ctrl.Control.ActSpeed>0){
				if(inst->Mapping.SensorClose){
					inst->State = ST_CLOSED;
					break;
				}
			} else {
				if(inst->Mapping.SensorNearlyClose){
					inst->State = ST_MIDDLE;
					break;
				}
              }
			if (inst->Mapping.DirectionSwitch == 0){	//Налево
				inst->X64Ctrl.Control.SetSpeed = -SPEED_LOW; 				
			} else {									//Направо
				inst->X64Ctrl.Control.SetSpeed = SPEED_LOW; 				
			  }
			break;
		case ST_CLOSED:
			inst->Leds.LedState = GATE_LED_OOOO;
			if((inst->X64Ctrl.Control.ActSpeed<0)&&(inst->Mapping.SensorClose==0)){
				inst->State = ST_NEARLY_CLOSED;
				break;
			}
			if (inst->Mapping.DirectionSwitch == 0){	//Налево
				inst->X64Ctrl.Control.SetSpeed = -SPEED_LOW; 				
			} else {									//Направо
				inst->X64Ctrl.Control.SetSpeed = SPEED_ZERO; 				
			  }
			break;
	}
		
	FBX64Ctrl(&inst->X64Ctrl);	
	FBGateLed(&inst->Leds);
}
