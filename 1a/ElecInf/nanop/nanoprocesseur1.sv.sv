`default_nettype none
/////////////////////////////////////////////////////////////////////////////////////
// Code pour le test du Nanoprocesseur : ETAPE1
/////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////
// Module auxiliaire pour les registres
/////////////////////////////////////////////////////////////////////////////////////
// Un module permettant de stocker une donnée de 'width' bits conditionnellement a un signal de chargement.
module registre #(parameter width=4) (input logic clk, input logic [width-1:0]D, input logic LOAD, output logic [width-1:0]Q) ;
  always @(posedge clk) if(LOAD) Q <= D ;
endmodule


////////////////////////////////////////////////////////////////////////////////////////////
// Le nanoprocesseur proprement dit
////////////////////////////////////////////////////////////////////////////////////////////

module processeur(input logic clk,
                  input logic reset_n,
                  output logic WRITE,
                  output logic [7:0] ADDR,
                  output logic [7:0] DOUT,
                  input logic [7:0] DIN) ;

  // PC
  PC u_PC(.clk(clk), .reset_n(reset_n), .PC(ADDR)) ;

  // Registre d'instruction
  logic Load_I ;
  logic [7:0] I;
  registre #(.width(8))  reg_I(.clk(clk), .D(DIN), .Q(I), .LOAD(Load_I)) ;

  // Registre pour le premier opérande
  logic Load_op1 ;
  logic [7:0] Op1;
  registre #(.width(8))  reg_Op1(.clk(clk), .D(DIN), .Q(Op1), .LOAD(Load_op1)) ;

  // Registre pour le second opérande
  logic Load_op2 ;
  logic [7:0] Op2;
  registre #(.width(8))  reg_Op2(.clk(clk), .D(DIN), .Q(Op2), .LOAD(Load_op2)) ;

// Unité arithmétique et logique
  ALU u_ALU(.I(I),
            .Op1(Op1),
            .Op2(Op2),
            .ALU_out(DOUT)) ;

 // Controleur
  CTRL u_CTRL(.clk(clk),
              .reset_n(reset_n),
              .Load_I(Load_I),
              .Load_op1(Load_op1),
              .Load_op2(Load_op2),
              .WRITE(WRITE));

endmodule

////////////////////////////////////////////////////////////////////////////////////////////
// L'assemblage du micro processeur avec sa mémoire associée
// Le PORT de sortie parallèle du Nanoprocesseur est connecté a une barre de Led
////////////////////////////////////////////////////////////////////////////////////////////
module board(input logic clk,
             input logic reset_n,
             output logic [7:0] LedBar) ;

  // Les signaux de connection
  logic [7:0] RAM_ADDR ;
  logic [7:0] RAM_DIN ;
  logic [7:0] RAM_DOUT ;
  logic RAM_WRITE ;

  // L'instance de  la mémoire
  ram u_ram(.clk(clk), .ADDR(RAM_ADDR), .D(RAM_DIN), .Q(RAM_DOUT), .WRITE(RAM_WRITE)) ;

  // L'instance du processeur
  processeur u_proc(.clk(clk), .reset_n(reset_n),  .ADDR(RAM_ADDR), .DIN(RAM_DOUT), .DOUT(RAM_DIN), .WRITE(RAM_WRITE)) ;

  // Pour le moment la sortie LedBar n'est pas utilisée
  // Mais il faut affecter qqchose a la sortie
  // sinon "le module board" est éliminé par la synthèse
  always@( *) LedBar <= RAM_ADDR ;
endmodule


/////////////////////////////////////////////////////////////////////////////////////
// Code squelette pour le Nanoprocesseur: La mémoire pour le programme et les données
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


////////////////////////////////////////////////////////////////////////////////////////////
// La mémoire RAM.  Contenant un programme de test
////////////////////////////////////////////////////////////////////////////////////////////
// Attention le style de codage utilisé ici, ne fait pas partie des apprentissages
// d'ELECINF102.
// - Il suffit de comprendre que la RAM a un certain contenu initial

module ram (input logic [7:0] ADDR,
           input logic [7:0] D,
           output logic [7:0]Q,
           input logic clk,
           input logic WRITE );

  logic [7:0] memoire [0:255] ;
  // Etape 1

  // Le programme a exécuter est ici
  // Programme de l'étape 1
  initial begin
     memoire[0] = ADD ;          // +
     memoire[1] = 8'd3 ;         // 3
     memoire[2] = 8'd4 ;         // 4
     // memoire[3] = x           // Contiendra 7
     memoire[4] = SUB ;          // -
     memoire[5] = 8'd12 ;        // 12
     memoire[6] = 8'd8  ;        // 8
     // memoire[7] = x           // Contiendra 4
  end

  always @(negedge clk)
    if(WRITE) memoire[ADDR] <= D ;

  always @(negedge clk)
    Q <= memoire[ADDR] ;
endmodule
