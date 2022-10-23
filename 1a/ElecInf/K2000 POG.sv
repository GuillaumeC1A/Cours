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

// WRITE YOUR CODE HERE
  logic dir;
  always@(posedge clk or negedge reset) begin
    if(!(reset)) begin
      leds<=12'b000000000001;
      dir <= 0; //On part vers la gauche
    end
    else begin
      if (leds == 12'b010000000000)
      dir <= 1; //On part vers la droite
      else if (leds == 12'b00000000010)
      dir <= 0; //On part vers la droite
  
    if(dir==0)
      leds<={leds[10:0],1'b0}; //décalage à gauche
    else if(dir==1)
      leds<={1'b0,leds[11:1]}; //décalage à droite
    end
end
endmodule

