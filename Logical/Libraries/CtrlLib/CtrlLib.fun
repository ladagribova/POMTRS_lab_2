
FUNCTION_BLOCK FBApertiodic (*�������������� ����� 2-�� ������� W  = 0.1 / (0.01s^2+0.3s+1). dt=0.001*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		x : REAL; (*����*)
		init : BOOL; (*���� �������������*)
	END_VAR
	VAR_OUTPUT
		y : REAL; (*�����*)
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
		Control : TX64Control; (*������� ����������*)
		Mapping : TX64Mapping; (*���������� ����������� �� �������� ��������������*)
		State : TX64State; (*���������*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FBGateControl (*���������� ��������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		Init : BOOL; (*���� �������������*)
	END_VAR
	VAR_OUTPUT
		Leds : FBGateLed;
		X64Ctrl : FBX64Ctrl; (*�������������� ���� ���������� ��������� ���������������*)
		State : TGateState; (*���������*)
		Mapping : TGateMapping; (*������� � ������ ����������*)
	END_VAR
END_FUNCTION_BLOCK

FUNCTION_BLOCK FBGateLed (*���������� ����������*) (*$GROUP=User,$CAT=User,$GROUPICON=User.png,$CATICON=User.png*)
	VAR_INPUT
		Init : BOOL; (*���� �������������*)
		LedState : TGateLedState; (*���� ������� �� ��������� ��������*)
		StatePos : TGateState;
	END_VAR
	VAR_OUTPUT
		Mapping : TGatesLeds; (*������ ��������*)
	END_VAR
	VAR
		TimestampPrev : DINT; (*����� ������� ��� �������*)
		Timestamp : DINT; (*����� ������� ��� �������*)
		cnt_fast : INT;
		cnt_middle : INT;
		cnt_slow : INT;
	END_VAR
END_FUNCTION_BLOCK
