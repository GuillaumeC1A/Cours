// Board with specific IO devices
// * ten switch button
// * one 12 leds bar
// * six 7 segments display

module board_tp(
  input logic clk,
  input logic rst,
  input logic sw0, sw1, sw2, sw3, sw4, sw5, sw6, sw7, sw8, sw9,
  output logic [11:0] LedBar0,
  output logic [6:0]  SevenSeg0,
  output logic [6:0]  SevenSeg1,
  output logic [6:0]  SevenSeg2,
  output logic [6:0]  SevenSeg3,
  output logic [6:0]  SevenSeg4,
  output logic [6:0]  SevenSeg5
  ) ;

  dut dut_i(
    .clk   (   clk                                                ) ,
    .reset (   rst                                                ) ,
    .sw    ( { sw9, sw8, sw7, sw6, sw5, sw4, sw3, sw2, sw1, sw0 } ) ,
    .leds  (   LedBar0                                            ) ,
    .hex0  (   SevenSeg0                                          ) ,
    .hex1  (   SevenSeg1                                          ) ,
    .hex2  (   SevenSeg2                                          ) ,
    .hex3  (   SevenSeg3                                          ) ,
    .hex4  (   SevenSeg4                                          ) ,
    .hex5  (   SevenSeg5                                          )
  ) ;

endmodule

// The main module
module dut (
    input  logic        clk   ,
    input  logic        reset ,
    input  logic [9:0]  sw    ,
    output logic [11:0] leds  ,
    output logic [6:0]  hex0  ,
    output logic [6:0]  hex1  ,
    output logic [6:0]  hex2  ,
    output logic [6:0]  hex3  ,
    output logic [6:0]  hex4  ,
    output logic [6:0]  hex5
  );

  logic signed [3:0] a;
  logic [3:0] a_pos;
  always@(*) begin
    a<=sw[3:0];
  if(a[3])
    a_pos<=-a;
  else
    a_pos<=a;
  end
  dec7seg i_dec7seg0(a,hex0);
  always@(*) hex1<={~a_pos[3],6'b111111};
  
  logic signed [3:0] b;
  logic [3:0] p_pos;
  always@(*) begin
    b<=sw[7:4];
    if(b[3])
      b_pos<=-b;
    else
      b_pos<=b;
    end 
  dec7seg i_dec7seg1(b_pos,hex1);
  always@(*) hex3<={~b[3],6'b111111};
  
  logic signed [4:0] res; //Sous 5 bits car 4b + 4b prend 5b de place
  always@(*) begin 
    if(sw[9])
      res<=a+b;
    else 
      res<=a-b;
    //A compléter ici... 
    //Plus haut aussi pour afficher des "-"
  dec7seg i_dec7seg2(res[3:0],hex2);
  dec7seg i_dec7seg3({3'b0,res[4]},hex3);
    

endmodule

