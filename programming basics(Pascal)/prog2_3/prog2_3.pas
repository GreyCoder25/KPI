uses crt;
type
	intfile = file of integer;
var
	f:intfile;
procedure check;
	begin
		if (ioresult <> 0) then
			begin
				clrscr;
				writeln('Файл не найден');
				halt(0);
			end;
	end;
procedure file_input(var f:intfile);
	const
		n = 40;
		m = 5;
		rand = 10;
	var
		i,j,el:word;
		x:shortint;
	begin
		{$I-}
		rewrite(f);
		{I+}
		check;
		
		randomize;
		x:=-1;
		i:=1;
		while (i <= n) do
			begin
				for j:=1 to m do
					begin
						el:=1+random(rand);
						write(f,el*x);
						{writeln('Элемент ',el*x,' был записан в файл(f)');}
					end;
				inc(i,5);
				x:=-x;
			end;
		close(f);
	end;
	
procedure file_output(var f:intfile);
	var
		r:integer;
		i:word;
	begin
		{$I-}
		reset(f);
		{I+}
		check;
		
		writeln('Компоненты файла: ');
		for i:=1 to FileSize(f) do  {while (not eof) do} {?}
			begin
				read(f,r);
				write(r:5);
			end;
		close(f);
	end;
	
procedure reflow(var f:intfile);
	const
		n = 20;
		m = 5;
	var
		r,r2:integer;
		i:byte;
	begin
		{$I-}
		reset(f);
		{I+}
		check;
		if FileSize(f) mod n <> 0 then
			begin
				writeln;
				writeln('Количество элементов файла не кратно 20-ти');
				halt(0);
			end;
		while (FilePos(f) < FileSize(f)-1) do
			begin
				writeln;
				seek(f,FilePos(f)+m);
				for i:=1 to m do
					begin
						read(f,r);
						seek(f,FilePos(f)+m-1);
						read(f,r2);
						seek(f,FilePos(f)-1);
						write(f,r);
						seek(f,FilePos(f) - (m+1));
						write(f,r2);
					end;
				seek(f,FilePos(f)+2*m)
			end;
			close(f);
			writeln('Перекомпоновка выполнена успешно');
			writeln;
	end;
		
begin
	assign(f,'input.dat');
	file_input(f);
	file_output(f);
	reflow(f);
	file_output(f);
end.
