{$MODE TP}
unit M2;

interface
	uses Common;
	
	procedure S4(var f:tg4);

implementation

	uses M1,MErr;

	procedure S8(var f:tg4);

		begin
			ProcStartWriter(f,'S8');
			Err(f);
			S1(f,Vg1);
			ProcFinishWriter(f,'S8');
		end;
		
	procedure S4;

		begin
			ProcStartWriter(f,'S4');
			Err(f);
			S8(f);
			ProcFinishWriter(f,'S4');
		end;
	

begin
	UnitStartWriter(f,'M2');
	UnitFinishWriter(f,'M2');
end.
