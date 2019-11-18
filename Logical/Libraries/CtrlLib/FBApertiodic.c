
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "CtrlLib.h"
#ifdef __cplusplus
	};
#endif
/* Апериодическое Звено 2-го порядка W  = 0.1 / (0.01s^2+0.3s+1) */
void FBApertiodic(struct FBApertiodic* inst)
{
	if(inst->init){
		inst->init = 0;
		inst->xz1=0;
		inst->xz2=0;
		inst->yz1=0;
		inst->yz2=0;
		inst->x=0;
		inst->y=0;
		return;
	}
	//Z-преобразование апериодического звена для dt=0.001 c
	inst->y=(4.9503e-06)*inst->xz1+(4.9011e-06)*inst->xz2-(-1.970347019481279)*inst->yz1-(0.9704455335485083)*inst->yz2;	
	inst->xz2 = inst->xz1;
	inst->xz1 = inst->x;
	inst->yz2 = inst->yz1;
	inst->yz1 = inst->y;
}
