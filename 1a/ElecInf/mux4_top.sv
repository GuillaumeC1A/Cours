// Write your modules here!
module mux2(input logic E0,
            input logic E1,
            input logic Sel,
            output logic S);
  always@(*)
    if (Sel) S<=E1;
    else S<=E0;
endmodule

module top(input logic[3:0] E,
           input logic[1:0] Salt,
           output logic Z);
  
  logic S1, S2;
  
  mux2 Inst1(.E0(E[0]),.E1(E[1]),.Sel(Salt[0]),.S(S1));
  mux2 Inst2(.E0(E[2]),.E1(E[3]),.Sel(Salt[0]),.S(S2));
  mux2 Inst3(.E0(S1),.E1(S2),.Sel(Salt[1]),.S(Z));
endmodule
    