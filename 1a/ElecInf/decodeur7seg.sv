// Write your modules here!
module dec7seg(input logic[3:0] E,
               output logic[6:0] SevenSeg0);
  always@(*)
case(E)
    4'b0000 : SevenSeg0 <= 7'b1000000;
    4'b0001 : SevenSeg0 <= 7'b1111001;
    4'b0010 : SevenSeg0 <= 7'b0100100;
    4'b0011 : SevenSeg0 <= 7'b0110000;
    4'b0100 : SevenSeg0 <= 7'b0011001;
    4'b0101 : SevenSeg0 <= 7'b0010010;
    4'b0110 : SevenSeg0 <= 7'b0000010;
    4'b0111 : SevenSeg0 <= 7'b1111000;
    4'b1000 : SevenSeg0 <= 7'b0000000;
    4'b1001 : SevenSeg0 <= 7'b0010000;
    4'b1010 : SevenSeg0 <= 7'b0001000;
    4'b1011 : SevenSeg0 <= 7'b0000011 ;
    4'b1100 : SevenSeg0 <= 7'b0000110 ;
    4'b1101 : SevenSeg0 <= 7'b0100001 ;
    4'b1110 : SevenSeg0 <= 7'b0000110 ;
    4'b1111 : SevenSeg0 <= 7'b0001110 ;
  endcase
    

endmodule