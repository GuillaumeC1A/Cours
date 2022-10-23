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
endmodule


////////////////////////////////////////
// ALU : L'unité Arithmétique et logique
////////////////////////////////////////
module ALU(input logic [7:0] I,
           input logic [7:0] Op1,
           input logic [7:0] Op2,
           output logic [7:0] ALU_out) ;


// Votre code ICI
  always@(*) begin 
    case(I)
      XOR : ALU_out <= Op1 ^ Op2;
      AND : ALU_out <= Op1 & Op2;
      OR  : ALU_out <= Op1 | Op2;
      ADD : ALU_out <= Op1 + Op2;
      SUB : ALU_out <= Op1 - Op2;
      default : ALU_out <= 8'd0;
    endcase
  end 
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
             output logic WRITE) ;

// Votre code ICI
  enum logic {IF, DF} etat;
  always@(posedge clk or negedge reset_n) begin
    if(!reset_n)
      etat <= IF;
    else 
      case(etat)
        IF : etat <= DF;
        DF : etat <= IF;
      endcase 
  end 
  
  //On peut faire always@(*) begin end ou alors always@(*) à chaque ligne
  //juste pour chaque "bloc d'instruction" porte sur une seule ligne, un seul bloc
  //Mais c'est exactement la même chose !
  
  always@(*) Load_I <= (etat == IF);
  always@(*) Load_Acc <= (etat == DF) && (I != STA);
  always@(*) Sel_Acc <= (etat == DF) && (I == LDA);
  always@(*) WRITE <= (etat == DF) && (I == STA);
endmodule