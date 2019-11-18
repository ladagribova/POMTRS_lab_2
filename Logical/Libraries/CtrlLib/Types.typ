
TYPE
	TX64Mapping : 	STRUCT 
		RFRD_Input : INT; (*Вход RFRD*)
		LFRD_Output : INT; (*Выход LFRD*)
		CMDD_Output : UINT; (*Выход CMDD*)
		ETAD_Input : UINT; (*Вход ETAD*)
	END_STRUCT;
	TX64State : 
		(
		STATE_NOT_READY_TO_SWITCH_ON := 0,
		STATE_SWITCH_ON_DISABLED := 64,
		STATE_READY_TO_SWITCH_ON := 33,
		STATE_SWITCHED_ON := 35,
		STATE_OPERATION_ENABLED := 39
		);
	TX64Command : 
		(
		CMD_DISABLE_VOLTAGE := 0,
		CMD_SHUTDOWN := 6,
		CMD_SWITCH_ON := 7,
		CMD_ENABLE_OPERATION := 15
		);
	TX64Control : 	STRUCT 
		Init : BOOL; (*Команда на инициализацию*)
		Enable : BOOL; (*Разрешение на работу*)
		ActSpeed : REAL; (*Актуальная скорость*)
		SetSpeed : REAL; (*Уставка по скорости*)
	END_STRUCT;
	TGateState : 
		(
		ST_UNKNOWN,
		ST_OPEN,
		ST_NEARLY_OPEN,
		ST_MIDDLE,
		ST_NEARLY_CLOSED,
		ST_CLOSED
		);
	TGateLedState : 
		(
		GATE_LED_BBBB,
		GATE_LED_oooo,
		GATE_LED_Oooo,
		GATE_LED_OOoo,
		GATE_LED_OOOo,
		GATE_LED_OOOO
		);
	TGatesLeds : 	STRUCT 
		Led1 : BOOL;
		Led2 : BOOL;
		Led3 : BOOL;
		Led4 : BOOL;
	END_STRUCT;
	TGateMapping : 	STRUCT 
		DirectionSwitch : BOOL;
		SensorOpen : BOOL;
		SensorNearlyOpen : BOOL;
		SensorNearlyClose : BOOL;
		SensorClose : BOOL;
	END_STRUCT;
END_TYPE
