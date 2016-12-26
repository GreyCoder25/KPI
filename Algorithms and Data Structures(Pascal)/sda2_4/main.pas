{$MODE TP}
program main;

uses M1,Common;

const
	message1:string = 'Main started';
	message2:string = 'Main finished';
begin
	append(f);
	writeln(f,message1);
	close(f);
	S1(f,Vg1);
	S2(f);
	S3(f);
	append(f);
	writeln(f,message2);
	close(f);
end.
