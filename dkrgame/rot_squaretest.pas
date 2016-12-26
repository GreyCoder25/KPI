{$MODE TP}
uses ptcGraph,ptcCrt;
const
	size = 4;
type
	cell = record //запись, которая описывает одну клетку игрового поля
		selected:boolean;//является ли клетка выбранной
		letter:char;//буква на клетке
		CoordX,CoordY:word;//координаты буквы
	end;{cell}
	
type
	indicator = record
		i,j:byte;
	end;
	
	matrix = array [1..size,1..size] of cell; //игровая таблица (1)
var
	Driver,Mode:integer;
	MainMatrix:matrix;
	ulcell:indicator;

procedure GraphInit(var Driver,Mode:integer);//инициализация графического режима
	begin
		Driver:=VGA;   //адаптер VGA
		Mode:=VGAHi;   //режим 640*480пикс.*16 цветов
	
		writeln('Драйвер: ', Driver, ', Графический режим: ', Mode);
		InitGraph(Driver, Mode,'');
		WriteLn('Разрешение: ', GetMaxX+1,'x',GetMaxY+1, ', Цветов: ', GetMaxColor+1);
	end;{GraphInit}
	
procedure MainMatrixInit(var A:matrix; w:char);//инициализация игровой таблицы (1)
	const
		NumLet = 16;
	type
		ArrLet = array [0..NumLet-1] of char;//массив (2) для заполнения таблицы 
	var
		AccArray:ArrLet;
		//ulcell:indicator;
		
	procedure ArrLetInit(var arr:ArrLet);//инициализация массива (2)
		var
			i:byte;
			letter:char;
		begin
			letter:='A';
			for i:=0 to NumLet-1 do
				begin
					arr[i]:=letter;
					letter:=chr(ord(letter)+1);
					write(arr[i],' ');
				end;
			writeln;
			writeln;
		end;{ArrLetInit}
		

	procedure swap(var arr:ArrLet; i,j:byte);//обмен местами двух элементов массива
		var
			temp:char;
		begin
			temp:=arr[i];
			arr[i]:=arr[j];
			arr[j]:=temp;
		end;{swap}
		
	procedure CellValuesInit(var A:matrix; const V:ArrLet);//инициализация букв соответствующих клеткам таблицы
		const
			size = 4;
			NumLet = 16;
		var
			i,j,k,lim:byte;
		begin
			lim:=NumLet;
			ArrLetInit(AccArray);
			randomize;
		
			for i:=1 to size do
				begin
					for j:=1 to size do
						begin
							k:=random(lim);
							A[i,j].letter:=AccArray[k];
							swap(AccArray,k,lim-1);
							dec(lim);
							write(A[i,j].letter,' ');
						end;
					writeln;
				end;
		end;{CellValuesInit}
		
	procedure CellValuesTestInit(var A:matrix; const V:ArrLet);

		begin

			A[1,1].letter:='B'; A[1,2].letter:='F'; A[1,3].letter:='C'; A[1,4].letter:='D';
			A[2,1].letter:='A'; A[2,2].letter:='E'; A[2,3].letter:='G'; A[2,4].letter:='H';
			A[3,1].letter:='I'; A[3,2].letter:='J'; A[3,3].letter:='K'; A[3,4].letter:='L';
			A[4,1].letter:='M'; A[4,2].letter:='N'; A[4,3].letter:='O'; A[4,4].letter:='P';
						
		end;{CellValuesInit}
		
	procedure CellCoordInit(var A:matrix);//инициализация координат
		const
			ExtX = 50;
			ExtY = 50;
			step = 100;
			size = 4;
		var
			x,y:word;
			i,j:byte;
		begin
			
			y:=ExtY;
			
			for i:=1 to size do
				begin
					x:=ExtX;
					for j:=1 to size do
						begin
							A[i,j].CoordX:=x;
							write('[',x,',');
							A[i,j].CoordY:=y;
							write(y,'] ');
							inc(x,step);
						end;
				inc(y,step);
				writeln;
				end;
		end;{CellCoordInit}
		
	procedure CellSelectInit(var A:matrix);//инициализация булевых значений выделения клеток таблицы
		const
			size = 4;
		var
			i,j:byte;
		begin
			for i:=1 to size do
				for j:=1 to size do
					A[i,j].selected:=FALSE;
		end;{CellSelectInit}
	procedure CellIndInit(var ind:indicator; i,j:byte);
		begin
			ind.i:=i;
			ind.j:=j;
		end;{CellIndInit}
		
	begin
		case w of
			's':CellValuesInit(MainMatrix,AccArray);
			't':CellValuesTestInit(MainMatrix,AccArray);
		end;
		
		CellCoordInit(MainMatrix);
		CellSelectInit(MainMatrix);
		CellIndInit(ulcell,1,1);
	end;{MainMatrixInit}
	
