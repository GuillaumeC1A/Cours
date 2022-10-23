// Write your modules here!
module mux2(input logic E0,
            input logic E1,
            input logic Sel,
            output logic S);
  always@(*)
    if (Sel) S <= E1;
    else S<= E0;
  
endmodule
