{$MODE TP}
unit Common;

interface

	const
		cg1 = 45;
		cg2 = 56;
		cg3 = 47;
	type
		tg1 = boolean;
		tg2 = real;
		tg3 = integer;
		tg4 = text;
		tg5 = string;
	var
		Vg1:tg1;
		Vg2:tg5;
		f:tg4;
		
	procedure UnitStartWriter(var PrF:tg4; name:string);

	procedure UnitFinishWriter(var PrF:tg4; name:string);

	procedure ProcStartWriter(var PrF:tg4; name:string);

	procedure ProcFinishWriter(var PrF:tg4; name:string);

		
implementation

	procedure UnitStartWriter;
		var
			r:string;
		begin
			r:=' initialization started';
			append(f);
			writeln(f,name,r);
			close(f);
		end;
		
	procedure UnitFinishWriter;
		var
			r:string;
		begin
			r:=' initialization finished';
			append(f);
			writeln(f,name,r);
			close(f);
		end;
		
	procedure ProcStartWriter;
		var
			r1,r2:string;
		begin
			r1:='procedure ';
			r2:=' started';
			append(f);
			writeln(f,r1,name,r2);
			close(f);
		end;
		
	procedure ProcFinishWriter;
		var
			r1,r2:string;
		begin
			r1:='procedure ';
			r2:=' finished';
			append(f);
			writeln(f,r1,name,r2);
			close(f);
		end;
	
begin
	assign(f,'protocol.txt');
	rewrite(f);
	
	UnitStartWriter(f,'Common');
	Vg1:=true;
	Vg2:=' Vg1 = ';
	append(f);
	writeln(f,Vg2,Vg1);
	close(f);
	UnitFinishWriter(f,'Common');
end.
