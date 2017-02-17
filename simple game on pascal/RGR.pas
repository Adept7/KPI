Program RGR;
uses GraphABC, ABCObjects;
type
  Coord = record
    x, y: byte;
  end;
var
  RedB,WhiteB,BlueB               :PictureABC;
  ChangeSizeM, ChangeSizeP        :PictureABC;
  Background                      :PictureABC;
  SizeT,Finish,Title,T1,RulesT,Rules,Start           :TextABC;
  Point,ChoosePoint               :SquareABC;
  Field                           :ObjectBoardABC;
  y1,x1,xMouse,yMouse:integer;
  Size,px,py,b: word;
  FlChoose: boolean;{false = fail, true = victory}
  sound := new system.Media.SoundPlayer;
  Arr:array[1..9,1..9]of byte;
  
procedure DrawField(Size:word); forward;
procedure Select_Object; forward;
procedure DrawBounce; forward;

  
                                     //MENU PROCEDURE
procedure MouseDown(x, y, mb: integer);
begin
  if mb = 1 then
  begin
    xMouse := x;
    yMouse := y;
  end;
end;



Procedure DrawMenu;
var
  s: string;
  f:text;
  ch:char;
begin
ClearWindow;
Size:=480;
SetWindowSize(800,500);
Background:=new PictureABC(0,0,'Menu.jpg');
Background.Width:=800;
Background.Height:=500;

Title:=new TextABC(160,50,30,'Голанский флаг',clWhite);
Title.FontSize:=50;
Title.FontStyle:=fsitalic;

SetFontName('Georgia');
T1 := new TextABC(250, 350, 20, 'Изменить размер поля', clWhite);
  ChangeSizeM:= new PictureABC(250, 395, 'minus.png');
  str(Size div 80,s);
  SizeT := new TextABC(380, 400, 15, s + 'x' + s, clWhite);
  ChangeSizeP:= new PictureABC(500, 395, 'plus.png');
  
Start:=new TextABC(340,190,40,'Start',clBlack); 
Rules:=new TextABC(365,280,20,'Rules',clBlack);
Finish:=new TextABC(650,420,23,'Выход',clWhite);

assign(f,'rules.txt');
reset(f);
s := '';
while not eof(f) do
begin
  read(f,ch);
  s := s + ch;
  while not eoln(f) do
  begin
    read(f,ch);
    s := s + ch;
  end;
end;
SetFontName('Georgia');
RulesT := new TextABC(120,25,15,s, clBlack);
RulesT.Visible := false;
RulesT.FontName := 'Georgia';
end;



procedure Menu;
var
  s: string;
  FRules:boolean;
begin
FRules:=false;
DrawMenu;
while true do
begin
  xMouse := -1;
  while xMouse = -1 do
    OnMouseDown := MouseDown;
    
  if ChangeSizeM.PtInside(xMouse, yMouse) then
    if Size > 240 then
    begin
      Size := Size - 240;
      str(Size div 80, s);
      SizeT.Text := s + 'x' + s;
    end;
   
  if ChangeSizeP.PtInside(xMouse, yMouse) then
    if Size <720 then
    begin
      Size := Size + 240;
      str(Size div 80, s);
      SizeT.Text := s + 'x' + s;
    end;      
      
  if Rules.PtInside(xMouse, yMouse) then
  begin
    if FRules=false then 
      begin
         Rules.Text:='Back to menu';
         Rules.MoveOn(-50,0);
      end
    else
      begin
        Rules.Text:='Rules     ';
        Rules.MoveOn(50,0);
      end;  
    ChangeSizeM.Visible:=not ChangeSizeM.Visible;
    ChangeSizeP.Visible:=not ChangeSizeP.Visible;
    Start.Visible:=not Start.Visible;
    T1.Visible:=not T1.Visible;
    Finish.Visible:=not Finish.Visible;
    SizeT.Visible:=not SizeT.Visible;
    Title.Visible:=not Title.Visible;
    RulesT.Visible:=not RulesT.Visible;
    FRules:=not FRules;
    end;
    
    if Start.PtInside(xMouse, yMouse) then
    begin
      ClearWindow;
      DrawField(Size);
      DrawBounce;
      Select_Object;   
    end;
    
    if Finish.PtInside(xMouse, yMouse) then
      halt;
  end;   
