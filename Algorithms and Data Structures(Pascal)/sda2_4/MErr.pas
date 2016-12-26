{$MODE TP}
unit MErr;

interface
	uses Common;

	procedure Err(var f:tg4);
		
implementation

	procedure Err;

		begin
			ProcStartWriter(f,'Err');
			ProcFinishWriter(f,'Err');
		end;

begin
	UnitStartWriter(f,'MErr');
	UnitFinishWriter(f,'MErr');
end.