procedure GameWindow(var A:matrix; var fw:boolean);//главное окно игры
	const
		TextColor = 5;
		BkColor = 15;
		size = 4;
		sw:boolean = TRUE;
	var
		ex:boolean;
					
		procedure UserControl(var A:matrix; size:byte; var ind:indicator;var ex:boolean);
			var
				key:char;
				
			procedure clearselect(var A:matrix; indi,indj:byte);//убирает выделение
				var
					i,j:byte;
				begin
					for i:=indi to indi+1 do
						for j:=indj to indj+1 do
							begin
								A[i,j].selected:=FALSE;
							end;
				end;{clearselect}
			
			procedure rotate(var A:matrix; i,j: byte);//вращение букв (по часовой стрелке)
				var
					temp:char;
				begin
					temp:=A[i,j].letter;
					A[i,j].letter:=A[i+1,j].letter;
					A[i+1,j].letter:=A[i+1,j+1].letter;
					A[i+1,j+1].letter:=A[i,j+1].letter;
					A[i,j+1].letter:=temp;
				end;{rotate}
				
			procedure FindElem(const A:matrix; size:byte; letter:char; var x,y:byte);
				var
					i,j:byte;
					indi,indj:byte;
				label	
					f;
				begin
					indi:=0; indj:=0;

					if letter <> ' ' then 
						begin
							for i:=1 to size do
								for j:=1 to size do
									if A[i,j].letter = letter then
										begin
											indi:=i;
											indj:=j;
											goto f;
										end;
							f:
							x:=indj; y:=indi;
						end;
				end;{FindElem}
				
			procedure KeybCoordInput(var A:matrix;var coord:byte; x,y:word);//реализует ввод значений координат с клавиатуры
				var
					sinp:byte;
					key:char;		
					flag:boolean;
					
				begin
						flag:=TRUE;//флажок который показывает, можно ли вводить еще символ
						writeln('Input started');
						
						SetColor(LightRed);
						rectangle(x-2,y-5,x+58,y+35);
						
					repeat
						//строке ввода присваивается начальное значение 
						SetColor(red);//установка цвета вводимых символов
						SetTextStyle(0,0,4);//стиль ввода текста
						
						key:=readkey;//считывание нажатия клавиши
						
						if key in [#27,#13] then break;
				
						if key = #8 then//если нажатая клавиша - 'BackSpace', то 
							begin
								SetColor(white);//цвет закрашивания - белый
								OutTextXY(x+10,y,#219);//закрасить введенный символ
								flag:=TRUE;//вводить можно
							end
						else
							begin
								if flag then//если вводить можно, то 
									begin
										SetColor(red);//установить красный, как цвет ввода
										if key in [#49,#50,#51] then 
											begin
												OutTextXY(x+10,y,key);//если введенный символ от '1' до '3', то
																	  //вывести его на экран	
												flag:=FALSE;//вводить больше нельзя
											end;
									end;
							end;
						
						sinp:=ord(key)-48;
				
					until(FALSE);//пока пользователь не нажмет 'Enter'	
						writeln('sinp = ',sinp);
					if key = #13 then
						begin
							clearselect(A,ind.i,ind.j);//убирается предыдущее выделение ячеек
							coord:=sinp;//координата окна вращения становится равна введенному значению
						end;
					writeln('Input finished');
				end;{KeyCoordInput}
				
			procedure KeybLetInput(var ch:char; x,y:word);//реализует ввод значений букв с клавиатуры
				var
					key:char;
					flag:boolean;
					
				begin
						flag:=TRUE;//флажок который показывает, можно ли вводить еще символ
						ch:=' ';
						writeln('Input started');
						
						SetColor(LightRed);
						rectangle(x-2,y-5,x+58,y+35);
						
					repeat

						SetColor(red);//установка цвета вводимых символов
						SetTextStyle(0,0,4);//стиль ввода текста
						
						key:=readkey;//считывание нажатия клавиши
						
						if key = #27 then break;
				
						if key = #8 then//если нажатая клавиша - 'BackSpace', то 
							begin
								SetColor(white);//цвет закрашивания - белый
								OutTextXY(x+10,y,#219);//закрасить введенный символ
								flag:=TRUE;//вводить можно
							end
						else
							begin
								if flag then//если вводить можно, то 
									begin
										SetColor(red);//установить красный, как цвет ввода
										if key in [#97..#112] then 
											begin
												OutTextXY(x+10,y,chr(ord(key)-32));//если введенный символ от '1' до '3', то
																				   //вывести его на экран
												ch:=key;	
												flag:=FALSE;//вводить больше нельзя
											end;
									end;
							end;
						
					until(key = #13);//пока пользователь не нажмет 'Enter'
					writeln('Input finished');
					
				end;{KeybLetInput}
				
			procedure FindAndSwap(var A:matrix; size:byte; ch1,ch2:char;var f:boolean);
				var
					x1,y1,x2,y2:byte;
				begin
					ch1:=chr(ord(ch1)-32);
					ch2:=chr(ord(ch2)-32);
					FindElem(A,size,ch1,x1,y1);
					FindElem(A,size,ch2,x2,y2);
					if ch2 <> ' ' then
						begin
							A[y1,x1].letter:=ch2;
							A[y2,x2].letter:=ch1;
							f:=FALSE
						end;
					
				end;{LetterSwap}
			
			procedure SwapLetters(var A:matrix;var f:boolean);
				const
					size = 4;
				var
					ch1,ch2:char;
				begin
					KeybLetInput(ch1,447,120);
					KeybLetInput(ch2,552,120);
					FindAndSwap(A,size,ch1,ch2,f);
				end;
				
			procedure CheckWin(const A:matrix; size:byte; var win:boolean);
				var
					i,j,count:byte;
					compch:char;
				begin
					count:=0;
					compch:='A';
				
					for i:=1 to size do
						for j:=1 to size do
							begin
								if A[i,j].letter = compch then inc(count);
								compch:=chr(ord(compch)+1);
							end;
				
					if count = 16 then win:=TRUE;
				end;

			
			begin
				key:=readkey;
			
				case key of
					#27:ex:=TRUE;
					
					#75:if (ind.j > 1) then  //клавиша "стрелка влево"
							begin
								clearselect(A,ind.i,ind.j);
								dec(ind.j);
								writeln(ind.i,'-',ind.j);	
								
							end;
							
					#77:if (ind.j < size-1) then //клавиша "стрелка вправо"
							begin
								clearselect(A,ind.i,ind.j);
								inc(ind.j);
								writeln(ind.i,'-',ind.j);
											
							end;
					 	
					#72:if (ind.i > 1) then  //клавиша "стрелка вверх"
							begin
								clearselect(A,ind.i,ind.j);
								dec(ind.i);
								writeln(ind.i,'-',ind.j);	
								
							end;
							
					#80:if (ind.i < size-1) then  //клавиша "стрелка вниз"
							begin
								clearselect(A,ind.i,ind.j);
								inc(ind.i);
								writeln(ind.i,'-',ind.j);	
								
							end;
							
					#32:begin
							rotate(A,ind.i,ind.j); // клавиша 'Space' - вращать буквы(по часовой стрелке)
							CheckWin(A,4,fw);
							writeln('rotate, fw = ',fw);
						end; 
					
					#97:begin								// клавиша - вызвать ввод координат с клавиатуры
							KeybCoordInput(A,ind.i,447,120);
							KeybCoordInput(A,ind.j,552,120);
							CheckWin(A,4,fw);
						end;
					#98:if sw then
							begin
								SwapLetters(A,sw);
								CheckWin(A,4,fw);
							end;
				end;{case}

			end;{UserControl}
			
		procedure DynElemDraw(var A:matrix; size:byte; var ind:indicator);
				
			var
				i,j,k:byte;
				
			procedure InputField(x1,y1:word; l,h:byte; color:byte);//рисует поле для ввода
				const
					n = 15;
				var
					InpFB:array [1..10] of word;
					InpFL:array [1..10] of word;
				begin                                           
					SetColor(blue);
					InpFB[1]:=x1;InpFB[2]:=y1;InpFB[3]:=x1+l;InpFB[4]:=y1;InpFB[5]:=x1+l;
					InpFB[6]:=y1+h;InpFB[7]:=x1;InpFB[8]:=y1+h;InpFB[9]:=x1;InpFB[10]:=y1;
					
					InpFL[1]:=x1+n;InpFL[2]:=y1+n;InpFL[3]:=x1+l-n;InpFL[4]:=y1+n;InpFL[5]:=x1+l-n;
					InpFL[6]:=y1+h-n;InpFL[7]:=x1+n;InpFL[8]:=y1+h-n;InpFL[9]:=x1+n;InpFL[10]:=y1+n;
					
					rectangle(x1,y1,x1+l,y1+h);
					rectangle(x1+n,y1+n,x1+l-n,y1+h-n);
				
					SetFillStyle(1,lightgray);
					FillPoly(5,InpFB);
					
					SetFillStyle(1,white);
					FillPoly(5,InpFL);
				end;{InputField}
				
			begin
				SetLineStyle(SolidLn,0,ThickWidth);
				
				InputField(430,100,90,70,7);
				InputField(535,100,90,70,7);
				
				SetColor(red);
					
				//столбцы
				Line(A[1,1].CoordX - 30, A[1,1].CoordY - 30, A[size,1].CoordX - 30, A[size,1].CoordY + 60);
			
				for i:=1 to size-1 do
					Line( (A[1,i].CoordX + A[1,i+1].CoordX + 28)div 2, A[1,1].CoordY-30, (A[1,i].CoordX + A[1,i+1].CoordX + 28)div 2, A[size,1].CoordY+60 );
					
				Line(A[1,size].CoordX + 65,A[1,1].CoordY-30, A[1,size].CoordX + 65, A[size,1].CoordY + 60);
			
				//строки
				Line(A[1,1].CoordX - 30, A[1,1].CoordY - 30, A[1,size].CoordX + 65, A[1,1].CoordY - 30);
			
				for i:=1 to size-1 do
					Line( A[1,1].CoordX - 30, (A[i,1].CoordY + A[i+1,1].CoordY + 30)div 2, A[1,size].CoordX + 65, (A[i,1].CoordY + A[i+1,1].CoordY + 30)div 2 );
				
				Line(A[1,1].CoordX - 30, A[size,1].CoordY + 60, A[1,size].CoordX + 65, A[size,1].CoordY + 60);
			
				//выделение

				for i:=ind.i to ind.i+1 do
					for j:=ind.j to ind.j+1 do
						A[i,j].selected:=TRUE;

				for i:=1 to size do
					for j:=1 to size do
						if A[i,j].selected then
							begin
								SetFillStyle(1,green);
								SetColor(lightred);
									for k:=0 to 15 do
										rectangle(A[i,j].CoordX-10-k, A[i,j].CoordY-10-k,A[i,j].CoordX+40+k, A[i,j].CoordY+40+k);
								
							end;
				//буквы
				SetColor(cyan);
				SetTextStyle(0,0,4);
				
				for i:=1 to size do
					for j:=1 to size do
						OutTextXY(A[i,j].CoordX,A[i,j].CoordY,A[i,j].letter);
			end;{DynElemDraw}
			
	begin
		sw:=TRUE;
		repeat	
			ex:=FALSE;
		
			cleardevice;
			SetBkColor(BkColor);
			SetColor(TextColor);
			DynElemDraw(A,size,ulcell);
			UserControl(A,size,ulcell,ex);
			if ex or fw then
				begin
					//Delay(500);
					break;
				end;

		until(FALSE);
	end;{GameWindow}
	
procedure WinWindow;

	begin
		writeln('WinWindow started');
		SetBkColor(white);
		cleardevice;
		SetColor(Red);
		SetTextStyle(0,0,16);
		OutTextXY(100,100,'WIN!');
		
		SetTextStyle(7,0,3);
		SetColor(green);
		OutTextXY(100,400,'press "Enter" to try once more');
		OutTextXY(100,420,'press "Esc" to return Menu');
	
	end;

procedure Rules;
	var
		xout,yout:word;
		key:char;
	procedure DelayedOutput(tekst:string; x,y:word);
		var
			i:byte;
			
		begin

			SetTextStyle(1,0,1);
			
			for i:=1 to length(tekst) do
				begin
					OutTextXY(x,y,tekst[i]);
					delay(10);
					if x > 600 then
						begin
							x:=10;
							inc(y,20);
						end
					else inc(x,16);
				end;			
		end;
	begin
		cleardevice;
		
		xout:=40;
		yout:=15;
		
		DelayedOutput('You have to regularize letters in the matrix.',xout,yout);
		xout:=40;
		inc(yout,95);
		DelayedOutput('Use arrows',xout,yout);
		
		rectangle(250,90,290,130); Line(255,110,285,110); Line(255,110,260,105); Line(255,110,260,115);
		rectangle(290,90,330,130); Line(310,95,310,125);  Line(310,125,305,120); Line(310,125,315,120);
		rectangle(330,90,370,130); Line(335,110,365,110); Line(365,110,360,105); Line(365,110,360,115);
		rectangle(290,50,330,90);  Line(310,55,310,85);   Line(310,55,305,60);   Line(310,55,315,60);
		
		DelayedOutput('to move releasing square or input its coordinates into special input fields(press "a" to start input, press "Enter" to fix the value).',400,110);
		
		xout:=100;
		inc(yout,80);
		DelayedOutput('Press "Space" to rotate 4 highlighted letters.',xout,yout);
		xout:=40;
		inc(yout,60);
		DelayedOutput('You can also swap two letters once writing them into the input fields (press "b"). Press "Esc" to exit from game or "Rules" to Menu.',xout,yout);
		SetBkColor(black);
		
		key:=readkey;		
		if key = #27 then exit;//выход в меню
			
	end;
	
procedure Menu;
	const
        numofelem=4;
    type
        menuel = record
           elx:word;
           ely:word;
           eltext:string;
           eltetxstyle:0..9;
           elchcolor:1..15;
           elnum:1..10;
        end;

    var
       menuels:array [1..4] of menuel;
       i:byte;
       currentel:0..numofelem+1;
       key:char;
       fw:boolean;

    begin
       with menuels[1] do 
		   begin
            elx:=230;
            ely:=150;
            eltext:='Play';
            elchcolor:=10;
           end;
       with menuels[2] do 
		   begin
            elx:=230;
            ely:=190;
            eltext:='Test Mode';
            elchcolor:=10;
           end;
       with menuels[3] do 
           begin
            elx:=230;
            ely:=230;
            eltext:='Rules';
            elchcolor:=10;
           end;
       with menuels[4] do 
		   begin
            elx:=230;
            ely:=270;
            eltext:='Exit';
            elchcolor:=10;
           end;
       

       currentel:=1;
       fw:=FALSE;
     
       repeat
			 SetBkColor(black);
             cleardevice;
             
             SetTextStyle(7,HorizDir,4);
             SetLineStyle(0,0,3);

             for i:=1 to numofelem do
				begin
				
                 with menuels[i] do 
					begin

					if (i=currentel) then
						begin
							menuels[i].elchcolor:=lightblue;
                        end
                    else
                        menuels[i].elchcolor:=lightgreen;
                    SetColor(elchcolor);
                    
                    elnum:=i;
                    OutTextXY(elx,ely,eltext);
		
					end;
				end;
				
			if fw then 
				begin
					WinWindow;
					writeln('here');
					key:=readkey;
					case key of 
						#13:begin
								writeln('fw = ',fw);
								fw:=FALSE;
								key := #13;
							end;
						#27:begin
								fw:=FALSE;
								continue;{выход в меню}
							end;
						
					end;
				end

             else key:=readkey;

             case key of
                  #80:begin
                           inc(currentel);
                           if currentel>4 then currentel:=currentel-4;
                      end;
                  #72:begin
                           dec(currentel);
                           if currentel<1 then currentel:=currentel+4;
                      end;
                  #13:case currentel of
                           1:begin
								 fw:=FALSE;	
								 MainMatrixInit(MainMatrix,'s');
								 GameWindow(MainMatrix,fw);
							 end;
						   2:begin
								 fw:=FALSE;	
								 MainMatrixInit(MainMatrix,'t');
								 GameWindow(MainMatrix,fw);
							 end;
                           3:Rules;
                           4:halt(0);
					  end;
             end;
             
             
             
       until (FALSE);
    end;{Menu}

BEGIN{main}

	GraphInit(Driver,Mode);
	Menu;
	CloseGraph;
	
END.{main}

