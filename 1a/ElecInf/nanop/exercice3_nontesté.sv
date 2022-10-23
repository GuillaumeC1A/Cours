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
module PC(input logic clk, input logic reset_n, input logic Inc_PC, output logic [7:0] PC) ;
// Votre code ICI
  always@(posedge clk or negedge reset_n) begin
    if(!reset_n)
      PC <= 8'd0;
    else if(Inc_PC)
      PC <= PC + 8'd1;
  end 
  //Cela revient à faire +Inc_PC puisqu'il vaut 1 quand il faut add 1 et 0 sinon.
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
      XOR : ALU_out <= Op1 ^ Op2;
      AND : ALU_out <= Op1 & Op2;
       OR : ALU_out <= Op1 | Op2;
      ADD : ALU_out <= Op1 + Op2;
      SUB : ALU_out <= Op1 - Op2;
endmodule

///////////////////////
// CTRL : Le contrôleur
///////////////////////
module CTRL (input logic clk,
             input logic reset_n,
             input logic [7:0] I,
             output logic Load_I,
             output logic Load_Acc,
             output logic Sel_Acc,
             output logic Load_Addr,
             output logic Sel_Addr,
             output logic Inc_PC,
             output logic WRITE) ;

// Votre code ICI
  enum logic [1:0] {AF, IF, EX} etat;
  always@(posedge clk or negedge reset_n) begin
    if(!reset_n) 
      etat <= IF;
    else 
      case(etat) 
        IF : etat <= AF;
        AF : etat <= EX;
        EX : etat <= IF;
      endcase
  end 
  
  always@(*) Inc_PC <= (etat == IF) || (etat == AF);
  always@(*) Sel_Acc <= (etat == EX) && (I == LDA);
  always@(*) Load_Acc <= (etat == EX) && (I != STA);
  always@(*) Load_Addr <= (etat == AF);
  always@(*) Sel_Addr <= (etat == EX);
  always@(*) WRITE <= (etat== AF) && (I== STA);
  always@(*) Load_I <= (etat == IF);
endmodule

