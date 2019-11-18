
FUNCTION_BLOCK FBApertiodic (*Апериодическое Звено 2-го порядка W  = 0.1 / (0.01s^2+0.3s+1). dt=0.001*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		x : REAL; (*Вход*)
		init : BOOL; (*Вход инициализации*)
	END_VAR
	VAR_OUTPUT
		y : REAL; (*Выход*)
	END_VAR
	VAR
		xz2 : REAL; (*xz^-2*)
		yz2 : REAL; (*yz^-2*)
		yz1 : REAL; (*yz^-1*)
		xz1 : REAL; (*xz^-1*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FBX64Ctrl (*X64 Inverter Control*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_OUTPUT
		Control : TX64Control; (*Команды управления*)
		Mapping : TX64Mapping; (*Переменные назначаемые на частоный пробразователь*)
		State : TX64State; (*Состояние*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FBGateControl (*Управление воротами*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		Init : BOOL; (*Вход инициализации*)
	END_VAR
	VAR_OUTPUT
		Leds : FBGateLed;
		X64Ctrl : FBX64Ctrl; (*Функциональный блок управления частотным преобрзователем*)
		State : TGateState; (*Состояние*)
		Mapping : TGateMapping; (*Датчики и органы управления*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FBGateLed (*Управление лампочками*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		Init : BOOL; (*Вход инициализации*)
		LedState : TGateLedState; (*Вход уставки по состоянию лампочек*)
		StatePos : TGateState;
	END_VAR
	VAR_OUTPUT
		Mapping : TGatesLeds; (*Выходы лампочек*)
	END_VAR
	VAR
		TimestampPrev : DINT; (*Метка времени для мигания*)
		Timestamp : DINT; (*Метка времени для мигания*)
		cnt_fast : INT;
		cnt_middle : INT;
		cnt_slow : INT;
	END_VAR
END_FUNCTION_BLOCK
