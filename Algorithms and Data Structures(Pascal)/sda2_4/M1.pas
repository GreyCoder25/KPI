{$MODE TP}
unit M1;

interface
	uses Common;
	
	procedure S1(var f:tg4; var bool:tg1);
	procedure S2(var f:tg4);
	procedure S3(var f:tg4);
	
implementation

	uses M2,MErr,M3;
	
	procedure S1;
		begin
			ProcStartWriter(f,'S1');
			Err(f);
			
			if bool then 
				begin
					bool:=not bool;
					append(f);
					writeln(f,Vg2,Vg1);
					close(f);
					S4(f);
				end;
			ProcFinishWriter(f,'S1');
		end;
	procedure S2;
		begin
			ProcStartWriter(f,'S2');
			Err(f);
			S5(f);
			S6(f);
			ProcFinishWriter(f,'S2');

		end;
	procedure S3;

		begin
			ProcStartWriter(f,'S3');
			Err(f);
			S7(f);
			ProcFinishWriter(f,'S3');
		end;
begin
	UnitStartWriter(f,'M1');
	UnitFinishWriter(f,'M1');
end.
	
