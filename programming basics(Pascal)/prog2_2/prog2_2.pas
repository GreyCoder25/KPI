uses crt;
type
	wfile = file of word;
var
	f,g:wfile;
procedure check;
	begin
		if (IOResult <> 0) then
			begin
				clrscr;
				writeln('Один из указанных файлов не найден');
				halt(0);
			end;
	end;
procedure filling(var f:wfile);
	const
		n:word = 50;
	var
		i:word;
	begin
		{$I-}
		rewrite(f);
		{I+}
		check;
		for i:=1 to n do 
			begin
				write(f,2*i);
				writeln('Number ',2*i,' was written to the file(f)');
			end;
		
		close(f);
	end;
procedure file_output(var f:wfile);
	var
		r:word;
	begin
		
		{$I-}
		reset(f);
		{I+}
		check;
		writeln;
		writeln('Components of the file:');
		
		while (not eof(f)) do
			begin
				read(f,r);
				write(r,'--');
			end;
		
		writeln;
		writeln;	
		close(f);	
	end;
procedure perf_squares(var f,g:wfile);
	var
		r:word;
	begin
		{$I-}
		reset(f);
		rewrite(g);
		{I+}
		check;
		while (not eof(f)) do
			begin
				read(f,r);
				if (sqrt(r) - trunc(sqrt(r)) = 0) then
					begin
						write(g,r);
						writeln('Number ',r,' was written to the file(g)');
					end;
			end;

		close(f);
		close(g);

	end;

begin
	assign(f,'prog2_2_input.dat');
	filling(f);
	file_output(f);

	assign(g,'prog2_2_output.dat');
	perf_squares(f,g);
	file_output(g);
end.
