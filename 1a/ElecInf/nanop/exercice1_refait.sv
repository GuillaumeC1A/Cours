`default_nettype none
/////////////////////////////////////////////////////////////////////////////////////
// Code squelette pour les modules  PC, ALU et CTRL du Nanoprocesseur
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// Définition de constantes permettant d'obtenir un code plus lisible
/////////////////////////////////////////////////////////////////////////////////////
`ifndef INSTRUCTIONS
// Etape 1
localparam ADD = 8'b0000_0100;
localparam SUB = 8'b0000_0110;
// Etape 1,2 & 3
localparam XOR = 8'b0000_0001;
localparam AND = 8'b0000_0010;
localparam  OR = 8'b0000_0011;
localparam LDA = 8'b0000_1010;
localparam STA = 8'b0000_1011;
// Etape 4
localparam NOP = 8'b0000_0000;
localparam OUT = 8'b0000_1100;
localparam ADC = 8'b0000_0101;
localparam SBC = 8'b0000_0111;
localparam ROL = 8'b0000_1000;
localparam ROR = 8'b0000_1001;
localparam JMP = 8'b0000_1101;
localparam JNC = 8'b0000_1110;
localparam JNZ = 8'b0000_1111;
`define INSTRUCTIONS
`endif

/////////////////////////////////
// PC : Le compteur de programmme
/////////////////////////////////
module PC(input logic clk, input logic reset_n, output logic [7:0] PC) ;

  // Votre code ICI
  always@(posedge clk or negedge reset_n) begin 
    if(!reset_n)
      PC <= 8'b0;
    else
      PC <= PC + 8'b1;
  end
endmodule


////////////////////////////////////////
// ALU : L'unité Arithmétique et logique
////////////////////////////////////////
module ALU(input logic [7:0] I,
           input logic [7:0] Op1,
           input logic [7:0] Op2,
           output logic [7:0] ALU_out) ;

   // Votre code ICI
  always@(*)
    case(I)
      ADD : ALU_out <= Op1+Op2;
      SUB : ALU_out <= Op1-Op2;
    endcase
  
endmodule

///////////////////////
// CTRL : Le contrôleur
///////////////////////
module CTRL (input logic clk,
             input logic reset_n,
             output logic Load_I,
             output logic Load_op1,
             output logic Load_op2,
             output logic WRITE) ;

      // VOTRE CODE ICI
  enum logic {IF, OP1F, OP2F, WR} etat, etat_f;
  
  always @(posedge clk or negedge reset_n) begin
    if(!reset_n)
      etat <= IF;
    else
      etat <= etat_f;
  end
  always@(*)
    case(etat)
      IF    : begin Load_I <= 1'b1; Load_op1 <= 1'b0 ; Load_op2 <= 1'b0; WRITE <= 1'b0; end
      OP1F  : begin Load_I <= 1'b0; Load_op1 <= 1'b1 ; Load_op2 <= 1'b0; WRITE <= 1'b0; end
      OP2F  : begin Load_I <= 1'b0; Load_op1 <= 1'b0 ; Load_op2 <= 1'b1; WRITE <= 1'b0; end
      WRITE : begin Load_I <= 1'b0; Load_op1 <= 1'b0 ; Load_op2 <= 1'b0; WRITE <= 1'b1; end
    endcase
endmodule

