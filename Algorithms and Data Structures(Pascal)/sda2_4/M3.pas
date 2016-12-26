{$MODE TP}
unit M3;

interface
	uses Common;
	
	procedure S5(var f:tg4);
	
	procedure S6(var f:tg4);
	
	procedure S7(var f:tg4);
	
implementation

	uses MErr;
	
	procedure S5;
		begin
			ProcStartWriter(f,'S5');
			Err(f);
			ProcFinishWriter(f,'S5');
		end;
		
	procedure S6;
		begin
			ProcStartWriter(f,'S6');
			Err(f);
			ProcFinishWriter(f,'S6');
		end;
		
	procedure S7;
		begin
			ProcStartWriter(f,'S7');
			Err(f);
			S6(f);
			ProcFinishWriter(f,'S7');
		end;
begin
	UnitStartWriter(f,'M3');
	UnitFinishWriter(f,'M3');
end.
	