end;

                                //GAME PROCEDURE
 procedure Check;
 var Sq:SquareABC; CheckWin:boolean; i,j:byte;
 begin
 CheckWin:=true;
 for i:=1 to Size div 80 do
   for j:=1 to Size div 80 do
     begin
     if i<=size div 80/3 then
       if Arr[i,j]<>2 then  begin CheckWin:=false; break; end;
     if ((i>size div 80/3) and (i<=2*(size div 80/3)))  then 
       if Arr[i,j]<>1 then  begin CheckWin:=false; break; end;
     if ((i>2*(size div 80/3)) and (i<=size div 80))  then 
       if Arr[i,j]<>0 then  begin CheckWin:=false; break; end;
     end;
   if CheckWin=true then
   begin
   Sound.SoundLocation:='victory.wav';
   Sound.Play;
   Sq:=new SquareABC(0,0,Size);
   Sq.Filled:=false;
   Sq.BorderColor:=clLightGreen;
   Sq.BorderWidth:=5;
   Sq.FontStyle:=fsBoldItalic;
   Sq.FontColor:=clGreen;
   Sq.Text:='You WIN!!!';
   end;
    
 end;



procedure DrawField;
begin 
ClearWindow;
SetWindowSize(Size, Size);
CenterWindow;
SetWindowIsFixedSize(true);
SetWindowCaption('РГР, вариант 24. Шевель О.С, "Голандский флаг"');
Field := new ObjectBoardABC(0, 0, Size div 80, Size div 80, 80, 80, clwhite);
Field.BorderWidth := 1;
Background:= new PictureABC(0,0,'Background.png');
Background.Width:=Size;
Background.Height:=Size;
BlueB:=new PictureABC(0,0,'BlueB.png');                                    
RedB:=new PictureABC(0,0,'RedB.png'); 
WhiteB:=new PictureABC(0,0,'WhiteB.png'); 
end;



procedure DrawBounce;
var CellNum,kB,kR,kW,i,j,r:byte;
begin
CellNum:=sqr(Size div 80);
kB:=0;
kW:=0;
kR:=0;
i:=1;
j:=1;
While j*i<=CellNum do
    begin
      r:=random(3);
      case r of 
        0:if kB<CellNum/3 then
          begin
            Field.Items[j,i]:=blueb.Clone0;
            inc(kB);
            Arr[i,j]:=0;
            if ((j=Size div 80) and (i<>sqrt(CellNum))) then begin inc(i); j:=1;  end
              else inc(j);
          end;
        1:if kW<CellNum/3 then
          begin
            Field.Items[j,i]:=Whiteb.clone0;
            inc(kW);
            Arr[i,j]:=1;
            if ((j=Size div 80) and (i<>sqrt(CellNum))) then begin inc(i); j:=1;  end
              else inc(j);
          end;
        2:if kR<CellNum/3 then
          begin
            Field.Items[j,i]:=Redb.clone0;
            inc(kR);
            Arr[i,j]:=2;
            if ((j=Size div 80) and (i<>sqrt(CellNum))) then begin inc(i); j:=1;  end
              else inc(j);
          end;
        end;
    end;    
WhiteB.Destroy;
BlueB.Destroy;
RedB.Destroy;
end;



procedure KeyDown(Key: integer);
begin
case Key of
  VK_Left:  if px>80   then begin Point.MoveOn(-80,0);  px:=px-80; end;
  VK_Right: if px<Size then begin Point.MoveOn(80,0);   px:=px+80; end;
  VK_Up:    if py>80   then begin Point.MoveOn(0,-80);  py:=py-80; end;
  VK_Down:  if py<Size then begin Point.MoveOn(0,80);   py:=py+80; end;
  VK_Space: begin 
              if FlChoose=true then
                begin
                  b:=Arr[y1,x1];
                  Arr[y1,x1]:=Arr[py div 80,px div 80];
                  Arr[py div 80,px div 80]:=b;                  
                  Field.SwapObjects(x1,y1,px div 80,py div 80);
                  sound.SoundLocation := 'click.wav';
                  sound.Play;
                  Check;
                  ChoosePoint.Visible:=false;
                  FLChoose:=false;
                end
              else
                begin
                  x1:=px div 80;
                  y1:=py div 80;
                  ChoosePoint.Visible:=true;
                  ChoosePoint.MoveTo(px-80,py-80);
                  FlChoose:=true;
                end;
            end; 
  VK_Back: halt;            
  end;
end;   



procedure Select_Object;
begin
FlChoose:=false;
Point:=new SquareABC(0,0,81);
  Point.Filled:=false;
  Point.BorderWidth:=5;
  Point.Color:=clDarkGray;

ChoosePoint:=new SquareABC(0,0,81);
  ChoosePoint.Filled:=false;
  ChoosePoint.BorderWidth:=5;
  ChoosePoint.Visible:=false;
  ChoosePoint.BorderColor:=clLightGreen;
px:=80; py:=80;  
OnKeyDown := KeyDown;
end;


begin  
Menu; 
end.